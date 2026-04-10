import React, { useState } from 'react';
import { addPart } from '../api/inventory';

const PartModal = ({ onClose, onSuccess }) => {
    const [formData, setFormData] = useState({
        ipn: '',
        location: '',
        quantity: 0,
        description: '',
        owner: '',
        product_category: '',
        product_type: '',
        pricing: 0.0
    });

    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData({ ...formData, [name]: value });
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            await addPart(formData);
            onSuccess();
        } catch (error) {
            console.error("Failed to add part:", error);
            alert("Error adding part. Ensure IPN is unique.");
        }
    };

    return (
        <div className="fixed inset-0 bg-black bg-opacity-50 flex justify-center items-center p-4">
            <div className="bg-white rounded-lg shadow-xl w-full max-w-md p-6">
                <h2 className="text-2xl font-bold mb-4">Add New Part</h2>
                
                <form onSubmit={handleSubmit} className="space-y-4">
                    <div>
                        <label className="block text-sm font-medium text-gray-700">Intel Part Number (IPN)</label>
                        <input required type="text" name="ipn" onChange={handleChange} className="mt-1 w-full border border-gray-300 p-2 rounded" />
                    </div>
                    
                    <div className="flex gap-4">
                        <div className="flex-1">
                            <label className="block text-sm font-medium text-gray-700">Location</label>
                            <input required type="text" name="location" onChange={handleChange} className="mt-1 w-full border border-gray-300 p-2 rounded" />
                        </div>
                        <div className="w-24">
                            <label className="block text-sm font-medium text-gray-700">Quantity</label>
                            <input required type="number" name="quantity" onChange={handleChange} className="mt-1 w-full border border-gray-300 p-2 rounded" />
                        </div>
                    </div>

                    <div>
                        <label className="block text-sm font-medium text-gray-700">Description</label>
                        <input type="text" name="description" onChange={handleChange} className="mt-1 w-full border border-gray-300 p-2 rounded" />
                    </div>

                    <div className="flex gap-4">
                        <div className="flex-1">
                            <label className="block text-sm font-medium text-gray-700">Owner</label>
                            <input type="text" name="owner" onChange={handleChange} className="mt-1 w-full border border-gray-300 p-2 rounded" />
                        </div>
                        <div className="w-32">
                            <label className="block text-sm font-medium text-gray-700">Pricing ($)</label>
                            <input type="number" step="0.01" name="pricing" onChange={handleChange} className="mt-1 w-full border border-gray-300 p-2 rounded" />
                        </div>
                    </div>

                    <div className="pt-4 flex justify-end space-x-2 border-t">
                        <button type="button" onClick={onClose} className="px-4 py-2 text-gray-600 border border-gray-300 rounded hover:bg-gray-100">
                            Cancel
                        </button>
                        <button type="submit" className="px-4 py-2 bg-blue-600 text-white rounded hover:bg-blue-700">
                            Save Part
                        </button>
                    </div>
                </form>
            </div>
        </div>
    );
};

export default PartModal;
