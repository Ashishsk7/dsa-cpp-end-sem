#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// --- DATA STRUCTURES ---
struct Product {
    int id;
    string name;
    double price;
    string barcode;
    int salesVolume;
};

class PriceWaveSystem {
private:
    // unordered_map provides O(1) average time complexity for product lookups
    unordered_map<int, Product> catalog;
    
    // Stack used for LIFO tracking of price modifications (Undo functionality)
    stack<pair<int, double>> priceHistory; 
    
    // Queue maintains FIFO order for fair processing during high-traffic checkouts
    queue<int> checkoutQueue; 
    
    // Adjacency list representing a graph of product relationships (co-purchases)
    unordered_map<int, vector<int>> bundleGraph; 

public:
    // Utility to populate initial catalog data
    void addProduct(int id, string name, double price, string barcode, int sales) {
        catalog[id] = {id, name, price, barcode, sales};
    }

    // Connects two nodes in the bundle graph
    void addBundleRelation(int id1, int id2) {
        bundleGraph[id1].push_back(id2);
        bundleGraph[id2].push_back(id1);
    }

    // Formats and displays single product details
    void displayProduct(const Product& p) {
        cout << "\n=== Product Details ===\n";
        cout << "ID: " << p.id << "\n";
        cout << "Name: " << p.name << "\n";
        cout << "Price: Rs " << p.price << "\n";
        cout << "Barcode: " << p.barcode << "\n";
        cout << "Sales Volume: " << p.salesVolume << "\n";
        cout << "=======================\n";
    }

    // --- SYSTEM FEATURES ---

    void viewEntireCatalog() {
        cout << "\n--- Complete Product Catalog ---\n";
        for (auto& pair : catalog) {
            cout << "ID: " << pair.first << " | " << pair.second.name << " | Rs " << pair.second.price << "\n";
        }
    }

    void updatePrice(int id, double newPrice) {
        if (catalog.find(id) != catalog.end()) {
            priceHistory.push({id, catalog[id].price}); // Push current state before modifying
            catalog[id].price = newPrice;
            cout << "Price updated! " << catalog[id].name << " is now Rs " << newPrice << "\n";
        } else {
            cout << "Error: Product ID not found.\n";
        }
    }

    void undoLastPriceChange() {
        if (priceHistory.empty()) {
            cout << "No price changes to undo.\n";
            return;
        }
        auto lastChange = priceHistory.top();
        priceHistory.pop();
        
        catalog[lastChange.first].price = lastChange.second;
        cout << "Undo successful! " << catalog[lastChange.first].name 
             << " reverted to Rs " << lastChange.second << "\n";
    }

    void addToCheckout(int id) {
        if (catalog.find(id) != catalog.end()) {
            checkoutQueue.push(id);
            cout << catalog[id].name << " added to checkout queue.\n";
        } else {
            cout << "Error: Invalid Product ID.\n";
        }
    }

    void processCheckout() {
        if (checkoutQueue.empty()) {
            cout << "Checkout queue is currently empty.\n";
            return;
        }
        int id = checkoutQueue.front();
        checkoutQueue.pop();
        catalog[id].salesVolume++; 
        cout << "Processed checkout for: " << catalog[id].name << ". New Sales Volume: " << catalog[id].salesVolume << "\n";
    }

    void lookupByBarcode(string targetBarcode) {
        vector<Product> sortedCatalog;
        for (auto& pair : catalog) sortedCatalog.push_back(pair.second);
        
        // Sorting is a prerequisite for Binary Search to achieve O(log N) lookup
        sort(sortedCatalog.begin(), sortedCatalog.end(), [](const Product& a, const Product& b) {
            return a.barcode < b.barcode;
        });

        // Binary Search implementation
        int left = 0, right = sortedCatalog.size() - 1;
        bool found = false;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (sortedCatalog[mid].barcode == targetBarcode) {
                cout << "\nBarcode Match Found!";
                displayProduct(sortedCatalog[mid]);
                found = true;
                break;
            }
            if (sortedCatalog[mid].barcode < targetBarcode) left = mid + 1;
            else right = mid - 1;
        }
        
