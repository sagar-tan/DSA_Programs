# Constitution of India Analysis Platform

A data analysis system that processes and visualizes the Constitution of India dataset, extracting insights through topic clustering, text analysis, and search capabilities.

## Features

- **Dataset Processing**: Upload and analyze the Constitution of India CSV file
- **Text Analysis**: Extract meaningful features from constitutional text
- **Interactive Clustering**: Group similar articles into thematic clusters
- **Visualizations**: Real-time visualizations of clusters and word frequencies
- **Semantic Search**: Find relevant articles through intelligent search
- **Statistics Dashboard**: Explore key metrics and insights about the Constitution

## Tech Stack

- **Backend**: Python, Flask, scikit-learn, NLTK, Pandas, Matplotlib
- **Frontend**: Next.js, React, TailwindCSS
- **Data Analysis**: TF-IDF Vectorization, K-means Clustering, PCA Dimensionality Reduction

## Getting Started

### Prerequisites

- Python 3.9+
- Node.js 14+
- npm or yarn

### Installation

1. **Clone the repository**:
   ```
   git clone <repository-url>
   cd ai-recipe-generator
   ```

2. **Set up the backend**:
   ```
   cd backend
   pip install -r requirements.txt
   ```

3. **Set up the frontend**:
   ```
   cd ../frontend
   npm install
   ```

### Running the Application

1. **Start the backend server**:
   ```
   cd backend
   python app.py
   ```
   The backend will be available at `http://localhost:5000`

2. **Start the frontend development server**:
   ```
   cd frontend
   npm run dev
   ```
   The frontend will be available at `http://localhost:3000`

3. **Access the application** by opening `http://localhost:3000` in your browser

## Usage

1. Start by uploading the Constitution of India CSV file or use the built-in dataset
2. Analyze the dataset to extract features and generate clusters
3. Explore the visualizations to discover patterns in the Constitution
4. Use the search feature to find specific articles based on keywords
5. Review statistics and insights about the dataset structure

## Dataset

The system is designed to work with the `Constitution Of India.csv` file, which contains the full text of the Indian Constitution organized by articles.

## License

This project is open source and available under the MIT License. 