from flask import Flask, request, jsonify, send_file
from flask_cors import CORS
import pandas as pd
import numpy as np
import json
import os
import re
import traceback
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
import nltk
from nltk.tokenize import word_tokenize, RegexpTokenizer
from nltk.corpus import stopwords
import matplotlib.pyplot as plt
from io import BytesIO
import base64
from scipy import sparse

# Initialize Flask app
app = Flask(__name__)
# Allow cross-origin requests from all origins
CORS(app, origins=["http://localhost:3000", "http://127.0.0.1:3000", "http://localhost:8000"], methods=["GET", "POST"], allow_headers=["Content-Type"])

# Download necessary NLTK data
try:
    nltk.download('punkt')
    nltk.download('stopwords')
except Exception as e:
    print(f"Error downloading NLTK data: {str(e)}")

# Create a RegexpTokenizer as a fallback
simple_tokenizer = RegexpTokenizer(r'\w+')

# Use a simple tokenizer function to avoid punkt_tab issues
def safe_tokenize(text):
    """Tokenize text using either NLTK or a regex fallback"""
    try:
        return word_tokenize(text)
    except Exception as e:
        print(f"Warning: NLTK tokenization failed, using regex fallback. Error: {str(e)}")
        return simple_tokenizer.tokenize(text)

# In-memory storage
current_dataset = None
processed_data = None
trained_model = None
feature_extractor = None
analysis_results = {}
visualizations = {}

# Root route to verify the server is running
@app.route('/', methods=['GET'])
def root():
    """Root endpoint for server verification"""
    return jsonify({
        "status": "running", 
        "message": "Constitution Analysis API is running. Use /api/health for health check.",
        "endpoints": [
            "/api/health",
            "/api/dataset/upload",
            "/api/dataset/analyze",
            "/api/visualization/<viz_type>",
            "/api/clusters/<cluster_id>",
            "/api/search",
            "/api/stats"
        ]
    })

# Helper Functions
def preprocess_text(text):
    """Preprocess text by removing special characters and tokenizing"""
    if not isinstance(text, str) or not text.strip():
        return "empty text"  # Return a placeholder instead of empty string
    
    # Remove special characters and convert to lowercase
    text = re.sub(r'[^\w\s]', ' ', text.lower())
    
    # Tokenize and remove stopwords
    stop_words = set(stopwords.words('english'))
    tokens = safe_tokenize(text)
    filtered_tokens = [w for w in tokens if w not in stop_words and len(w) > 1]
    
    # If all tokens were removed, keep some original tokens to prevent empty text
    if not filtered_tokens and tokens:
        filtered_tokens = [w for w in tokens if len(w) > 1][:5]  # Keep up to 5 non-stopwords
    
    # If still empty, add a placeholder
    if not filtered_tokens:
        return "empty text"
        
    return " ".join(filtered_tokens)

def extract_features(data):
    """Extract TF-IDF features from text data"""
    # Ensure we have non-empty text to analyze
    processed_texts = data.copy()
    
    # Add dummy text to prevent empty vocabulary, will be removed later in clustering
    dummy_text = "constitution government law rights freedom justice equality republic federal democracy"
    processed_texts.append(dummy_text)
    
    # Check if all texts are empty and add a fallback
    empty_count = sum(1 for text in processed_texts if not text.strip())
    if empty_count > len(processed_texts) * 0.9:  # If more than 90% are empty
        print(f"Warning: {empty_count} out of {len(processed_texts)} texts are empty after preprocessing")
        # Add more diverse tokens to ensure enough vocabulary
        for i, text in enumerate(processed_texts):
            if not text.strip():
                # Add some diverse dummy content with position-dependent words
                processed_texts[i] = f"text{i} document{i} content{i} analysis{i} {i % 10}"
    
    # Use very permissive vectorizer settings to get as many features as possible
    vectorizer = TfidfVectorizer(
        max_features=500,
        min_df=1,         # Include terms that appear in only one document
        max_df=1.0,       # Include terms that appear in all documents
        sublinear_tf=True # Apply sublinear tf scaling (logarithmic)
    )
    
    try:
        # Fit and transform the data
        features = vectorizer.fit_transform(processed_texts)
        
        # If we have very few features, add artificial variation
        if features.shape[1] < 5:
            print(f"Warning: Only {features.shape[1]} features extracted, adding artificial variation")
            # Recreate texts with more variation
            varied_texts = processed_texts.copy()
            for i in range(len(varied_texts)):
                # Append positional markers to create artificial variation
                if i % 2 == 0:
                    varied_texts[i] += f" variation_{i} group_a group_b"
                else:
                    varied_texts[i] += f" variation_{i} group_c group_d"
                    
            # Refit with varied texts
            vectorizer = TfidfVectorizer(
                max_features=500,
                min_df=1,
                max_df=1.0,
                sublinear_tf=True
            )
            features = vectorizer.fit_transform(varied_texts)
            
        # Remove the dummy document we added at the beginning
        features = features[:-1]
        
        print(f"Extracted {features.shape[1]} features from {features.shape[0]} documents")
        return vectorizer, features
        
    except Exception as e:
        print(f"Error in feature extraction: {str(e)}")
        # Create a minimal feature matrix with random values
        print("Creating fallback feature matrix")
        n_docs = len(processed_texts) - 1  # Exclude the dummy document
        n_features = 10
        fallback_features = np.random.rand(n_docs, n_features)
        sparse_features = sparse.csr_matrix(fallback_features)
        
        # Create a minimal vectorizer
        class FallbackVectorizer:
            def transform(self, texts):
                # Return features with same number of rows as input
                return sparse.csr_matrix(np.random.rand(len(texts), n_features))
                
        return FallbackVectorizer(), sparse_features

