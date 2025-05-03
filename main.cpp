#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class: Item (Encapsulation used here)
class Item
{
private:
    string itemID;
    string name;
    int quantity;
    string section;

public:
    // Constructor
    Item(string id, string n, int qty, string sec)
    {
        itemID = id;
        name = n;
        quantity = qty;
        section = sec;
    }

    // Getters
    string getItemID() const { return itemID; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    string getSection() const { return section; }

    // Setters
    void setQuantity(int qty) { quantity = qty; }
    void setSection(string sec) { section = sec; }

    // Method to display item details
    virtual void display() const
    {
        cout << "Item ID: " << itemID << ", Name: " << name
             << ", Quantity: " << quantity << ", Section: " << section << endl;
    }

    // Method to check if item is available
    bool isAvailable() const
    {
        return quantity > 0;
    }
};

// Derived class: PerishableItem (uses Inheritance)
class PerishableItem : public Item
{
private:
    string expiryDate;

public:
    // Constructor
    PerishableItem(string id, string n, int qty, string sec, string expiry)
        : Item(id, n, qty, sec), expiryDate(expiry) {}

    // Override display to include expiry date
    void display() const override
    {
        Item::display(); // Call base class display
        cout << "   Expiry Date: " << expiryDate << endl;
    }
};

// Warehouse class that holds items
class Warehouse
{
private:
    vector<Item *> inventory; // List of pointers to Item objects (polymorphism)

public:
    // Add new item to warehouse
    void addItem(Item *item)
    {
        inventory.push_back(item);
    }

    // Display all items
    void showInventory() const
    {
        cout << "Warehouse Inventory:\n";
        for (auto item : inventory)
        {
            item->display();
        }
    }

    // Fulfill order by item ID
    void fulfillOrder(string itemID, int orderQty)
    {
        for (auto item : inventory)
        {
            if (item->getItemID() == itemID)
            {
                if (item->getQuantity() >= orderQty)
                {
                    cout << "Order Fulfilled for " << item->getName() << endl;
                    item->setQuantity(item->getQuantity() - orderQty);
                }
                else
                {
                    cout << "Insufficient stock for " << item->getName() << endl;
                }
                return;
            }
        }
        cout << "Item ID " << itemID << " not found in warehouse.\n";
    }
};

// Main function to test the system
int main()
{
    Warehouse wh;

    // Adding normal items
    Item *item1 = new Item("101", "Screwdriver", 50, "A1");
    Item *item2 = new Item("102", "Hammer", 30, "A2");

    // Adding perishable item
    Item *item3 = new PerishableItem("201", "Milk Pack", 20, "B1", "2025-05-10");

    // Add items to warehouse
    wh.addItem(item1);
    wh.addItem(item2);
    wh.addItem(item3);

    // Show all inventory
    wh.showInventory();

    cout << "\nTrying to fulfill an order...\n";
    wh.fulfillOrder("102", 10); // Fulfill 10 Hammers

    cout << "\nUpdated Inventory:\n";
    wh.showInventory();

    // Cleanup memory
    delete item1;
    delete item2;
    delete item3;

    return 0;
}
