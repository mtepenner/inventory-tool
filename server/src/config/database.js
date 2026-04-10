const sqlite3 = require('sqlite3').verbose();
const path = require('path');

// Connect to the SQLite database (creates the file if it doesn't exist)
const dbPath = path.resolve(__dirname, '../../database/inventory.sqlite');
const db = new sqlite3.Database(dbPath, (err) => {
    if (err) {
        console.error('Error connecting to SQLite database:', err.message);
    } else {
        console.log('📦 Connected to the SQLite database.');
        
        // Create the inventory table if it doesn't exist
        db.run(`CREATE TABLE IF NOT EXISTS inventory (
            ipn TEXT PRIMARY KEY,
            location TEXT,
            quantity INTEGER DEFAULT 0,
            full_date_code TEXT,
            date_code_year_only TEXT,
            cycle_count_date TEXT,
            additional_notes TEXT,
            owner TEXT,
            coo TEXT,
            mfr TEXT,
            mpn TEXT,
            description TEXT,
            product_category TEXT,
            product_type TEXT,
            pricing REAL DEFAULT 0.0
        )`, (err) => {
            if (err) {
                console.error('Error creating table:', err.message);
            }
        });
    }
});

module.exports = db;