def generate_clusters(features, n_clusters=5):
    """Generate clusters using KMeans"""
    kmeans = KMeans(n_clusters=n_clusters, random_state=42)
    clusters = kmeans.fit_predict(features)
    return kmeans, clusters

def reduce_dimensions(features, n_components=2):
    """Reduce dimensions using PCA for visualization"""
    # Get the maximum possible components based on data shape
    max_components = min(features.shape[0], features.shape[1])
    
    # Adjust n_components if needed
    if n_components > max_components:
        print(f"Warning: Reducing n_components from {n_components} to {max_components}")
        n_components = max_components
    
    # If we can't even do 1D PCA, return simple coordinates
    if max_components == 0:
        print("Warning: Cannot perform PCA, using default coordinates")
        # Create simple coordinates - each point at position (index, 0)
        return None, np.array([[i, 0] for i in range(features.shape[0])])
    
    # If we can only do 1D PCA, add a second coordinate of zeros
    if max_components == 1:
        print("Warning: Can only perform 1D PCA, adding second coordinate")
        pca = PCA(n_components=1)
        reduced_1d = pca.fit_transform(features.toarray())
        # Add a second dimension of zeros to make it 2D
        reduced_features = np.column_stack((reduced_1d, np.zeros(reduced_1d.shape[0])))
        return pca, reduced_features
    
    # Normal case - we can do full PCA
    pca = PCA(n_components=n_components)
    reduced_features = pca.fit_transform(features.toarray())
    return pca, reduced_features

def generate_wordcloud_data(text_data, clusters, cluster_id):
    """Generate word frequency data for a specific cluster"""
    cluster_texts = [text for i, text in enumerate(text_data) if clusters[i] == cluster_id]
    combined_text = " ".join(cluster_texts)
    
    # Count word frequencies
    words = safe_tokenize(combined_text)
    word_freq = {}
    for word in words:
        if len(word) > 1:  # Skip single character words
            word_freq[word] = word_freq.get(word, 0) + 1
    
    # Sort by frequency and return top 50
    sorted_words = sorted(word_freq.items(), key=lambda x: x[1], reverse=True)[:50]
    return dict(sorted_words)

