# 📦 Full-Stack Inventory Management System

A full-stack web application designed to efficiently track hardware components (specifically structured around Intel Part Numbers), manage stock quantities, log part locations, and maintain detailed metadata such as product categories, owners, and pricing. 

This project is a modernized version of a legacy C++ command-line tool, now featuring a React frontend, a Node.js API, and a robust SQLite database.

## ✨ Features

* **Modern Web Interface:** A responsive React dashboard to view, add, and manage inventory seamlessly.
* **Add & Edit Parts:** Input new inventory items with detailed metadata (Location, Date Codes, Manufacturer, Description, etc.) through an intuitive modal form.
* **Dynamic CSV Reporting:** Generate and download custom inventory reports formatted automatically as `[mm-dd-yyyy]-WW[ww#]-inventory-report.csv`.
* **Persistent Relational Storage:** Utilizes a local SQLite database for structured data integrity and lightning-fast queries.
* **Legacy Migration Ready:** Includes a migration script to effortlessly transfer data from legacy `InventoryData.txt` files into the new database.

## 🛠️ Tech Stack

**Frontend (Client)**
* React.js (via Vite)
* Tailwind CSS (Styling)
* Axios (API Communication)

**Backend (Server)**
* Node.js & Express.js (REST API)
* SQLite3 (Database)
* date-fns & json2csv (Report Formatting)

## 📂 Project Structure

The repository is split into two distinct environments:

```text
inventory-app/
├── client/                     # React Frontend
│   ├── src/
│   │   ├── api/                # Axios API calls
│   │   ├── components/         # Reusable UI (Navbar, DataTable, PartModal)
│   │   ├── pages/              # Main view (Dashboard)
│   │   └── App.jsx             
│   └── package.json            
│
├── server/                     # Node.js Backend
│   ├── src/
│   │   ├── controllers/        # Route logic (inventory, reports)
│   │   ├── routes/             # API endpoint definitions
│   │   ├── config/             # SQLite connection setup
│   │   ├── utils/              # Helper functions (date generation)
│   │   └── server.js           # Express app entry point
│   ├── database/               # Auto-generated SQLite file
│   └── package.json            
```

## 🚀 Installation & Setup

Ensure you have Node.js installed. You will need to run the client and the server in two separate terminal windows.

### 1. Start the Backend Server
```bash
cd server
npm install
npm run dev
```
*The server will run on `http://localhost:5000` and automatically generate the SQLite database file on first run.*

### 2. Start the Frontend Client
```bash
cd client
npm install
npm run dev
```
*The client will typically run on `http://localhost:5173`. Open this URL in your browser to use the application.*

## 📦 Data Migration

If you are upgrading from the older C++ version of this tool, you can migrate your existing `InventoryData.txt` file directly into the new SQLite database.

1. Place your `InventoryData.txt` file in the root of the `server/` directory.
2. Run the migration script:
   ```bash
   node migrate.js
   ```
3. Your legacy data is now available in the web dashboard!

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

1. Fork the project.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

