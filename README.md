# 📦 Postgrad Inventory Management System

A lightweight, command-line-based Inventory Management System built in C++. This tool is designed to efficiently track hardware components (specifically structured around Intel Part Numbers), manage stock quantities, log part locations, and maintain detailed metadata such as product categories, owners, and pricing. 

The system uses local text files for persistent data storage and dynamically loads product categories from a relational CSV file.

## 📑 Table of Contents
- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [Usage](#-usage)
- [Contributing](#-contributing)

## 🚀 Features

- **Add New Parts:** Easily input new inventory items with detailed metadata (Location, Date Codes, Manufacturer, Description, etc.).
- **Dynamic Categorization:** Reads product categories and types from a `DropDownWithRelation.csv` file to ensure standardized data entry.
- **Stock Management:** Quickly deduct part quantities as they are consumed without recreating the entry.
- **Part Modification:** Append additional notes or change the assigned owner of existing parts.
- **Locate Parts:** Search for a specific component using its Intel Part Number to retrieve its location, description, and pricing details.
- **Persistent Storage:** Automatically saves and alphabetizes inventory data (by Location) to `InventoryData.txt`.

## 🛠️ Technologies Used

- **Language:** C++ (Standard Template Library)
- **Data Storage:** Flat-file storage (`.txt` delimited by `|` and `.csv`)

## 📂 Project Structure

Ensure the following files are in the same directory for the program to function properly:

- `inventory_mgmt.cpp`: The main C++ source code.
- `InventoryData.txt`: The text file where inventory data is stored persistently (automatically generated/updated).
- `DropDownWithRelation.csv`: A CSV file containing headers (Categories) and columns of respective item Types used during part creation.

## 💻 Installation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/postgrad-inventory-tool.git](https://github.com/your-username/postgrad-inventory-tool.git)
   cd postgrad-inventory-tool
   ```

2. **Compile the code:**
   You can compile the application using any standard C++ compiler like `g++`:
   ```bash
   g++ -o inventory_tool inventory_mgmt.cpp
   ```

3. **Set up data files:**
   Ensure `DropDownWithRelation.csv` is present in your working directory. If it is missing, the program will gracefully fall back to manual text entry for Categories and Types.

## 🕹️ Usage

Run the compiled executable from your terminal:

```bash
./inventory_tool
```

You will be greeted with the main menu:
```text
=========================================
       INVENTORY MANAGEMENT SYSTEM       
=========================================
1. Add a part to inventory
2. Deduct a part quantity
3. Delete a part
4. Add notes to existing parts
5. Locate a part
6. Change part owner
7. Exit
Enter your choice: 
```

Simply type the number corresponding to the action you wish to perform and follow the on-screen prompts.

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! 

1. Fork the project.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.
