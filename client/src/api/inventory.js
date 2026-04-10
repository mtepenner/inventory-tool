import axios from 'axios';

const API_URL = 'http://localhost:5000/api'; // Adjust this to match your backend port

export const getInventory = async () => {
    const response = await axios.get(`${API_URL}/inventory`);
    return response.data;
};

export const addPart = async (partData) => {
    const response = await axios.post(`${API_URL}/inventory`, partData);
    return response.data;
};

export const deletePart = async (ipn) => {
    const response = await axios.delete(`${API_URL}/inventory/${ipn}`);
    return response.data;
};

export const downloadInventoryReport = async () => {
    // This expects the backend to return a file attachment
    const response = await axios.get(`${API_URL}/reports/inventory`, {
        responseType: 'blob', 
    });
    
    // Create a temporary link to trigger the browser download
    const url = window.URL.createObjectURL(new Blob([response.data]));
    const link = document.createElement('a');
    link.href = url;
    
    // Attempt to extract filename from content-disposition header, fallback if not present
    const contentDisposition = response.headers['content-disposition'];
    let fileName = 'inventory-report.csv';
    if (contentDisposition) {
        const fileNameMatch = contentDisposition.match(/filename="?([^"]+)"?/);
        if (fileNameMatch && fileNameMatch.length === 2) {
            fileName = fileNameMatch[1];
        }
    }
    
    link.setAttribute('download', fileName);
    document.body.appendChild(link);
    link.click();
    link.remove();
};
