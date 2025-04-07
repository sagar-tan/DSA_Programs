'use client';

import { useState, useEffect } from 'react';

export default function ClusterVisualization({ analysisResults }) {
  const [selectedCluster, setSelectedCluster] = useState(null);
  const [clusterItems, setClusterItems] = useState(null);
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState(null);
  const [clusterImage, setClusterImage] = useState(null);
  const [isLoadingImage, setIsLoadingImage] = useState(false);
  const [imageError, setImageError] = useState(null);
  const [loadTimeout, setLoadTimeout] = useState(false);
  const [clusters, setClusters] = useState(null);

  useEffect(() => {
    const fetchClusters = async () => {
      setIsLoading(true);
      setError(null);
      
      try {
        const response = await fetch('http://127.0.0.1:5000/api/visualization/clusters');
        
        if (!response.ok) {
          const errorData = await response.json();
          throw new Error(errorData.message || 'Failed to fetch cluster data');
        }
        
        const data = await response.json();
        setClusters(data);
      } catch (error) {
        console.error('Error fetching clusters:', error);
        setError(error.message || 'Failed to load cluster visualization');
      } finally {
        setIsLoading(false);
      }
    };
    
    fetchClusters();
  }, []);

  const fetchClusterImage = async () => {
    if (!analysisResults?.visualizations?.includes('clusters')) {
      setImageError("Visualization data not available");
      return;
    }
    
    setIsLoadingImage(true);
    setImageError(null);
    
    // Set a timeout to detect if the request is taking too long
    const timeoutId = setTimeout(() => {
      setLoadTimeout(true);
    }, 10000); // 10 seconds timeout
    
    try {
      const response = await fetch('http://127.0.0.1:5000/api/visualization/clusters');
      
      clearTimeout(timeoutId);
      
      if (!response.ok) {
        throw new Error('Failed to fetch visualization');
      }
      
      const data = await response.json();
      
      if (data.success && data.image) {
        setClusterImage(data.image);
      } else {
        throw new Error(data.message || 'No image data received');
      }
    } catch (error) {
      console.error('Error fetching cluster image:', error);
      setImageError(error.message || 'Failed to load visualization');
    } finally {
      setIsLoadingImage(false);
      clearTimeout(timeoutId);
    }
  };

  const fetchClusterItems = async (clusterId) => {
    setIsLoading(true);
    setError(null);
    
    try {
      const response = await fetch(`http://localhost:5000/api/clusters/${clusterId}`);
      
      if (!response.ok) {
        throw new Error('Failed to fetch cluster details');
      }

      const data = await response.json();
      setClusterItems(data);
      setIsLoading(false);
    } catch (error) {
      setError('Error fetching cluster details: ' + error.message);
      setIsLoading(false);
    }
  };

  const handleClusterClick = async (clusterId) => {
    setSelectedCluster(clusterId);
    setIsLoading(true);
    setError(null);
    
    try {
      const response = await fetch(`http://127.0.0.1:5000/api/clusters/${clusterId}`);
      
      if (!response.ok) {
        throw new Error('Failed to fetch cluster details');
      }
      
      const data = await response.json();
      setClusterItems(data);
    } catch (error) {
      console.error('Error fetching cluster details:', error);
      setError(error.message || 'Failed to load cluster details');
    } finally {
      setIsLoading(false);
    }
  };

  if (!analysisResults) {
    return (
      <div className="text-center py-8">
        <div className="text-yellow-400 mb-4">
          <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
        </div>
        <h2 className="text-xl font-semibold text-white mb-2">No Analysis Results</h2>
        <p className="text-gray-300">Please analyze the dataset first before viewing visualizations.</p>
      </div>
    );
  }

  // Get cluster data from analysis results
  const clusterData = analysisResults.clusters || {};
  const clusterCount = clusterData.count || 0;
  const clusterDistribution = clusterData.distribution || {};
  const topWords = clusterData.top_words || {};

  return (
    <div className="max-w-6xl mx-auto">
      <div className="mb-6">
        <h2 className="text-xl font-semibold text-white mb-2">
          Constitution Article Clusters
        </h2>
        <p className="text-gray-300 mb-4">
          The Constitution articles have been grouped into {clusterCount} thematic clusters.
          Click on a cluster to see its details and representative articles.
        </p>
      </div>

      {error && (
        <div className="bg-red-900/30 text-red-200 p-3 rounded-md text-sm mb-4 border border-red-800/40">
          {error}
        </div>
      )}

      <div className="grid grid-cols-1 lg:grid-cols-3 gap-6 mb-8">
        <div className="lg:col-span-2 glass-panel rounded-lg p-4">
          <h3 className="text-lg font-medium text-white mb-4">Cluster Visualization</h3>
          
          {isLoadingImage ? (
            <div className="h-64 flex flex-col items-center justify-center border border-slate-700/30 rounded-lg bg-slate-800/20">
              <div className="animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-sky-500 mb-4"></div>
              <p className="text-gray-300">Loading visualization...</p>
              {loadTimeout && (
                <div className="mt-4 text-yellow-400 text-sm">
                  <p>This is taking longer than expected.</p>
                  <button 
                    onClick={fetchClusterImage}
                    className="px-3 py-1 mt-2 bg-yellow-600/50 hover:bg-yellow-500/50 rounded text-sm"
                  >
                    Try Again
                  </button>
                </div>
              )}
            </div>
          ) : imageError ? (
            <div className="h-64 flex flex-col items-center justify-center border border-slate-700/30 rounded-lg bg-slate-800/20">
              <div className="text-red-400 mb-4">
                <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M12 8v4m0 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
                </svg>
              </div>
              <p className="text-red-200 mb-4">{imageError}</p>
              <button 
                onClick={fetchClusterImage}
                className="glass-primary-button"
              >
                Retry Loading
              </button>
            </div>
          ) : clusterImage ? (
            <div className="relative border border-slate-700/30 rounded-lg overflow-hidden">
              <img 
                src={`data:image/png;base64,${clusterImage}`} 
                alt="Article Clusters Visualization" 
                className="w-full h-auto"
              />
              <div className="absolute bottom-2 right-2 glass-card px-2 py-1 text-xs text-gray-300 rounded shadow">
                PCA Visualization of Article Clusters
              </div>
            </div>
          ) : (
            <div className="h-64 flex items-center justify-center border border-slate-700/30 rounded-lg bg-slate-800/20">
              <div className="text-gray-400">No visualization available</div>
            </div>
          )}
        </div>
        
        <div className="glass-panel rounded-lg p-4">
          <h3 className="text-lg font-medium text-white mb-4">Cluster Distribution</h3>
          <div className="space-y-3">
            {Object.entries(clusterDistribution).map(([clusterId, count]) => {
              // Calculate percentage
              const percentage = Math.round((count / Object.values(clusterDistribution).reduce((a, b) => a + b, 0)) * 100);
              
              return (
                <div key={clusterId} className="relative">
                  <button
                    onClick={() => handleClusterClick(clusterId)}
                    className={`w-full text-left p-3 rounded-lg transition-colors ${
                      selectedCluster === clusterId
                        ? 'bg-sky-900/40 border border-sky-700/40'
                        : 'bg-slate-800/30 hover:bg-slate-700/30 border border-slate-700/30'
                    }`}
                  >
                    <div className="flex justify-between items-center mb-1">
                      <span className="font-medium text-white">Cluster {clusterId}</span>
                      <span className="text-xs bg-sky-900/60 text-sky-200 px-2 py-1 rounded-full">
                        {count} articles
                      </span>
                    </div>
                    <div className="w-full bg-slate-700/50 rounded-full h-2.5">
                      <div
                        className="bg-sky-600/70 h-2.5 rounded-full"
                        style={{ width: `${percentage}%` }}
                      ></div>
                    </div>
                    <div className="mt-2 text-xs text-gray-300">
                      {percentage}% of all articles
                    </div>
                  </button>
                </div>
              );
            })}
          </div>
        </div>
      </div>

      {selectedCluster !== null && (
        <div className="glass-panel rounded-lg p-4 mb-8">
          <div className="flex justify-between items-center mb-4">
            <h3 className="text-lg font-medium text-white">
              Cluster {selectedCluster} Details
            </h3>
            <button
              onClick={() => setSelectedCluster(null)}
              className="text-gray-400 hover:text-gray-300"
            >
              <svg xmlns="http://www.w3.org/2000/svg" className="h-5 w-5" viewBox="0 0 20 20" fill="currentColor">
                <path fillRule="evenodd" d="M4.293 4.293a1 1 0 011.414 0L10 8.586l4.293-4.293a1 1 0 111.414 1.414L11.414 10l4.293 4.293a1 1 0 01-1.414 1.414L10 11.414l-4.293 4.293a1 1 0 01-1.414-1.414L8.586 10 4.293 5.707a1 1 0 010-1.414z" clipRule="evenodd" />
              </svg>
            </button>
          </div>

          {isLoading ? (
            <div className="text-center py-8">
              <div className="animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-sky-500 mx-auto"></div>
              <p className="mt-4 text-gray-300">Loading cluster data...</p>
            </div>
          ) : clusterItems ? (
            <div>
              <div className="mb-6">
                <h4 className="text-md font-medium text-white mb-3">Key Terms in This Cluster</h4>
                <div className="flex flex-wrap gap-2">
                  {Object.entries(clusterItems.top_words || {}).slice(0, 20).map(([word, count]) => (
                    <div
                      key={word}
                      className="bg-sky-900/30 text-sky-200 px-3 py-1 rounded-full text-sm"
                      style={{
                        fontSize: `${Math.max(0.7, Math.min(1.5, 0.8 + count / 50))}rem`,
                      }}
                    >
                      {word}
                    </div>
                  ))}
                </div>
              </div>

              <div>
                <h4 className="text-md font-medium text-white mb-3">Articles in This Cluster</h4>
                <div className="space-y-4 mt-3">
                  {clusterItems.items && clusterItems.items.map((item, index) => (
                    <div key={index} className="border border-slate-700/30 rounded-md p-3 bg-slate-800/20">
                      <p className="text-white">{item.Articles}</p>
                    </div>
                  ))}
                </div>
                {clusterItems.count > (clusterItems.items || []).length && (
                  <p className="text-sm text-gray-300 mt-4">
                    Showing {clusterItems.items.length} of {clusterItems.count} articles in this cluster.
                  </p>
                )}
              </div>
            </div>
          ) : (
            <div className="text-center py-4">
              <p className="text-gray-300">Select a cluster to view details</p>
            </div>
          )}
        </div>
      )}

      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
        <div className="glass-panel rounded-lg p-4">
          <h3 className="text-lg font-medium text-white mb-4">Top Words by Cluster</h3>
          <div className="space-y-4">
            {Object.entries(topWords).map(([clusterId, words]) => (
              <div key={clusterId} className="border-t border-slate-700/30 pt-3">
                <h4 className="font-medium text-white mb-2">
                  Cluster {clusterId}
                </h4>
                <div className="flex flex-wrap gap-1">
                  {Object.entries(words).slice(0, 10).map(([word, count]) => (
                    <span 
                      key={word} 
                      className="inline-flex items-center px-2.5 py-0.5 rounded-full text-xs font-medium bg-slate-800/50 text-gray-200"
                    >
                      {word}
                    </span>
                  ))}
                </div>
              </div>
            ))}
          </div>
        </div>

        <div className="glass-panel rounded-lg p-4">
          <h3 className="text-lg font-medium text-white mb-4">Interpretation Guide</h3>
          <div className="text-gray-300 space-y-3">
            <p>
              The visualization shows how articles in the Constitution of India are grouped into thematic clusters based on their content.
            </p>
            <p>
              <strong>Clusters:</strong> Each color represents a distinct thematic group of articles that share similar language and topics.
            </p>
            <p>
              <strong>Key Terms:</strong> The most frequent and distinctive words that characterize each cluster, helping to understand the main themes.
            </p>
            <p>
              <strong>Distribution:</strong> The percentage of articles that fall into each cluster, showing the relative importance of different themes in the Constitution.
            </p>
            <p className="italic text-sm mt-4 text-gray-400">
              This analysis can reveal underlying patterns and relationships between constitutional provisions that might not be immediately apparent from a linear reading.
            </p>
          </div>
        </div>
      </div>
    </div>
  );
} 