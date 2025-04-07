'use client';

import { useState } from 'react';

export default function ArticleSearch({ datasetLoaded }) {
  const [searchQuery, setSearchQuery] = useState('');
  const [searchResults, setSearchResults] = useState(null);
  const [isSearching, setIsSearching] = useState(false);
  const [searchError, setSearchError] = useState(null);
  const [recentSearches, setRecentSearches] = useState([]);

  const handleSearch = async () => {
    if (!searchQuery.trim()) {
      setSearchError('Please enter a search query');
      return;
    }
    
    setIsSearching(true);
    setSearchError(null);
    setSearchResults([]);
    
    try {
      const response = await fetch('http://127.0.0.1:5000/api/search', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ query: searchQuery.trim() }),
      });
      
      if (!response.ok) {
        const errorData = await response.json();
        throw new Error(errorData.message || 'Search failed');
      }
      
      const data = await response.json();
      setSearchResults(data.results || []);
      
      if (data.results && data.results.length === 0) {
        setSearchError('No matching articles found');
      }
      
      // Add to recent searches if not already there
      if (!recentSearches.includes(searchQuery) && searchQuery.trim()) {
        setRecentSearches(prev => [searchQuery, ...prev].slice(0, 5));
      }
    } catch (error) {
      console.error('Search error:', error);
      setSearchError(error.message || 'Failed to perform search');
    } finally {
      setIsSearching(false);
    }
  };

  const handleRecentSearchClick = (query) => {
    setSearchQuery(query);
    // Trigger search immediately
    const event = { preventDefault: () => {} };
    setTimeout(() => handleSearch(event), 100);
  };

  if (!datasetLoaded) {
    return (
      <div className="text-center py-8">
        <div className="text-yellow-400 mb-4">
          <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
        </div>
        <h2 className="text-xl font-semibold text-white mb-2">No Dataset Available</h2>
        <p className="text-gray-300">Please upload a dataset first before searching.</p>
      </div>
    );
  }

  return (
    <div className="max-w-4xl mx-auto">
      <div className="mb-6">
        <h2 className="text-xl font-semibold text-white mb-2">
          Search Constitution Articles
        </h2>
        <p className="text-gray-300 mb-4">
          Enter keywords to find relevant articles in the Constitution of India.
        </p>
      </div>

      <div className="glass-panel rounded-lg mb-6">
        <form onSubmit={handleSearch}>
          <div className="flex flex-col sm:flex-row gap-3">
            <div className="flex-1 relative">
              <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                <svg className="h-5 w-5 text-gray-400" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20" fill="currentColor" aria-hidden="true">
                  <path fillRule="evenodd" d="M8 4a4 4 0 100 8 4 4 0 000-8zM2 8a6 6 0 1110.89 3.476l4.817 4.817a1 1 0 01-1.414 1.414l-4.816-4.816A6 6 0 012 8z" clipRule="evenodd" />
                </svg>
              </div>
              <input
                type="text"
                value={searchQuery}
                onChange={(e) => setSearchQuery(e.target.value)}
                placeholder="Search for keywords (e.g., rights, president, states)"
                className="glass-input pl-10 w-full"
                disabled={isSearching}
              />
            </div>
            <button
              type="submit"
              disabled={isSearching || !searchQuery.trim()}
              className={`px-4 py-2 text-sm font-medium rounded-md text-white ${
                isSearching || !searchQuery.trim()
                  ? 'bg-slate-700/50 cursor-not-allowed'
                  : 'glass-primary-button'
              }`}
            >
              {isSearching ? 'Searching...' : 'Search'}
            </button>
          </div>
        </form>

        {searchError && (
          <div className="bg-red-900/30 text-red-200 p-3 rounded-md text-sm mt-4 border border-red-800/40">
            {searchError}
          </div>
        )}

        {recentSearches.length > 0 && (
          <div className="mt-4">
            <div className="text-sm text-gray-300 mb-2">Recent searches:</div>
            <div className="flex flex-wrap gap-2">
              {recentSearches.map((query, index) => (
                <button
                  key={index}
                  onClick={() => handleRecentSearchClick(query)}
                  className="glass-button text-xs px-2.5 py-0.5 rounded-full"
                >
                  {query}
                </button>
              ))}
            </div>
          </div>
        )}
      </div>

      {isSearching && (
        <div className="text-center py-12">
          <div className="animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-sky-500 mx-auto"></div>
          <p className="mt-4 text-gray-300">Searching articles...</p>
        </div>
      )}

      {searchResults && !isSearching && (
        <div className="glass-panel rounded-lg overflow-hidden">
          <div className="px-4 py-5 border-b border-slate-700/30 sm:px-6">
            <h3 className="text-lg leading-6 font-medium text-white">
              Search Results
            </h3>
            <p className="mt-1 max-w-2xl text-sm text-gray-300">
              Found {searchResults.length} matching articles for "{searchQuery}"
            </p>
          </div>

          {searchResults.length === 0 ? (
            <div className="text-center py-8 px-4">
              <svg className="mx-auto h-12 w-12 text-gray-400" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9.172 16.172a4 4 0 015.656 0M9 10h.01M15 10h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
              </svg>
              <h3 className="mt-2 text-sm font-medium text-white">No results found</h3>
              <p className="mt-1 text-sm text-gray-300">
                Try adjusting your search terms or using different keywords.
              </p>
            </div>
          ) : (
            <div className="divide-y divide-slate-700/30">
              {searchResults.map((result, index) => (
                <div key={index} className="px-4 py-5 sm:p-6">
                  {'similarity' in result && (
                    <div className="mb-2">
                      <div className="text-xs text-gray-300 flex items-center">
                        <span>Relevance:</span>
                        <div className="ml-2 w-24 bg-slate-700/50 rounded-full h-1.5">
                          <div 
                            className="bg-sky-600/70 h-1.5 rounded-full" 
                            style={{ width: `${Math.round(result.similarity * 100)}%` }}
                          ></div>
                        </div>
                        <span className="ml-1">{Math.round(result.similarity * 100)}%</span>
                      </div>
                    </div>
                  )}
                  <p className="text-white">{result.Articles}</p>
                </div>
              ))}
            </div>
          )}
        </div>
      )}

      <div className="glass-panel mt-8 rounded-lg p-4">
        <h3 className="text-lg font-medium text-white mb-3">Search Tips</h3>
        <ul className="list-disc list-inside text-gray-300 space-y-2">
          <li>Use specific terms related to your area of interest (e.g., "fundamental rights", "elections")</li>
          <li>Try searching for key constitutional concepts like "liberty", "equality", "justice"</li>
          <li>Search for governmental bodies like "parliament", "judiciary", "president"</li>
          <li>Results are ranked by relevance to your query using semantic search</li>
        </ul>
      </div>
    </div>
  );
} 