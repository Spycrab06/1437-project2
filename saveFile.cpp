#include "saveFile.h"
#include "Item.h"

#include <fstream>
#include <iostream>

SaveFile::SaveFile(int quota, int money, int health, const vector<Item>& inventory) : quota(quota), money(money), health(health), inventory(inventory) {}

void SaveFile::save(const string& filename) const {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error: Could not open file for saving: " << filename << endl;
        return;
    }

    // Save basic properties
    outFile << quota << endl << money << endl << health << endl;

    // Save inventory
    outFile << inventory.size() << endl;
    for (const auto& item : inventory) {
        outFile << item.toString() << endl;
    }

    outFile.close();
    outFile.close();
}

void SaveFile::load(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file for loading: " << filename << endl;
        return;
    }

    // Load basic properties
    inFile >> quota >> money >> health;

    // Load inventory
    size_t inventorySize;
    inFile >> inventorySize;
    inventory.clear();
    inventory.resize(inventorySize);

    for (size_t i = 0; i < inventorySize; ++i) {
        string itemData;
        inFile.ignore(); // Ignore newline character
        getline(inFile, itemData);
        inventory[i] = inventory[i].fromString(itemData);
    }

    inFile.close();
}


void SaveFile::setInventory(const vector<Item>& inventory) {
    this->inventory = inventory;
}

int SaveFile::getQuota() const {
    return quota;
}

int SaveFile::getMoney() const {
    return money;
}

int SaveFile::getHealth() const {
    return health;
}

const vector<Item>& SaveFile::getInventory() const {
    return inventory;
}