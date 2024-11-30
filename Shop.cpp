#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Shop.h"
#include "Item.h"
#include "Player.h"

// Constructor
Shop::Shop(const string& itemFile) : numberOfItemsForSale(0) {

    // load items from file
    loadItemsFromFile(itemFile);

    // generate initial stock for sale
    generateItemsForSale();
}

Shop::~Shop() {
    for (auto item : allItems) {
        delete item;
    }
}

// load items from a file
void Shop::loadItemsFromFile(const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        int value, x, y, color;
        string character, name;
        bool sellable;

        if (iss >> value >> x >> y >> color >> character >> name >> sellable) {
            Item* newItem = new Item(value, x, y, color, character, name, sellable);
            allItems.push_back(newItem);
        }
    }

    inFile.close();
}

// generate items for sale from loaded items
void Shop::generateItemsForSale() {
    itemsArray.clear();
    itemsForSale.clear();

    for (int i = 0; i < 5; ++i) {
        vector<ItemForSale> row;
        for (int j = 0; j < 5 && i * 5 + j < static_cast<int>(allItems.size()); ++j) {
            Item* item = allItems[i * 5 + j];
            row.push_back({item, item->getValue() * 10, static_cast<float>(rand() % 100) / 100.0f});
        }
        itemsArray.push_back(row);
    }

    // randomly select items for sale
    for (int i = 0; i < 10 && i < static_cast<int>(allItems.size()); ++i) {
        int row = rand() % itemsArray.size();
        int col = rand() % itemsArray[row].size();
        itemsForSale.push_back(itemsArray[row][col]);
    }

    numberOfItemsForSale = itemsForSale.size();
}

// sell items from inventory
void Shop::sellItems(Player* player, int &money) {
    for (int i = 0; i < player->getItemCount(); i++) {
        Item* currentItem = player->getItemFromInventory(i);
        if (currentItem && currentItem->isSellable()) {
            money += currentItem->getValue();
            player->setInventorySlot(i, nullptr);
        }
    }
   cout << "Items sold successfully!\n";
}

// open the shop menu
void Shop::openShopMenu(Player* player, int& money) {
    cout << "Welcome to the Shop! Here are the items available for sale:\n";
    for (size_t i = 0; i < itemsForSale.size(); ++i) {
        cout << i + 1 << ". " << itemsForSale[i].item->getName()
                  << " - Price: " << itemsForSale[i].price << "\n";
    }

    cout << "Enter the number of the item to buy, or 0 to exit: ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(itemsForSale.size())) {
        buyItem(player, choice - 1, money);
    } else {
        cout << "Exiting shop menu.\n";
    }
}

// buy an item
void Shop::buyItem(Player* player, int itemIndex, int &money) {
    if (itemIndex < 0 || itemIndex >= static_cast<int>(itemsForSale.size())) {
        cout << "Invalid choice.\n";
        return;
    }

    ItemForSale& selectedItem = itemsForSale[itemIndex];
    if (money >= selectedItem.price) {
        int slot = getLowestEmptySlot(player);
        if (slot != -1) {
            player->setInventorySlot(slot, new Item(*selectedItem.item));
            money -= selectedItem.price;
            cout << "Item purchased successfully!\n";
        } else {
            cout << "Inventory is full!\n";
        }
    } else {
        cout << "Not enough money to buy this item.\n";
    }
}

// get the lowest empty slot in the player's inventory
int Shop::getLowestEmptySlot(Player* player) {
    for (int i = 0; i < player->getItemCount(); i++) {
        if (player->getItemFromInventory(i) == nullptr) {
            return i;
        }
    }
    return -1; // No empty slots
}
