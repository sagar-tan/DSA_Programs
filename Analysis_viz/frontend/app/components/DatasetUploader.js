'use client';

import { useState } from 'react';

export default function DatasetUploader({ onDatasetUploaded, apiStatus }) {
  const [file, setFile] = useState(null);
  const [isUploading, setIsUploading] = useState(false);
  const [uploadError, setUploadError] = useState(null);
  const [uploadProgress, setUploadProgress] = useState(0);

  const handleFileChange = (e) => {
    const selectedFile = e.target.files[0];
    if (selectedFile && selectedFile.name.endsWith('.csv')) {
      setFile(selectedFile);
      setUploadError(null);
    } else {
      setFile(null);
      setUploadError('Please select a valid CSV file');
    }
  };

  const simulateProgress = () => {
    // Simulate upload progress for better UX
    setUploadProgress(0);
    const interval = setInterval(() => {
      setUploadProgress((prev) => {
        const newProgress = prev + Math.random() * 10;
        return newProgress >= 90 ? 90 : newProgress; // Cap at 90% until actual completion
      });
    }, 300);
    return interval;
  };

  const handleUpload = async () => {
    if (!file && !useDefault) {
      setUploadError('Please select a file or use the default dataset');
      return;
    }

    setIsUploading(true);
    setUploadError(null);
    
    const progressInterval = simulateProgress();
    
    try {
      const formData = new FormData();
      if (file) {
        formData.append('file', file);
      } else {
        formData.append('useDefault', 'true');
      }

      const response = await fetch('http://127.0.0.1:5000/api/dataset/upload', {
        method: 'POST',
        body: formData,
      });

      clearInterval(progressInterval);
      
      if (!response.ok) {
        const errorData = await response.json();
        throw new Error(errorData.message || 'Failed to upload dataset');
      }

      const data = await response.json();
      setUploadProgress(100);
      
      setTimeout(() => {
        onDatasetUploaded(data);
        setIsUploading(false);
      }, 500);
      
    } catch (error) {
      clearInterval(progressInterval);
      setUploadError(error.message || 'An error occurred while uploading the dataset');
      setIsUploading(false);
      setUploadProgress(0);
    }
  };

  const handleUseDefault = async () => {
    setFile(null);
    setIsUploading(true);
    setUploadError(null);
    
    const progressInterval = simulateProgress();
    
    try {
      const formData = new FormData();
      formData.append('useDefault', 'true');

      const response = await fetch('http://127.0.0.1:5000/api/dataset/upload', {
        method: 'POST',
        body: formData,
      });

      clearInterval(progressInterval);
      
      if (!response.ok) {
        const errorData = await response.json();
        throw new Error(errorData.message || 'Failed to load default dataset');
      }

      const data = await response.json();
      setUploadProgress(100);
      
      setTimeout(() => {
        onDatasetUploaded(data);
        setIsUploading(false);
      }, 500);
      
    } catch (error) {
      clearInterval(progressInterval);
      setUploadError(error.message || 'An error occurred while loading the default dataset');
      setIsUploading(false);
      setUploadProgress(0);
    }
  };

  if (apiStatus.status !== 'connected') {
    return (
      <div className="text-center py-8">
        <div className="text-red-400 mb-4">
          <svg className="w-12 h-12 mx-auto" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M12 8v4m0 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
        </div>
        <h2 className="text-xl font-semibold text-gray-200 mb-2">API Connection Error</h2>
        <p className="text-gray-300 mb-4">{apiStatus.message}</p>
        <p className="text-gray-400">Please start the backend server and try again.</p>
      </div>
    );
  }

  return (
    <div className="max-w-xl mx-auto">
      <div>
        <h2 className="text-xl font-semibold text-gray-200 mb-3">Upload Dataset</h2>
        <p className="text-gray-300 mb-4">
          Upload a CSV file containing the Constitution of India data for analysis.
        </p>

        <div className="glass-panel rounded-lg p-5 mb-4 text-center">
          <input
            type="file"
            accept=".csv"
            onChange={handleFileChange}
            className="hidden"
            id="file-upload"
            disabled={isUploading}
          />
          <label
            htmlFor="file-upload"
            className={`inline-flex items-center px-4 py-2 text-sm font-medium rounded-md text-white ${
              isUploading ? 'bg-slate-700/50 cursor-not-allowed' : 'glass-button cursor-pointer'
            }`}
          >
            Select CSV File
          </label>
          {file && (
            <div className="mt-3 text-sm text-gray-300">
              Selected file: <span className="font-medium">{file.name}</span>
            </div>
          )}
        </div>

        {uploadError && (
          <div className="bg-red-900/30 text-red-200 p-3 rounded-md text-sm mb-4 border border-red-800/40">
            {uploadError}
          </div>
        )}

        {isUploading && (
          <div className="mb-4">
            <div className="h-1.5 bg-slate-800/50 rounded-full overflow-hidden">
              <div
                className="h-full bg-sky-600/70 transition-all duration-300"
                style={{ width: `${uploadProgress}%` }}
              ></div>
            </div>
            <div className="mt-2 text-xs text-gray-400 text-center">
              {uploadProgress < 100 
                ? 'Processing dataset...' 
                : 'Dataset processed successfully!'}
            </div>
          </div>
        )}

        <div className="flex space-x-3">
          <button
            onClick={handleUpload}
            disabled={isUploading || (!file && false)}
            className={`flex-1 px-4 py-2 text-sm font-medium rounded-md text-white ${
              isUploading || (!file && false)
                ? 'bg-slate-700/50 cursor-not-allowed'
                : 'glass-success-button'
            }`}
          >
            {isUploading ? 'Processing...' : 'Upload & Process'}
          </button>
          
          <button
            onClick={handleUseDefault}
            disabled={isUploading}
            className={`flex-1 px-4 py-2 text-sm font-medium rounded-md text-white ${
              isUploading
                ? 'bg-slate-700/50 cursor-not-allowed'
                : 'glass-primary-button'
            }`}
          >
            Use Default Dataset
          </button>
        </div>
      </div>

      <div className="border-t border-slate-700/30 pt-4 mt-6">
        <h3 className="text-base font-medium text-gray-200 mb-2">What happens next?</h3>
        <ul className="space-y-1 text-sm text-gray-300">
          <li>• Dataset processing and feature extraction</li>
          <li>• Clustering of similar articles</li>
          <li>• Visualization of patterns and relationships</li>
          <li>• Search capabilities through the Constitution</li>
        </ul>
      </div>
    </div>
  );
} 