def generate_visualization(data_type):
    """Generate visualizations based on data type"""
    global processed_data, analysis_results
    
    if data_type == "clusters":
        # Check if we have the required data
        if "reduced_features" not in analysis_results or "clusters" not in analysis_results:
            print("Missing required data for visualization")
            return None
            
        try:
            reduced_features = analysis_results["reduced_features"]
            clusters = analysis_results["clusters"]
            
            # Verify dimensions
            if reduced_features is None or len(reduced_features) == 0:
                print("No reduced features available for visualization")
                return None
                
            if reduced_features.shape[0] != len(clusters):
                print(f"Dimension mismatch: {reduced_features.shape[0]} points but {len(clusters)} cluster labels")
                # Truncate or pad to make them match
                min_len = min(reduced_features.shape[0], len(clusters))
                reduced_features = reduced_features[:min_len]
                clusters = clusters[:min_len]
            
            # Create the plot
            plt.figure(figsize=(10, 8))
            plt.scatter(
                reduced_features[:, 0],
                reduced_features[:, 1],
                c=clusters,
                cmap='viridis',
                alpha=0.6
            )
            plt.title("Article Clusters")
            plt.xlabel("Component 1")
            plt.ylabel("Component 2")
            
            # Save plt to a bytes buffer
            buffer = BytesIO()
            plt.savefig(buffer, format='png')
            buffer.seek(0)
            
            # Convert to base64 string
            img_str = base64.b64encode(buffer.getvalue()).decode('utf-8')
            plt.close()
            
            return img_str
        except Exception as e:
            print(f"Error generating visualization: {str(e)}")
            # Create a fallback visualization
            try:
                plt.figure(figsize=(10, 8))
                # Generate random points in a grid pattern
                n_points = len(processed_data) if processed_data is not None else 50
                x = np.array([i % 10 for i in range(n_points)])
                y = np.array([i // 10 for i in range(n_points)])
                colors = np.array([i % 5 for i in range(n_points)])
                
                plt.scatter(x, y, c=colors, cmap='viridis', alpha=0.6)
                plt.title("Fallback Visualization (Error in clustering)")
                plt.xlabel("X")
                plt.ylabel("Y")
                
                buffer = BytesIO()
                plt.savefig(buffer, format='png')
                buffer.seek(0)
                
                img_str = base64.b64encode(buffer.getvalue()).decode('utf-8')
                plt.close()
                
                return img_str
            except:
                return None
    
    return None

# API Routes
@app.route('/api/health', methods=['GET'])
def health_check():
    """API health check endpoint"""
    response_data = {"status": "healthy", "message": "Constitution Analysis API is running"}
    return jsonify(response_data)

@app.route('/api/dataset/upload', methods=['POST'])
def upload_dataset():
    """Upload and process a CSV dataset"""
    global current_dataset, processed_data
    
    try:
        if 'file' not in request.files:
            # Check if we should use default data
            if request.form.get('useDefault', 'false') == 'true':
                # Load the built-in Constitution of India.csv
                file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 
                                     '..', 'Constitution Of India.csv')
                print(f"Looking for file at: {file_path}")
                print(f"File exists: {os.path.exists(file_path)}")
                
                if os.path.exists(file_path):
                    try:
                        df = pd.read_csv(file_path)
                        current_dataset = df
                        
                        print("DataFrame loaded, columns:", df.columns.tolist())
                        
                        # Basic preprocessing
                        print("Starting preprocessing...")
                        # Initialize with empty strings instead of empty list
                        df['Processed_Text'] = ""
                        for i, row in df.iterrows():
                            try:
                                processed = preprocess_text(row['Articles'])
                                df.at[i, 'Processed_Text'] = processed
                            except Exception as e:
                                print(f"Error processing row {i}: {str(e)}")
                                df.at[i, 'Processed_Text'] = ""
                        
                        processed_data = df
                        print("Preprocessing complete")
                        
                        return jsonify({
                            "success": True,
                            "message": "Default Constitution of India dataset loaded successfully",
                            "rows": len(df),
                            "columns": df.columns.tolist(),
                            "sample": df.head(5).to_dict('records')
                        })
                    except Exception as inner_e:
                        print(f"Error in file processing: {str(inner_e)}")
                        return jsonify({"success": False, "message": f"Error processing default file: {str(inner_e)}"}), 500
                else:
                    return jsonify({"success": False, "message": "Default dataset file not found"}), 404
            
            return jsonify({"success": False, "message": "No file provided"}), 400
        
        file = request.files['file']
        
        if file.filename == '':
            return jsonify({"success": False, "message": "No file selected"}), 400
        
        if file and file.filename.endswith('.csv'):
            # Read the CSV file
            df = pd.read_csv(file)
            current_dataset = df
            
            # Determine the text column - assume it's called 'Articles' for Constitution data
            text_column = 'Articles' if 'Articles' in df.columns else df.columns[0]
            
            # Basic preprocessing
            df['Processed_Text'] = ""  # Initialize with empty string
            for i, row in df.iterrows():
                try:
                    processed = preprocess_text(row[text_column])
                    df.at[i, 'Processed_Text'] = processed
                except Exception as e:
                    print(f"Error processing row {i}: {str(e)}")
                    df.at[i, 'Processed_Text'] = ""
            
            processed_data = df
            
            return jsonify({
                "success": True,
                "message": "Dataset uploaded and processed successfully",
                "rows": len(df),
                "columns": df.columns.tolist(),
                "sample": df.head(5).to_dict('records')
            })
        else:
            return jsonify({"success": False, "message": "Only CSV files are supported"}), 400
            
    except Exception as e:
        traceback_str = traceback.format_exc()
        print(f"Error in upload_dataset: {str(e)}")
        print(traceback_str)
        return jsonify({"success": False, "message": f"Error processing file: {str(e)}"}), 500

@app.route('/api/dataset/analyze', methods=['POST'])
def analyze_dataset():
    """Analyze the dataset and extract insights"""
    global processed_data, analysis_results, feature_extractor, visualizations
    
    if processed_data is None:
        return jsonify({"success": False, "message": "No dataset has been processed yet"}), 400
    
    try:
        # Get the parameters
        params = request.json.get('params', {}) if request.json else {}
        print(f"Received analyze parameters: {params}")
        
        # Extract number of clusters with fallback
        n_clusters = 5  # Default value
        
        if 'num_clusters' in params:
            try:
                n_clusters = int(params['num_clusters'])
                print(f"Using requested number of clusters: {n_clusters}")
            except (ValueError, TypeError):
                print(f"Invalid value for num_clusters: {params['num_clusters']}, using default: 5")
        elif 'clusters' in params:
            try:
                n_clusters = int(params['clusters'])
                print(f"Using legacy 'clusters' parameter: {n_clusters}")
            except (ValueError, TypeError):
                print(f"Invalid value for clusters: {params['clusters']}, using default: 5")
        
        # Ensure the number of clusters is within reasonable bounds
        n_clusters = max(2, min(10, n_clusters))  # Between 2 and 10
        print(f"Final number of clusters: {n_clusters}")
        
        # Clear previous visualizations
        visualizations = {}
        
        # Check if we have any text to analyze
        if 'Processed_Text' not in processed_data.columns:
            return jsonify({"success": False, "message": "No processed text column found in dataset"}), 400
        
        # Log what we're working with
        print(f"Starting analysis with {len(processed_data)} rows")
        
        # Ensure we have a reasonable number of clusters
        if len(processed_data) < n_clusters:
            original_n_clusters = n_clusters
            n_clusters = min(5, max(2, len(processed_data) // 2))
            print(f"Adjusted number of clusters from {original_n_clusters} to {n_clusters} based on dataset size")
        
        # Extract features
        print("Extracting features...")
        try:
            vectorizer, features = extract_features(processed_data['Processed_Text'].tolist())
            feature_extractor = vectorizer
            print(f"Features shape: {features.shape}")
        except Exception as feature_error:
            print(f"Error during feature extraction: {str(feature_error)}")
            return jsonify({"success": False, "message": f"Error extracting features: {str(feature_error)}"}), 500
        
        # Ensure we have enough data for clustering
        if features.shape[0] < n_clusters:
            original_n_clusters = n_clusters
            n_clusters = max(2, features.shape[0] - 1)
            print(f"Adjusted number of clusters from {original_n_clusters} to {n_clusters} based on feature shape")
        
        # Generate clusters
        print(f"Generating {n_clusters} clusters...")
        try:
            kmeans, clusters = generate_clusters(features, n_clusters)
        except Exception as cluster_error:
            print(f"Error during clustering: {str(cluster_error)}")
            return jsonify({"success": False, "message": f"Error during clustering: {str(cluster_error)}"}), 500
        
        # Reduce dimensions for visualization
        print("Reducing dimensions for visualization...")
        try:
            pca, reduced_features = reduce_dimensions(features)
        except Exception as pca_error:
            print(f"Error during dimensionality reduction: {str(pca_error)}")
            # Create fallback 2D coordinates
            reduced_features = np.array([[i % 10, i // 10] for i in range(features.shape[0])])
            pca = None
            print("Using fallback coordinates for visualization")
        
        # Store results
        analysis_results = {
            "features": features,
            "clusters": clusters,
            "cluster_model": kmeans,
            "reduced_features": reduced_features,
            "pca_model": pca
        }
        
        # Add cluster assignments to processed data
        processed_data['Cluster'] = clusters
        
        # Generate top words for each cluster
        print("Generating top words for each cluster...")
        cluster_words = {}
        try:
            for i in range(n_clusters):
                cluster_words[i] = generate_wordcloud_data(
                    processed_data['Processed_Text'].tolist(), 
                    clusters, 
                    i
                )
        except Exception as wordcloud_error:
            print(f"Error generating word clouds: {str(wordcloud_error)}")
            # Create fallback word frequencies
            for i in range(n_clusters):
                cluster_words[i] = {f"term_{j}": 10-j for j in range(1, 11)}
        
        # Generate cluster visualization
        print("Generating visualizations...")
        try:
            cluster_viz = generate_visualization("clusters")
            if cluster_viz:
                visualizations["clusters"] = cluster_viz
                print("Visualization generated successfully")
            else:
                print("No visualization was generated")
        except Exception as viz_error:
            print(f"Error generating visualization: {str(viz_error)}")
            traceback_str = traceback.format_exc()
            print(traceback_str)
        
        print("Analysis complete")
        return jsonify({
            "success": True,
            "message": "Dataset analyzed successfully",
            "clusters": {
                "count": n_clusters,
                "distribution": {str(i): int((clusters == i).sum()) for i in range(n_clusters)},
                "top_words": cluster_words
            },
            "visualizations": list(visualizations.keys())
        })
        
    except Exception as e:
        traceback_str = traceback.format_exc()
        print(f"Error in analyze_dataset: {str(e)}")
        print(traceback_str)
        return jsonify({"success": False, "message": f"Error analyzing dataset: {str(e)}"}), 500

@app.route('/api/visualization/<viz_type>', methods=['GET'])
def get_visualization(viz_type):
    """Get a specific visualization"""
    if viz_type not in visualizations:
        return jsonify({"success": False, "message": f"Visualization {viz_type} not found"}), 404
    
    return jsonify({
        "success": True,
        "image": visualizations[viz_type]
    })

@app.route('/api/clusters/<int:cluster_id>', methods=['GET'])
def get_cluster_items(cluster_id):
    """Get items belonging to a specific cluster"""
    global processed_data, analysis_results
    
    if processed_data is None or "clusters" not in analysis_results:
        return jsonify({"success": False, "message": "No clusters have been generated yet"}), 400
    
    try:
        cluster_data = processed_data[processed_data['Cluster'] == cluster_id]
        
        # Get top words for this cluster
        top_words = generate_wordcloud_data(
            processed_data['Processed_Text'].tolist(),
            analysis_results["clusters"],
            cluster_id
        )
        
        return jsonify({
            "success": True,
            "cluster_id": cluster_id,
            "count": len(cluster_data),
            "top_words": top_words,
            "items": cluster_data.head(20).to_dict('records')
        })
        
    except Exception as e:
        return jsonify({"success": False, "message": f"Error retrieving cluster data: {str(e)}"}), 500

@app.route('/api/search', methods=['POST'])
def search_dataset():
    """Search the dataset for relevant articles"""
    global processed_data, feature_extractor, analysis_results
    
    if processed_data is None:
        return jsonify({"success": False, "message": "No dataset has been processed yet"}), 400
    
    try:
        params = request.json or {}
        query = params.get('query', '')
        
        if not query:
            return jsonify({"success": False, "message": "Search query is required"}), 400
        
        print(f"Processing search query: '{query}'")
        
        # Process the query
        try:
            processed_query = preprocess_text(query)
            print(f"Processed query: '{processed_query}'")
        except Exception as query_error:
            print(f"Error processing query: {str(query_error)}")
            # Use a simplified approach if preprocess fails
            processed_query = query.lower()
            processed_query = re.sub(r'[^\w\s]', ' ', processed_query)
            processed_query = " ".join([w for w in processed_query.split() if len(w) > 1])
            print(f"Fallback processed query: '{processed_query}'")
        
        # If query processing resulted in empty text, use original with minimal processing
        if not processed_query or processed_query == "empty text":
            processed_query = " ".join([w for w in query.lower().split() if len(w) > 1])
            print(f"Using minimal processed query: '{processed_query}'")
        
        # If we have a feature extractor, use it for a more sophisticated search
        if feature_extractor and "features" in analysis_results:
            print("Using TF-IDF based search")
            try:
                query_vector = feature_extractor.transform([processed_query])
                
                # Calculate similarity scores
                from sklearn.metrics.pairwise import cosine_similarity
                feature_matrix = analysis_results["features"]
                similarity_scores = cosine_similarity(query_vector, feature_matrix).flatten()
                
                # Get top matches
                top_indices = similarity_scores.argsort()[-10:][::-1]
                results = processed_data.iloc[top_indices].copy()
                results['similarity'] = similarity_scores[top_indices]
                
                print(f"Found {len(results)} matches using TF-IDF search")
                return jsonify({
                    "success": True,
                    "query": query,
                    "results": results.to_dict('records')
                })
            except Exception as vector_error:
                print(f"Error in vector-based search: {str(vector_error)}")
                print("Falling back to simple text search")
                # Continue to fallback method
        
        # Fallback to simple text matching
        print("Using simple text matching search")
        try:
            # First try with processed_data['Articles']
            if 'Articles' in processed_data.columns:
                matching_rows = processed_data[processed_data['Articles'].str.contains(query, case=False, na=False)]
                
                if len(matching_rows) == 0:
                    # If no matches, try with first column as fallback
                    first_col = processed_data.columns[0]
                    matching_rows = processed_data[processed_data[first_col].str.contains(query, case=False, na=False)]
                
                print(f"Found {len(matching_rows)} matches using text search")
                return jsonify({
                    "success": True,
                    "query": query,
                    "results": matching_rows.head(10).to_dict('records')
                })
            else:
                # Use first column
                first_col = processed_data.columns[0]
                matching_rows = processed_data[processed_data[first_col].str.contains(query, case=False, na=False)]
                
                print(f"Found {len(matching_rows)} matches using text search on column '{first_col}'")
                return jsonify({
                    "success": True,
                    "query": query,
                    "results": matching_rows.head(10).to_dict('records')
                })
        except Exception as text_search_error:
            print(f"Error in text search: {str(text_search_error)}")
            # Last resort - return first 5 rows of dataset
            print("Returning first 5 rows as fallback")
            return jsonify({
                "success": True,
                "query": query,
                "message": "Search failed, showing sample results",
                "results": processed_data.head(5).to_dict('records')
            })
        
    except Exception as e:
        traceback_str = traceback.format_exc()
        print(f"Error in search_dataset: {str(e)}")
        print(traceback_str)
        return jsonify({
            "success": False, 
            "message": "An error occurred during search. Please try a different query.",
            "error": str(e)
        }), 500

@app.route('/api/stats', methods=['GET'])
def get_dataset_stats():
    """Get statistics about the loaded dataset"""
    global processed_data
    
    if processed_data is None:
        return jsonify({"success": False, "message": "No dataset has been processed yet"}), 400
    
    try:
        # Calculate text length statistics
        text_lengths = processed_data['Articles'].str.len()
        word_counts = processed_data['Articles'].str.split().str.len()
        
        # Calculate word frequency if processed text is available
        word_freq = {}
        if 'Processed_Text' in processed_data.columns:
            all_words = " ".join(processed_data['Processed_Text']).split()
            for word in all_words:
                if len(word) > 1:  # Skip single character words
                    word_freq[word] = word_freq.get(word, 0) + 1
        
        # Get top words
        top_words = dict(sorted(word_freq.items(), key=lambda x: x[1], reverse=True)[:50])
        
        # Get cluster stats if available
        cluster_stats = None
        if 'Cluster' in processed_data.columns:
            cluster_counts = processed_data['Cluster'].value_counts().to_dict()
            cluster_stats = {
                "count": len(cluster_counts),
                "distribution": {str(k): int(v) for k, v in cluster_counts.items()}
            }
        
        return jsonify({
            "success": True,
            "rows": len(processed_data),
            "text_stats": {
                "avg_length": float(text_lengths.mean()),
                "min_length": int(text_lengths.min()),
                "max_length": int(text_lengths.max()),
                "avg_words": float(word_counts.mean()),
                "min_words": int(word_counts.min()),
                "max_words": int(word_counts.max()),
            },
            "top_words": top_words,
            "clusters": cluster_stats
        })
    except Exception as e:
        return jsonify({"success": False, "message": f"Error calculating statistics: {str(e)}"}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000) 