        if (!found) cout << "Error: Barcode not found in system.\n";
    }

    void showBestSellers() {
        vector<Product> sellers;
        for (auto& pair : catalog) sellers.push_back(pair.second);
        
        // Sort in descending order based on sales volume
        sort(sellers.begin(), sellers.end(), [](const Product& a, const Product& b) {
            return a.salesVolume > b.salesVolume; 
        });

        cout << "\n=== Top 5 Best Sellers ===\n";
        for (int i = 0; i < min(5, (int)sellers.size()); i++) {
            cout << i+1 << ". " << sellers[i].name 
                 << " | Sold: " << sellers[i].salesVolume 
                 << " | Price: Rs " << sellers[i].price << "\n";
        }
        cout << "==========================\n";
    }

    void suggestBundles(int id) {
        if (catalog.find(id) == catalog.end()) {
            cout << "Error: Product ID not found.\n";
            return;
        }
        
        cout << "\n--- Bundle Recommendations for " << catalog[id].name << " ---\n";
        // Check if the node exists in the adjacency list and has connected edges
        if (bundleGraph.find(id) == bundleGraph.end() || bundleGraph[id].empty()) {
            cout << "No bundle recommendations available for this product.\n";
            return;
        }
        
        for (int relatedId : bundleGraph[id]) {
            cout << " -> " << catalog[relatedId].name << " (Rs " << catalog[relatedId].price << ")\n";
        }
    }

    void calculateMaxDiscount(double basePrice) {
        // Greedy approach: apply the largest absolute impact discount first
        double price = basePrice;
        cout << "\n--- Greedy Discount Calculator ---\n";
        cout << "Base Price: Rs " << price << "\n";
        
        price = price * 0.80; // 20% seasonal off 
        cout << "After 20% Seasonal Discount: Rs " << price << "\n";
        
        if (price > 50) price -= 50; // Rs 50 flat off coupon
        cout << "After Rs 50 Flat Coupon: Rs " << price << "\n";
        
        cout << "Final Optimal Price: Rs " << price << "\n";
    }

    void maximizeProfit(int id, int demandChoice) {
        if (catalog.find(id) != catalog.end()) {
            double basePrice = catalog[id].price;
            double dynamicPrice = basePrice;

            cout << "\n--- Profit Maximizer Engine ---\n";
            if (demandChoice == 1) { 
                dynamicPrice = basePrice * 0.90; 
                cout << "Alert: Low demand. Dropping price by 10% to stimulate sales.\n";
            } else if (demandChoice == 2) { 
                dynamicPrice = basePrice * 1.05; 
                cout << "Alert: Medium demand. Increasing price slightly by 5%.\n";
            } else if (demandChoice == 3) { 
                dynamicPrice = basePrice * 1.20; 
                cout << "Alert: High demand! Implementing 20% surge pricing.\n";
            } else {
                cout << "Error: Invalid demand level.\n";
                return;
            }

            // Ensure the dynamic price change is logged for potential rollback
            priceHistory.push({id, basePrice}); 
            catalog[id].price = dynamicPrice;
            
            cout << catalog[id].name << " dynamically priced at: Rs " << dynamicPrice << " (Old Price: Rs " << basePrice << ")\n";
        } else {
            cout << "Error: Product ID not found.\n";
        }
    }
};

