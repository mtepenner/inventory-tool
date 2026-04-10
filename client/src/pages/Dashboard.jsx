import React, { useState, useEffect } from 'react';
import { getInventory, deletePart, downloadInventoryReport } from '../api/inventory';
import DataTable from '../components/DataTable';
import PartModal from '../components/PartModal';

const Dashboard = () => {
    const [inventory, setInventory] = useState([]);
    const [isModalOpen, setIsModalOpen] = useState(false);

    const fetchInventory = async () => {
        try {
            const data = await getInventory();
            setInventory(data);
        } catch (error) {
            console.error("Failed to fetch inventory:", error);
        }
    };

    useEffect(() => {
        fetchInventory();
    }, []);

    const handleDelete = async (ipn) => {
        if (window.confirm(`Are you sure you want to delete part ${ipn}?`)) {
            try {
                await deletePart(ipn);
                fetchInventory(); // Refresh list
            } catch (error) {
                console.error("Failed to delete part:", error);
            }
        }
    };

    const handleExport = async () => {
        try {
            await downloadInventoryReport();
        } catch (error) {
            console.error("Failed to download report:", error);
        }
    };

    return (
        <div className="max-w-7xl mx-auto">
            <header className="flex justify-between items-center mb-6">
                <h1 className="text-3xl font-bold">📦 Inventory Management</h1>
                <div className="space-x-4">
                    <button 
                        onClick={handleExport}
                        className="bg-green-600 text-white px-4 py-2 rounded shadow hover:bg-green-700"
                    >
                        Export Report
                    </button>
                    <button 
                        onClick={() => setIsModalOpen(true)}
                        className="bg-blue-600 text-white px-4 py-2 rounded shadow hover:bg-blue-700"
                    >
                        + Add Part
                    </button>
                </div>
            </header>

            <main className="bg-white rounded shadow p-4 overflow-x-auto">
                <DataTable data={inventory} onDelete={handleDelete} />
            </main>

            {isModalOpen && (
                <PartModal 
                    onClose={() => setIsModalOpen(false)} 
                    onSuccess={() => {
                        setIsModalOpen(false);
                        fetchInventory();
                    }}
                />
            )}
        </div>
    );
};

export default Dashboard;
