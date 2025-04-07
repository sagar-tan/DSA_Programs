'use client';

import { useState, useEffect } from 'react';

export default function StatisticsDisplay({ datasetInfo, analysisResults }) {
  const [stats, setStats] = useState(null);
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchStats = async () => {
      setIsLoading(true);
      setError(null);
      
      try {
        const response = await fetch('http://127.0.0.1:5000/api/stats');
        
        if (!response.ok) {
          throw new Error('Failed to fetch statistics');
        }
        
        const data = await response.json();
        setStats(data);
      } catch (error) {
        console.error('Error fetching stats:', error);
        setError(error.message || 'Failed to load statistics');
      } finally {
        setIsLoading(false);
      }
    };
    
    fetchStats();
  }, []);

  if (!datasetInfo) {
    return (
      <div className="text-center py-8">
        <div className="text-yellow-400 mb-4">
          <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
        </div>
        <h2 className="text-xl font-semibold text-white mb-2">No Dataset Available</h2>
        <p className="text-gray-300">Please upload a dataset first to view statistics.</p>
      </div>
    );
  }

  if (isLoading) {
    return (
      <div className="text-center py-12">
        <div className="animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-sky-500 mx-auto"></div>
        <p className="mt-4 text-gray-300">Loading statistics...</p>
      </div>
    );
  }

  if (error) {
    return (
      <div className="text-center py-8">
        <div className="text-red-400 mb-4">
          <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M12 8v4m0 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
        </div>
        <h2 className="text-xl font-semibold text-white mb-2">Error Loading Statistics</h2>
        <p className="text-gray-300 mb-4">{error}</p>
        <button
          onClick={fetchStats}
          className="inline-flex items-center px-4 py-2 text-sm font-medium rounded-md glass-primary-button"
        >
          Retry
        </button>
      </div>
    );
  }

  if (!stats) {
    return null;
  }

  // Get text statistics
  const textStats = stats.text_stats || {};
  const topWords = stats.top_words || {};
  const clusters = stats.clusters;

  return (
    <div className="max-w-6xl mx-auto">
      <div className="mb-6">
        <h2 className="text-xl font-semibold text-gray-800 mb-2">
          Constitution of India Statistics
        </h2>
        <p className="text-gray-600 mb-4">
          Key metrics and insights about the Constitution dataset.
        </p>
      </div>

      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-4 mb-8">
        {/* Dataset Size Card */}
        <div className="bg-white rounded-lg shadow p-4">
          <h3 className="text-sm font-medium text-gray-500 uppercase tracking-wider mb-2">
            Dataset Size
          </h3>
          <p className="text-3xl font-bold text-blue-600">{stats.rows}</p>
          <p className="text-gray-600 text-sm mt-1">Total articles</p>
        </div>

        {/* Average Article Length */}
        <div className="bg-white rounded-lg shadow p-4">
          <h3 className="text-sm font-medium text-gray-500 uppercase tracking-wider mb-2">
            Average Length
          </h3>
          <p className="text-3xl font-bold text-blue-600">{Math.round(textStats.avg_words || 0)}</p>
          <p className="text-gray-600 text-sm mt-1">Words per article</p>
        </div>

        {/* Longest Article */}
        <div className="bg-white rounded-lg shadow p-4">
          <h3 className="text-sm font-medium text-gray-500 uppercase tracking-wider mb-2">
            Longest Article
          </h3>
          <p className="text-3xl font-bold text-blue-600">{Math.round(textStats.max_words || 0)}</p>
          <p className="text-gray-600 text-sm mt-1">Words in longest article</p>
        </div>

        {/* Cluster Count */}
        <div className="bg-white rounded-lg shadow p-4">
          <h3 className="text-sm font-medium text-gray-500 uppercase tracking-wider mb-2">
            Thematic Clusters
          </h3>
          <p className="text-3xl font-bold text-blue-600">{clusters ? clusters.count : 'N/A'}</p>
          <p className="text-gray-600 text-sm mt-1">Distinct topic groups</p>
        </div>
      </div>

      <div className="grid grid-cols-1 lg:grid-cols-3 gap-6 mb-8">
        {/* Word Cloud */}
        <div className="lg:col-span-2 bg-white rounded-lg shadow p-6">
          <h3 className="text-lg font-medium text-gray-800 mb-4">Most Frequent Terms</h3>
          <div className="flex flex-wrap gap-2">
            {Object.entries(topWords).slice(0, 50).map(([word, count]) => {
              // Calculate relative font size based on frequency
              const maxCount = Math.max(...Object.values(topWords));
              const minCount = Math.min(...Object.values(topWords));
              const fontSize = 0.8 + ((count - minCount) / (maxCount - minCount)) * 1.7;
              
              return (
                <div
                  key={word}
                  className="px-3 py-1 rounded-full"
                  style={{
                    fontSize: `${fontSize}rem`,
                    opacity: 0.7 + ((count - minCount) / (maxCount - minCount)) * 0.3,
                    backgroundColor: `hsl(${Math.floor(210 + (count / maxCount) * 150)}, 70%, 90%)`,
                    color: `hsl(${Math.floor(210 + (count / maxCount) * 150)}, 70%, 35%)`,
                  }}
                >
                  {word}
                </div>
              );
            })}
          </div>
        </div>

        {/* Text Statistics */}
        <div className="bg-white rounded-lg shadow p-6">
          <h3 className="text-lg font-medium text-gray-800 mb-4">Text Statistics</h3>
          <div className="space-y-4">
            <div>
              <div className="flex justify-between mb-1">
                <span className="text-sm font-medium text-gray-700">Average Words per Article</span>
                <span className="text-sm text-gray-600">{Math.round(textStats.avg_words || 0)}</span>
              </div>
              <div className="w-full bg-gray-200 rounded-full h-2">
                <div 
                  className="bg-blue-600 h-2 rounded-full" 
                  style={{ width: `${Math.min(100, (textStats.avg_words / 200) * 100)}%` }}
                ></div>
              </div>
            </div>
            
            <div>
              <div className="flex justify-between mb-1">
                <span className="text-sm font-medium text-gray-700">Min Words</span>
                <span className="text-sm text-gray-600">{Math.round(textStats.min_words || 0)}</span>
              </div>
              <div className="w-full bg-gray-200 rounded-full h-2">
                <div 
                  className="bg-blue-600 h-2 rounded-full" 
                  style={{ width: `${Math.min(100, (textStats.min_words / 200) * 100)}%` }}
                ></div>
              </div>
            </div>
            
            <div>
              <div className="flex justify-between mb-1">
                <span className="text-sm font-medium text-gray-700">Max Words</span>
                <span className="text-sm text-gray-600">{Math.round(textStats.max_words || 0)}</span>
              </div>
              <div className="w-full bg-gray-200 rounded-full h-2">
                <div 
                  className="bg-blue-600 h-2 rounded-full" 
                  style={{ width: `${Math.min(100, (textStats.max_words / 200) * 100)}%` }}
                ></div>
              </div>
            </div>

            <div className="pt-4 border-t border-gray-200">
              <h4 className="text-md font-medium text-gray-700 mb-2">Character Statistics</h4>
              
              <div className="flex justify-between mb-1">
                <span className="text-sm font-medium text-gray-700">Average Length</span>
                <span className="text-sm text-gray-600">{Math.round(textStats.avg_length || 0)} chars</span>
              </div>
              
              <div className="flex justify-between mb-1">
                <span className="text-sm font-medium text-gray-700">Shortest Article</span>
                <span className="text-sm text-gray-600">{Math.round(textStats.min_length || 0)} chars</span>
              </div>
              
              <div className="flex justify-between mb-1">
                <span className="text-sm font-medium text-gray-700">Longest Article</span>
                <span className="text-sm text-gray-600">{Math.round(textStats.max_length || 0)} chars</span>
              </div>
            </div>
          </div>
        </div>
      </div>

      {clusters && (
        <div className="bg-white rounded-lg shadow p-6 mb-8">
          <h3 className="text-lg font-medium text-gray-800 mb-4">Cluster Distribution</h3>
          <div className="overflow-hidden">
            <div className="flex h-10 mb-4">
              {Object.entries(clusters.distribution).map(([clusterId, count]) => {
                const percentage = (count / stats.rows) * 100;
                return (
                  <div
                    key={clusterId}
                    style={{ width: `${percentage}%` }}
                    className={`h-full flex items-center justify-center text-xs text-white font-medium px-1 ${
                      parseInt(clusterId) % 2 === 0 ? 'bg-blue-600' : 'bg-blue-500'
                    }`}
                    title={`Cluster ${clusterId}: ${count} articles (${percentage.toFixed(1)}%)`}
                  >
                    {percentage > 5 ? `${percentage.toFixed(1)}%` : ''}
                  </div>
                );
              })}
            </div>
            <div className="flex text-xs text-gray-600">
              {Object.entries(clusters.distribution).map(([clusterId, count]) => {
                const percentage = (count / stats.rows) * 100;
                return (
                  <div
                    key={clusterId}
                    style={{ width: `${percentage}%` }}
                    className="px-1 truncate"
                  >
                    {percentage > 3 ? `C${clusterId}` : ''}
                  </div>
                );
              })}
            </div>
          </div>
          <p className="mt-4 text-sm text-gray-500">
            The Constitution articles are distributed across {clusters.count} thematic clusters, with some clusters being more prevalent than others.
          </p>
        </div>
      )}

      <div className="bg-white rounded-lg shadow p-6">
        <h3 className="text-lg font-medium text-gray-800 mb-4">Insights</h3>
        <div className="space-y-4 text-gray-700">
          <p>
            The Constitution of India, with its {stats.rows} articles, is one of the most comprehensive constitutions in the world. 
            The analysis reveals several interesting patterns in its structure and content.
          </p>
          <p>
            The average article contains about {Math.round(textStats.avg_words || 0)} words, indicating a balance between brevity and detail. 
            The considerable variation in article length (from {Math.round(textStats.min_words || 0)} to {Math.round(textStats.max_words || 0)} words) 
            reflects the differing complexity of constitutional matters addressed.
          </p>
          <p>
            The most frequent terms in the text highlight the central concerns of the Constitution, 
            with focus on governance structures, rights, and procedural matters. The cluster analysis 
            reveals distinct thematic groupings, showing how different parts of the Constitution address 
            related concerns.
          </p>
          <p>
            This quantitative analysis provides a foundation for deeper legal and historical interpretation 
            of the document and its significance in India's governance framework.
          </p>
        </div>
      </div>
    </div>
  );
} 