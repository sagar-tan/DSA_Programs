'use client';

import { useState } from 'react';

export default function AnalysisPanel({ datasetInfo, onAnalysisComplete }) {
  const [isAnalyzing, setIsAnalyzing] = useState(false);
  const [analysisError, setAnalysisError] = useState(null);
  const [clusterCount, setClusterCount] = useState(5);
  const [analyzeProgress, setAnalyzeProgress] = useState(0);
  const [currentStep, setCurrentStep] = useState('');

  const simulateProgress = () => {
    // Simulate analysis progress with steps for better UX
    setAnalyzeProgress(0);
    const steps = [
      'Extracting features from text...',
      'Applying TF-IDF transformation...',
      'Clustering articles...',
      'Reducing dimensions for visualization...',
      'Generating word frequencies...',
      'Creating visualizations...'
    ];
    let stepIndex = 0;
    setCurrentStep(steps[stepIndex]);

    const interval = setInterval(() => {
      setAnalyzeProgress((prev) => {
        const increment = Math.random() * 5 + 3; // 3-8% increment
        const newProgress = prev + increment;
        
        // Change steps based on progress
        const newStepIndex = Math.min(Math.floor(newProgress / (100 / steps.length)), steps.length - 1);
        if (newStepIndex !== stepIndex) {
          stepIndex = newStepIndex;
          setCurrentStep(steps[stepIndex]);
        }
        
        return newProgress >= 90 ? 90 : newProgress; // Cap at 90% until actual completion
      });
    }, 500);
    
    return interval;
  };

  const handleStartAnalysis = async () => {
    setIsAnalyzing(true);
    setAnalysisError(null);
    setAnalyzeProgress(0);
    
    // Start progress simulation
    let percentage = 0;
    const interval = setInterval(() => {
      percentage += Math.random() * 10;
      if (percentage > 95) percentage = 95;
      setAnalyzeProgress(percentage);
    }, 500);
    
    try {
      const response = await fetch('http://127.0.0.1:5000/api/dataset/analyze', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          params: {
            num_clusters: parseInt(clusterCount, 10)
          }
        }),
      });
      
      clearInterval(interval);
      
      if (!response.ok) {
        const errorData = await response.json();
        throw new Error(errorData.message || 'Analysis failed');
      }
      
      const result = await response.json();
      setAnalyzeProgress(100);
      setCurrentStep('Analysis complete!');
      
      setTimeout(() => {
        onAnalysisComplete(result);
        setIsAnalyzing(false);
      }, 500);
      
    } catch (error) {
      clearInterval(interval);
      console.error('Analysis error:', error);
      setAnalysisError(error.message || 'An error occurred during analysis');
      setIsAnalyzing(false);
      setAnalyzeProgress(0);
      setCurrentStep('');
    }
  };

  if (!datasetInfo) {
    return (
      <div className="text-center py-8">
        <div className="text-yellow-400 mb-4">
          <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
        </div>
        <h2 className="text-xl font-semibold text-white mb-2">No Dataset Available</h2>
        <p className="text-gray-300">Please upload a dataset first before analyzing.</p>
      </div>
    );
  }

  return (
    <div className="max-w-3xl mx-auto">
      <div className="mb-6">
        <h2 className="text-xl font-semibold text-white mb-2">Analyze Dataset</h2>
        <p className="text-gray-300 mb-4">
          Perform analysis on the Constitution of India data to discover patterns and insights.
        </p>
      </div>

      <div className="glass-card bg-blue-900/30 p-4 rounded-lg mb-6">
        <h3 className="text-lg font-medium text-white mb-2">Dataset Information</h3>
        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
          <div>
            <p className="text-sm text-gray-200">
              <span className="font-medium">Rows:</span> {datasetInfo.rows}
            </p>
            <p className="text-sm text-gray-200">
              <span className="font-medium">Columns:</span> {datasetInfo.columns.join(', ')}
            </p>
          </div>
          <div>
            <p className="text-sm text-gray-200">
              <span className="font-medium">Status:</span> {datasetInfo.success ? 'Ready for analysis' : 'Error loading data'}
            </p>
          </div>
        </div>
      </div>

      <div className="glass-panel rounded-lg p-4 mb-6">
        <h3 className="text-lg font-medium text-white mb-3">Analysis Configuration</h3>
        
        <div className="mb-4">
          <label htmlFor="clusterCount" className="block text-sm font-medium text-gray-200 mb-1">
            Number of Clusters
          </label>
          <div className="flex items-center space-x-3">
            <input
              type="range"
              id="clusterCount"
              min="2"
              max="10"
              step="1"
              value={clusterCount}
              onChange={(e) => setClusterCount(parseInt(e.target.value))}
              disabled={isAnalyzing}
              className="flex-1"
            />
            <span className="text-gray-200 font-medium">{clusterCount}</span>
          </div>
          <p className="mt-1 text-sm text-gray-300">
            Choose how many thematic groups to divide the Constitution articles into.
          </p>
        </div>

        {analysisError && (
          <div className="bg-red-900/30 text-red-200 p-3 rounded-md text-sm mb-4 border border-red-800/40">
            {analysisError}
          </div>
        )}

        {isAnalyzing && (
          <div className="mb-4">
            <div className="h-2 bg-slate-700/50 rounded-full overflow-hidden">
              <div
                className="h-full bg-sky-600/70 transition-all duration-300"
                style={{ width: `${analyzeProgress}%` }}
              ></div>
            </div>
            <div className="mt-2 text-sm text-gray-300 flex justify-between items-center">
              <span>{currentStep}</span>
              <span>{Math.round(analyzeProgress)}%</span>
            </div>
          </div>
        )}

        <button
          onClick={handleStartAnalysis}
          disabled={isAnalyzing}
          className={`w-full px-4 py-2 text-sm font-medium rounded-md text-white ${
            isAnalyzing
              ? 'bg-slate-700/50 cursor-not-allowed'
              : 'glass-primary-button'
          }`}
        >
          {isAnalyzing ? 'Analyzing...' : 'Analyze Dataset'}
        </button>
      </div>

      <div className="glass-panel p-4 rounded-lg">
        <h3 className="text-lg font-medium text-white mb-3">What happens during analysis?</h3>
        <ol className="list-decimal list-inside text-gray-300 space-y-2">
          <li>Text is processed and cleaned to extract meaningful words</li>
          <li>TF-IDF vectorization converts text to numerical features</li>
          <li>K-means clustering groups similar articles together</li>
          <li>Dimensionality reduction helps visualize the patterns</li>
          <li>Word frequencies show key terms in each cluster</li>
        </ol>
      </div>

      {datasetInfo.sample && datasetInfo.sample.length > 0 && (
        <div className="mt-6 glass-panel rounded-lg overflow-x-auto">
          <h3 className="text-lg font-medium text-white mb-3">Sample Data</h3>
          <div className="overflow-x-auto">
            <table className="min-w-full divide-y divide-slate-700/30">
              <thead className="bg-slate-800/50">
                <tr>
                  {Object.keys(datasetInfo.sample[0])
                    .filter(key => key !== 'Processed_Text') // Skip processed text column
                    .map((key) => (
                      <th
                        key={key}
                        scope="col"
                        className="px-6 py-3 text-left text-xs font-medium text-gray-300 uppercase tracking-wider"
                      >
                        {key}
                      </th>
                    ))}
                </tr>
              </thead>
              <tbody className="divide-y divide-slate-700/30">
                {datasetInfo.sample.map((row, rowIndex) => (
                  <tr key={rowIndex}>
                    {Object.entries(row)
                      .filter(([key]) => key !== 'Processed_Text') // Skip processed text column
                      .map(([key, value]) => (
                        <td key={key} className="px-6 py-4 whitespace-nowrap text-sm text-gray-300">
                          {typeof value === 'string' 
                            ? value.length > 100 ? value.substring(0, 100) + '...' : value
                            : String(value)
                          }
                        </td>
                      ))}
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </div>
      )}
    </div>
  );
} 