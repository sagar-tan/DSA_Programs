'use client';

import { useState, useEffect } from 'react';
import DatasetUploader from './components/DatasetUploader';
import AnalysisPanel from './components/AnalysisPanel';
import ClusterVisualization from './components/ClusterVisualization';
import ArticleSearch from './components/ArticleSearch';
import StatisticsDisplay from './components/StatisticsDisplay';

export default function Home() {
  const [datasetLoaded, setDatasetLoaded] = useState(false);
  const [datasetInfo, setDatasetInfo] = useState(null);
  const [analysisResults, setAnalysisResults] = useState(null);
  const [activeTab, setActiveTab] = useState('upload');
  const [apiStatus, setApiStatus] = useState({ status: 'checking', message: 'Checking API connection...' });

  // Check API connection on component mount
  useEffect(() => {
    checkApiStatus();
  }, []);

  // Function to check if the backend API is running
  const checkApiStatus = async () => {
    setApiStatus({ status: 'checking', message: 'Checking API connection...' });
    try {
      const response = await fetch('http://127.0.0.1:5000/api/health');
      
      if (response.ok) {
        const data = await response.json();
        setApiStatus({
          status: 'connected',
          message: data.message || 'API is connected',
        });
      } else {
        setApiStatus({
          status: 'error',
          message: 'API responded with an error',
        });
      }
    } catch (error) {
      setApiStatus({
        status: 'error',
        message: 'Failed to connect to API. Please make sure the backend server is running.',
      });
    }
  };

  // Handle successful dataset upload
  const handleDatasetUploaded = (info) => {
    setDatasetLoaded(true);
    setDatasetInfo(info);
    setActiveTab('analyze');
  };

  // Handle analysis completion
  const handleAnalysisComplete = (results) => {
    setAnalysisResults(results);
    setActiveTab('visualize');
  };

  // Function to render the current active tab
  const renderActiveTab = () => {
    switch (activeTab) {
      case 'upload':
        return (
          <DatasetUploader 
            onDatasetUploaded={handleDatasetUploaded} 
            apiStatus={apiStatus}
          />
        );
      case 'analyze':
        return (
          <AnalysisPanel 
            datasetInfo={datasetInfo} 
            onAnalysisComplete={handleAnalysisComplete}
          />
        );
      case 'visualize':
        return (
          <ClusterVisualization 
            analysisResults={analysisResults}
          />
        );
      case 'search':
        return (
          <ArticleSearch 
            datasetLoaded={datasetLoaded}
          />
        );
      case 'statistics':
        return (
          <StatisticsDisplay 
            datasetInfo={datasetInfo}
            analysisResults={analysisResults}
          />
        );
      default:
        return (
          <DatasetUploader 
            onDatasetUploaded={handleDatasetUploaded} 
            apiStatus={apiStatus}
          />
        );
    }
  };

  return (
    <main className="min-h-screen p-6">
      <div className="max-w-7xl mx-auto">
        <header className="mb-8 glass-panel rounded-lg p-5 text-center">
          <h1 className="text-3xl font-bold text-white">
            Constitution of India Analysis Platform
          </h1>
          <p className="mt-2 text-gray-300">
            Upload, analyze, and visualize patterns in the Constitution of India
          </p>
          
          {apiStatus.status !== 'connected' && (
            <div className="mt-4 p-3 bg-red-900/40 backdrop-blur-sm text-red-200 rounded-md border border-red-800/50">
              <strong>API Status:</strong> {apiStatus.message}
              <button 
                onClick={checkApiStatus}
                className="ml-4 px-3 py-1 bg-red-800/60 hover:bg-red-700/60 rounded text-sm"
              >
                Retry Connection
              </button>
            </div>
          )}
        </header>

        {/* Navigation Tabs */}
        <div className="mb-5 flex justify-center">
          <nav className="flex glass-card p-1 rounded-full">
            <button
              onClick={() => setActiveTab('upload')}
              className={`px-4 py-2 text-sm rounded-full transition-all ${
                activeTab === 'upload'
                  ? 'bg-sky-700/70 text-white shadow-sm'
                  : 'text-gray-300 hover:text-white hover:bg-slate-800/40'
              }`}
              disabled={apiStatus.status !== 'connected'}
            >
              Upload Dataset
            </button>
            <button
              onClick={() => setActiveTab('analyze')}
              className={`px-4 py-2 text-sm rounded-full transition-all ${
                activeTab === 'analyze'
                  ? 'bg-sky-700/70 text-white shadow-sm'
                  : 'text-gray-300 hover:text-white hover:bg-slate-800/40'
              }`}
              disabled={!datasetLoaded || apiStatus.status !== 'connected'}
            >
              Analyze
            </button>
            <button
              onClick={() => setActiveTab('visualize')}
              className={`px-4 py-2 text-sm rounded-full transition-all ${
                activeTab === 'visualize'
                  ? 'bg-sky-700/70 text-white shadow-sm'
                  : 'text-gray-300 hover:text-white hover:bg-slate-800/40'
              }`}
              disabled={!analysisResults || apiStatus.status !== 'connected'}
            >
              Visualize
            </button>
            <button
              onClick={() => setActiveTab('search')}
              className={`px-4 py-2 text-sm rounded-full transition-all ${
                activeTab === 'search'
                  ? 'bg-sky-700/70 text-white shadow-sm'
                  : 'text-gray-300 hover:text-white hover:bg-slate-800/40'
              }`}
              disabled={!datasetLoaded || apiStatus.status !== 'connected'}
            >
              Search
            </button>
            <button
              onClick={() => setActiveTab('statistics')}
              className={`px-4 py-2 text-sm rounded-full transition-all ${
                activeTab === 'statistics'
                  ? 'bg-sky-700/70 text-white shadow-sm'
                  : 'text-gray-300 hover:text-white hover:bg-slate-800/40'
              }`}
              disabled={!datasetLoaded || apiStatus.status !== 'connected'}
            >
              Stats
            </button>
          </nav>
        </div>

        {/* Content Area */}
        <div className="glass-card p-5">
          {renderActiveTab()}
        </div>
      </div>
    </main>
  );
} 