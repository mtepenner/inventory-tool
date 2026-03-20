#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// Structure to hold all part information
struct Part {
    string IntelPartNumber;
    string Location;
    int Quantity;
    string FullDateCode;
    string DateCodeYearOnly;
    string CycleCountDate;
    string AdditionalNotes;
    string Owner;
    string CountryOfOrigin;
    string Manufacturer;
    string ManufacturerPartNumber;
    string Description;
    string ProductCategory;
    string ProductType;
    double Pricing;
};

// Structure for Dropdown relationships
struct CategoryInfo {
    string name;
    vector<string> types;
};

// Global Data
vector<Part> inventory;
vector<CategoryInfo> categoriesDB;

const string INV_FILENAME = "InventoryData.txt";
const string DROPDOWN_FILENAME = "DropDownWithRelation.csv";
const char DELIMITER = '|';

// Function prototypes
void loadInventory();
void saveInventory();
void loadDropdowns();
vector<string> parseCSVLine(const string& line);
void addPart();
void deductQuantity();
void deletePart();
void addNotes();
void locatePart();
void changeOwner();
int findPartIndex(const string& partNum);
void clearInputBuffer();

int main() {
    loadDropdowns();
    loadInventory();
    int choice = 0;

    while (choice != 7) {
        cout << "\n=========================================\n";
        cout << "       INVENTORY MANAGEMENT SYSTEM       \n";
        cout << "=========================================\n";
        cout << "1. Add a part to inventory\n";
        cout << "2. Deduct a part quantity\n";
        cout << "3. Delete a part\n";
        cout << "4. Add notes to existing parts\n";
        cout << "5. Locate a part\n";
        cout << "6. Change part owner\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addPart(); break;
            case 2: deductQuantity(); break;
            case 3: deletePart(); break;
            case 4: addNotes(); break;
            case 5: locatePart(); break;
            case 6: changeOwner(); break;
            case 7: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

// Helper function to clear standard input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Parses a CSV line handling quotes and commas inside quotes
vector<string> parseCSVLine(const string& line) {
    vector<string> result;
    string current = "";
    bool inQuotes = false;
    
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            inQuotes = !inQuotes; // Toggle quote state
        } else if (c == ',' && !inQuotes) {
            result.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    result.push_back(current);
    return result;
}

// Loads Categories and Types from DropDownWithRelation.csv
void loadDropdowns() {
    ifstream file(DROPDOWN_FILENAME);
    if (!file.is_open()) {
        cout << "Warning: Could not open " << DROPDOWN_FILENAME << ". Category/Type selection will be skipped or manual.\n";
        return;
    }

    string line;
    // Skip the first row ("DO NOT USE THIS PAGE...")
    getline(file, line);
    
    // Read the second row (Headers / Categories)
    if (getline(file, line)) {
        vector<string> headers = parseCSVLine(line);
        for (const string& h : headers) {
            CategoryInfo ci;
            ci.name = h;
            categoriesDB.push_back(ci);
        }
    }

    // Read subsequent rows (Types belonging to Categories)
    while (getline(file, line)) {
        if (line.empty() || line.find_first_not_of(',') == string::npos) continue; // Skip empty rows

        vector<string> types = parseCSVLine(line);
        for (size_t i = 0; i < types.size() && i < categoriesDB.size(); ++i) {
            // Trim whitespace and check if empty
            string t = types[i];
            t.erase(t.find_last_not_of(" \n\r\t") + 1);
            if (!t.empty()) {
                categoriesDB[i].types.push_back(t);
            }
        }
    }
    file.close();
}

// Sorts inventory alphabetically by Location and saves to the text file
void saveInventory() {
    sort(inventory.begin(), inventory.end(), [](const Part& a, const Part& b) {
        return a.Location < b.Location;
    });

    ofstream file(INV_FILENAME);
    if (!file.is_open()) {
        cout << "Error opening file for writing!\n";
        return;
    }

    for (const auto& p : inventory) {
        file << p.IntelPartNumber << DELIMITER
             << p.Location << DELIMITER
             << p.Quantity << DELIMITER
             << p.FullDateCode << DELIMITER
             << p.DateCodeYearOnly << DELIMITER
             << p.CycleCountDate << DELIMITER
             << p.AdditionalNotes << DELIMITER
             << p.Owner << DELIMITER
             << p.CountryOfOrigin << DELIMITER
             << p.Manufacturer << DELIMITER
             << p.ManufacturerPartNumber << DELIMITER
             << p.Description << DELIMITER
             << p.ProductCategory << DELIMITER
             << p.ProductType << DELIMITER
             << p.Pricing << "\n";
    }
    file.close();
}

// Loads inventory from the text file into the vector
void loadInventory() {
    ifstream file(INV_FILENAME);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string item;
        Part p;

        getline(ss, p.IntelPartNumber, DELIMITER);
        getline(ss, p.Location, DELIMITER);
        
        getline(ss, item, DELIMITER);
        p.Quantity = item.empty() ? 0 : stoi(item);
        
        getline(ss, p.FullDateCode, DELIMITER);
        getline(ss, p.DateCodeYearOnly, DELIMITER);
        getline(ss, p.CycleCountDate, DELIMITER);
        getline(ss, p.AdditionalNotes, DELIMITER);
        getline(ss, p.Owner, DELIMITER);
        getline(ss, p.CountryOfOrigin, DELIMITER);
        getline(ss, p.Manufacturer, DELIMITER);
        getline(ss, p.ManufacturerPartNumber, DELIMITER);
        getline(ss, p.Description, DELIMITER);
        getline(ss, p.ProductCategory, DELIMITER);
        getline(ss, p.ProductType, DELIMITER);
        
        getline(ss, item, DELIMITER);
        p.Pricing = item.empty() ? 0.0 : stod(item);

        inventory.push_back(p);
    }
    file.close();
}

int findPartIndex(const string& partNum) {
    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i].IntelPartNumber == partNum) return i;
    }
    return -1;
}

