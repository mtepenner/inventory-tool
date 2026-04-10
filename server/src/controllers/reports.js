const db = require('../config/database');
const { Parser } = require('json2csv');
const { generateReportFilename } = require('../utils/dateHelpers');

exports.exportInventoryReport = (req, res) => {
    const sql = 'SELECT * FROM inventory ORDER BY location ASC';
    
    db.all(sql, [], (err, rows) => {
        if (err) {
            return res.status(500).json({ error: 'Failed to fetch data for report' });
        }

        try {
            // Fields map exactly to your database columns
            const fields = [
                'ipn', 'location', 'quantity', 'full_date_code', 'date_code_year_only', 
                'cycle_count_date', 'additional_notes', 'owner', 'coo', 'mfr', 
                'mpn', 'description', 'product_category', 'product_type', 'pricing'
            ];
            
            const json2csvParser = new Parser({ fields });
            const csv = json2csvParser.parse(rows);
            const fileName = generateReportFilename();

            res.header('Content-Type', 'text/csv');
            res.attachment(fileName);
            return res.send(csv);
            
        } catch (error) {
            console.error('CSV Generation Error:', error);
            res.status(500).send('Error generating report');
        }
    });
};
