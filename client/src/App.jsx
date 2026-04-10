import React from 'react';
import Dashboard from './pages/Dashboard';
import Navbar from './components/Navbar';

function App() {
  return (
    <div className="min-h-screen bg-gray-100 text-gray-900 font-sans">
      <Navbar />
      <div className="p-6">
        <Dashboard />
      </div>
    </div>
  );
}

export default App;