// 1. Add a part to inventory (Updated with Dropdown Logic)
void addPart() {
    Part p;
    clearInputBuffer();
    
    cout << "\n--- Add New Part ---\n";
    cout << "Intel Part Number: "; getline(cin, p.IntelPartNumber);
    
    if (findPartIndex(p.IntelPartNumber) != -1) {
        cout << "Part already exists! Consider deducting or adding to quantity instead.\n";
        return;
    }

    cout << "Location: "; getline(cin, p.Location);
    cout << "Quantity: "; cin >> p.Quantity; clearInputBuffer();
    cout << "Full Date Code(s): "; getline(cin, p.FullDateCode);
    cout << "Date Code Year Only: "; getline(cin, p.DateCodeYearOnly);
    cout << "Cycle Count Date: "; getline(cin, p.CycleCountDate);
    cout << "Additional Notes: "; getline(cin, p.AdditionalNotes);
    cout << "Owner: "; getline(cin, p.Owner);
    cout << "Country of Origin: "; getline(cin, p.CountryOfOrigin);
    cout << "Manufacturer: "; getline(cin, p.Manufacturer);
    cout << "Manufacturer Part Number: "; getline(cin, p.ManufacturerPartNumber);
    cout << "Description: "; getline(cin, p.Description);
    
    // --- DROPDOWN SELECTION LOGIC ---
    if (!categoriesDB.empty()) {
        int catChoice = 0;
        while (true) {
            cout << "\n--- Select Product Category ---\n";
            for (size_t i = 0; i < categoriesDB.size(); ++i) {
                if (!categoriesDB[i].name.empty()) {
                    cout << i + 1 << ". " << categoriesDB[i].name << "\n";
                }
            }
            cout << "Enter category number: ";
            if (cin >> catChoice && catChoice > 0 && catChoice <= categoriesDB.size()) {
                p.ProductCategory = categoriesDB[catChoice - 1].name;
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            cout << "Invalid choice. Try again.\n";
        }

        int typeChoice = 0;
        int targetCatIndex = catChoice - 1;
        while (true) {
            cout << "\n--- Select Product Type for '" << p.ProductCategory << "' ---\n";
            if (categoriesDB[targetCatIndex].types.empty()) {
                cout << "No specific types found for this category. Press Enter to skip.\n";
                getline(cin, p.ProductType);
                break;
            }
            for (size_t i = 0; i < categoriesDB[targetCatIndex].types.size(); ++i) {
                cout << i + 1 << ". " << categoriesDB[targetCatIndex].types[i] << "\n";
            }
            cout << "Enter type number: ";
            if (cin >> typeChoice && typeChoice > 0 && typeChoice <= categoriesDB[targetCatIndex].types.size()) {
                p.ProductType = categoriesDB[targetCatIndex].types[typeChoice - 1];
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            cout << "Invalid choice. Try again.\n";
        }
    } else {
        // Fallback if CSV is missing
        cout << "Product Category: "; getline(cin, p.ProductCategory);
        cout << "Product Type: "; getline(cin, p.ProductType);
    }
    // --------------------------------

    cout << "Pricing: $"; cin >> p.Pricing; clearInputBuffer();

    inventory.push_back(p);
    saveInventory();
    cout << "Part added and inventory saved successfully!\n";
}

// 2. Deduct a part quantity
void deductQuantity() {
    clearInputBuffer();
    string partNum;
    cout << "\n--- Deduct Quantity ---\n";
    cout << "Enter Intel Part Number: ";
    getline(cin, partNum);

    int index = findPartIndex(partNum);
    if (index == -1) {
        cout << "Part not found.\n";
        return;
    }

    int deductAmt;
    cout << "Current Quantity: " << inventory[index].Quantity << "\n";
    cout << "Amount to deduct: ";
    cin >> deductAmt; clearInputBuffer();

    if (deductAmt > inventory[index].Quantity) {
        cout << "Error: Cannot deduct more than current inventory.\n";
    } else {
        inventory[index].Quantity -= deductAmt;
        saveInventory();
        cout << "Quantity updated. New Quantity: " << inventory[index].Quantity << "\n";
    }
}

// 3. Delete a part
void deletePart() {
    clearInputBuffer();
    string partNum;
    cout << "\n--- Delete Part ---\n";
    cout << "Enter Intel Part Number to delete: ";
    getline(cin, partNum);

    int index = findPartIndex(partNum);
    if (index == -1) {
        cout << "Part not found.\n";
        return;
    }

    inventory.erase(inventory.begin() + index);
    saveInventory();
    cout << "Part successfully deleted.\n";
}

// 4. Add notes to existing parts
void addNotes() {
    clearInputBuffer();
    string partNum;
    cout << "\n--- Add Notes ---\n";
    cout << "Enter Intel Part Number: ";
    getline(cin, partNum);

    int index = findPartIndex(partNum);
    if (index == -1) {
        cout << "Part not found.\n";
        return;
    }

    string newNote;
    cout << "Current Notes: " << inventory[index].AdditionalNotes << "\n";
    cout << "Enter note to append: ";
    getline(cin, newNote);

    if (inventory[index].AdditionalNotes.empty()) {
        inventory[index].AdditionalNotes = newNote;
    } else {
        inventory[index].AdditionalNotes += " | " + newNote;
    }
    
    saveInventory();
    cout << "Notes updated successfully.\n";
}

// 5. Locate a part
void locatePart() {
    clearInputBuffer();
    string partNum;
    cout << "\n--- Locate Part ---\n";
    cout << "Enter Intel Part Number: ";
    getline(cin, partNum);

    int index = findPartIndex(partNum);
    if (index == -1) {
        cout << "Part not found in inventory.\n";
        return;
    }

    cout << "\n--- Part Details ---\n";
    cout << "Location: " << inventory[index].Location << "\n";
    cout << "Description: " << inventory[index].Description << "\n";
    cout << "Category: " << inventory[index].ProductCategory << "\n";
    cout << "Type: " << inventory[index].ProductType << "\n";
    cout << "Quantity: " << inventory[index].Quantity << "\n";
    cout << "Owner: " << inventory[index].Owner << "\n";
    cout << "Pricing: $" << fixed << setprecision(2) << inventory[index].Pricing << "\n";
    cout << "--------------------\n";
}

// 6. Change part owner
void changeOwner() {
    clearInputBuffer();
    string partNum;
    cout << "\n--- Change Owner ---\n";
    cout << "Enter Intel Part Number: ";
    getline(cin, partNum);

    int index = findPartIndex(partNum);
    if (index == -1) {
        cout << "Part not found.\n";
        return;
    }

    string newOwner;
    cout << "Current Owner: " << inventory[index].Owner << "\n";
    cout << "Enter new Owner name: ";
    getline(cin, newOwner);

    inventory[index].Owner = newOwner;
    saveInventory();
    cout << "Owner updated successfully.\n";
}
