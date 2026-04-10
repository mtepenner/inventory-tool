const db = require('../config/database');

// GET all inventory items
exports.getInventory = (req, res) => {
    const sql = 'SELECT * FROM inventory ORDER BY location ASC';
    db.all(sql, [], (err, rows) => {
        if (err) {
            return res.status(500).json({ error: err.message });
        }
        res.json(rows);
    });
};

// POST a new part
exports.addPart = (req, res) => {
    const {
        ipn, location, quantity, full_date_code, date_code_year_only,
        cycle_count_date, additional_notes, owner, coo, mfr, mpn,
        description, product_category, product_type, pricing
    } = req.body;

    const sql = `INSERT INTO inventory (
        ipn, location, quantity, full_date_code, date_code_year_only, 
        cycle_count_date, additional_notes, owner, coo, mfr, mpn, 
        description, product_category, product_type, pricing
    ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)`;

    const params = [
        ipn, location, quantity, full_date_code, date_code_year_only,
        cycle_count_date, additional_notes, owner, coo, mfr, mpn,
        description, product_category, product_type, pricing
    ];

    db.run(sql, params, function(err) {
        if (err) {
            return res.status(400).json({ error: err.message });
        }
        res.status(201).json({ message: 'Part added successfully', ipn: ipn });
    });
};

// DELETE a part
exports.deletePart = (req, res) => {
    const { ipn } = req.params;
    const sql = 'DELETE FROM inventory WHERE ipn = ?';
    
    db.run(sql, ipn, function(err) {
        if (err) {
            return res.status(500).json({ error: err.message });
        }
        res.json({ message: 'Part deleted successfully', changes: this.changes });
    });
};
