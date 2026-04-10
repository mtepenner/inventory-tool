import React from 'react';

const DataTable = ({ data, onDelete }) => {
    if (!data || data.length === 0) {
        return <p className="text-center text-gray-500 py-4">No inventory data found.</p>;
    }

    return (
        <table className="w-full text-left border-collapse">
            <thead>
                <tr className="border-b bg-gray-50">
                    <th className="p-3">IPN</th>
                    <th className="p-3">Location</th>
                    <th className="p-3">Qty</th>
                    <th className="p-3">Description</th>
                    <th className="p-3">Owner</th>
                    <th className="p-3">Price</th>
                    <th className="p-3 text-center">Actions</th>
                </tr>
            </thead>
            <tbody>
                {data.map((item) => (
                    <tr key={item.ipn} className="border-b hover:bg-gray-50">
                        <td className="p-3 font-medium">{item.ipn}</td>
                        <td className="p-3">{item.location}</td>
                        <td className="p-3">{item.quantity}</td>
                        <td className="p-3 truncate max-w-xs">{item.description}</td>
                        <td className="p-3">{item.owner}</td>
                        <td className="p-3">${item.pricing}</td>
                        <td className="p-3 text-center">
                            <button 
                                onClick={() => onDelete(item.ipn)}
                                className="text-red-500 hover:underline"
                            >
                                Delete
                            </button>
                        </td>
                    </tr>
                ))}
            </tbody>
        </table>
    );
};

export default DataTable;