// --- MAIN EXECUTION ---
int main() {
    PriceWaveSystem system;
    
    // Initialize Catalog Database
    system.addProduct(101, "Smartphone Pro", 15000.0, "BAR101", 8500);
    system.addProduct(102, "Rugged Phone Case", 500.0, "BAR102", 12000);
    system.addProduct(103, "Gaming Laptop", 85000.0, "BAR103", 3000);
    system.addProduct(104, "Wireless Mouse", 800.0, "BAR104", 5400);
    system.addProduct(105, "Leather Laptop Bag", 1200.0, "BAR105", 2100);
    system.addProduct(106, "Bluetooth Earbuds", 2500.0, "BAR106", 9600);
    system.addProduct(107, "Fitness Smartwatch", 3000.0, "BAR107", 6300);
    system.addProduct(108, "20000mAh Power Bank", 1500.0, "BAR108", 4100);
    system.addProduct(109, "Fast-Charge USB-C", 300.0, "BAR109", 15000);
    system.addProduct(110, "27-inch Monitor", 12000.0, "BAR110", 1800);
    system.addProduct(111, "Mechanical Keyboard", 3500.0, "BAR111", 2700);
    system.addProduct(112, "HDMI Cable 2m", 400.0, "BAR112", 8200);
    system.addProduct(113, "Drawing Tablet", 20000.0, "BAR113", 1100);
    system.addProduct(114, "Digital Stylus Pen", 1500.0, "BAR114", 900);
    system.addProduct(115, "Dual-Band WiFi Router", 2500.0, "BAR115", 3400);
    
    // Initialize Product Relationships (Graph Edges)
    system.addBundleRelation(101, 102); 
    system.addBundleRelation(101, 106); 
    system.addBundleRelation(101, 108); 
    system.addBundleRelation(101, 109); 
    system.addBundleRelation(103, 104); 
    system.addBundleRelation(103, 105); 
    system.addBundleRelation(110, 111); 
    system.addBundleRelation(110, 112); 
    system.addBundleRelation(113, 114); 

    int choice;
    do {
        cout << "\n=======================================\n";
        cout << "   PriceWave E-Commerce Engine         \n";
        cout << "=======================================\n";
        cout << "1. View Entire Catalog\n";
        cout << "2. Update Product Price (Hash Map)\n";
        cout << "3. Undo Last Price Change (Stack)\n";
        cout << "4. Add to Checkout Queue (Queue)\n";
        cout << "5. Process Next Checkout (Queue)\n";
        cout << "6. Lookup via Barcode (Binary Search)\n";
        cout << "7. Show Best Sellers (Sorting)\n";
        cout << "8. Bundle Recommendations (Graph)\n";
        cout << "9. Calculate Best Discount (Greedy)\n";
        cout << "10. Profit Maximizer (Dynamic Pricing)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int id;
        double price;
        string barcode;
        int demandChoice;

        switch (choice) {
            case 1: 
                system.viewEntireCatalog(); 
                break;
            case 2: 
                cout << "Enter Product ID: "; cin >> id;
                cout << "Enter New Price: "; cin >> price;
                system.updatePrice(id, price); 
                break;
            case 3: 
                system.undoLastPriceChange(); 
                break;
            case 4: 
                cout << "Enter Product ID to add to cart: "; cin >> id;
                system.addToCheckout(id); 
                break;
            case 5: 
                system.processCheckout(); 
                break;
            case 6: 
                cout << "Enter Barcode (e.g., BAR103): "; cin >> barcode;
                system.lookupByBarcode(barcode); 
                break;
            case 7: 
                system.showBestSellers(); 
                break;
            case 8:
                cout << "Enter Product ID for recommendations (e.g., 101 or 103): "; cin >> id;
                system.suggestBundles(id);
                break;
            case 9: 
                cout << "Enter a base price to calculate discount: "; cin >> price;
                system.calculateMaxDiscount(price); 
                break;
            case 10: 
                cout << "Enter Product ID: "; cin >> id;
                cout << "Select Demand Level (1: Low, 2: Medium, 3: High): "; cin >> demandChoice;
                system.maximizeProfit(id, demandChoice); 
                break;
            case 0: 
                cout << "Exiting system...\n"; 
                break;
            default: 
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}