#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Product {
public:
    int id;
    string name;
    double price;
    int stock;

    Product(int id, string name, double price, int stock) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    void display() const {
        cout << left << setw(5) << id << setw(20) << name
             << setw(10) << price << setw(10) << stock << endl;
    }
};

class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product product, int quantity)
        : product(product), quantity(quantity) {}
};

class ShoppingSystem {
private:
    vector<Product> products;
    vector<CartItem> cart;
    int nextProductId = 1;

public:
    void addProduct() {
        string name;
        double price;
        int stock;

        cout << "\nEnter correct product name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter correect product price: ";
        cin >> price;
        cout << "Enter stock quantity: ";
        cin >> stock;

        products.push_back(Product(nextProductId++, name, price, stock));
        cout << "\n✅ Product added successfully!\n";
    }

    void viewProducts() {
        if (products.empty()) {
            cout << "\n⚠️ No products available.\n";
            return;
        }

        cout << "\nAvailable Products:\n";
        cout << left << setw(5) << "ID" << setw(20) << "Name"
             << setw(10) << "Price" << setw(10) << "Stock" << endl;
        cout << "-----------------------------------------------------\n";
        for (const auto &p : products)
            p.display();
    }

    void searchProduct() {
        string keyword;
        cout << "\nEnter product name to search: ";
        cin.ignore();
        getline(cin, keyword);

        bool found = false;
        for (const auto &p : products) {
            if (p.name.find(keyword) != string::npos) {
                if (!found) {
                    cout << "\nSearch Results:\n";
                    cout << left << setw(5) << "ID" << setw(20) << "Name"
                         << setw(10) << "Price" << setw(10) << "Stock" << endl;
                    cout << "-----------------------------------------------------\n";
                }
                p.display();
                found = true;
            }
        }
        if (!found) cout << "\n❌ No product found.\n";
    }

    void addToCart() {
        int id, qty;
        cout << "\nEnter Product ID to add to cart: ";
        cin >> id;

        bool found = false;
        for (auto &p : products) {
            if (p.id == id) {
                found = true;
                cout << "Enter quantity: ";
                cin >> qty;

                if (qty <= p.stock && qty > 0) {
                    cart.push_back(CartItem(p, qty));
                    p.stock -= qty;
                    cout << "\n🛒 Added to cart successfully!\n";
                } else {
                    cout << "\n❌ Invalid quantity or out of stock.\n";
                }
                break;
            }
        }
        if (!found)
            cout << "\n❌ Product ID not found.\n";
    }

    void viewCart() {
        if (cart.empty()) {
            cout << "\n🛒 Your cart is empty.\n";
            return;
        }

        double total = 0;
        cout << "\nYour Shopping Cart:\n";
        cout << left << setw(5) << "ID" << setw(20) << "Name"
             << setw(10) << "Price" << setw(10) << "Qty" << setw(10) << "Total\n";
        cout << "-------------------------------------------------------------\n";

        for (const auto &item : cart) {
            double subtotal = item.product.price * item.quantity;
            total += subtotal;
            cout << left << setw(5) << item.product.id << setw(20) << item.product.name
                 << setw(10) << item.product.price << setw(10) << item.quantity
                 << setw(10) << subtotal << endl;
        }

        cout << "-------------------------------------------------------------\n";
        cout << "Total Amount: $" << total << endl;
    }

    void checkout() {
        if (cart.empty()) {
            cout << "\n⚠️ Cart is empty! Add items first.\n";
            return;
        }

        double total = 0;
        for (const auto &item : cart)
            total += item.product.price * item.quantity;

        cout << "\n💳 Checkout Summary\n";
        viewCart();
        cout << "\nTotal Amount Due: $" << total << endl;

        char confirm;
        cout << "Confirm purchase? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            cart.clear();
            cout << "\n✅ Purchase successful! Thank you for shopping.\n";
        } else {
            cout << "\n❌ Checkout canceled.\n";
        }
    }

    void mainMenu() {
        int choice;
        do {
            cout << "\n========== ONLINE SHOPPING SYSTEM ==========\n";
            cout << "1. Add Product\n";
            cout << "2. View All Products\n";
            cout << "3. Search Product\n";
            cout << "4. Add to Cart\n";
            cout << "5. View Cart\n";
            cout << "6. Checkout\n";
            cout << "0. Exit\n";
            cout << "===========================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addProduct(); break;
                case 2: viewProducts(); break;
                case 3: searchProduct(); break;
                case 4: addToCart(); break;
                case 5: viewCart(); break;
                case 6: checkout(); break;
                case 0: cout << "\n👋 Exiting the system. Goodbye!\n"; break;
                default: cout << "\n❌ Invalid choice. Try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    ShoppingSystem system;
    system.mainMenu();
    return 0;
}
