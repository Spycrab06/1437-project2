#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Shop.h"
#include "Item.h"
#include "Player.h"

// Constructor
Shop::Shop(const string& itemFile, int numItems) {

    numberOfItemsForSale = numItems; // default value
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
        cout << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) {
            continue; // skip empty lines
        }

        istringstream iss(line);
        int value, color, rarity, increase;
        string character, name, sellableStr, passiveStr, type;
        bool sellable, passive;

        if (iss >> value >> color >> rarity >> increase >> type >> character ) {
            // check for space after character
            char space;
            iss.get(space);
            if (space != ' ') {
                cout << "Error: Missing space after character in line: " << line << endl;
                continue;
            }

            // read the rest
            getline(iss, name);
            int lastSpace = name.find_last_of(' ');
            if (lastSpace == string::npos) {
                cout << "Error: Missing sellable field in line: " << line << endl;
                continue;
            }

            // Split name and passiveString
            passiveStr = name.substr(lastSpace + 1);
            name = name.substr(0, lastSpace);

            // convert passive to bool
            if (passiveStr == "true") {passive = true;}
            else if (passiveStr == "false") {passive = false;}
            else {
                cout << "Error: Invalid passive value in line: " << line << endl;
                continue;
            }

            lastSpace = name.find_last_of(' ');
            if (lastSpace == string::npos) {
                cout << "Error: Missing passive field in line: " << line << endl;
                continue;
            }
            
            // Split name and sellableStr
            sellableStr = name.substr(lastSpace + 1);
            name = name.substr(0, lastSpace);

            // convert sellableStr to bool
            if (sellableStr == "true") {sellable = true;}
            else if (sellableStr == "false") {sellable = false;}
            else {
                cout << "Error: Invalid sellable value in line: " << line << endl;
                continue;
            }

            // trim spaces from name
            name.erase(0, name.find_first_not_of(' '));

            //cout << "Loaded item: " << name << " (Value: " << value << ")" << endl;
            Item* newItem = new Item(value, 0, 0, color, rarity, increase, type, character + " ", name, sellable, passive);
            allItems.push_back(newItem);
        }
        else {
            cout << "Error: Invalid item data in line: " << line << endl;
        }
    }

    inFile.close();
}

// generate items for sale from loaded items
void Shop::generateItemsForSale() {
    itemsForSale.clear(); // clear just in case

    if (allItems.empty()) {
        cout << "No items available to generate shop inventory." << endl;
        return;
    }

    if (numberOfItemsForSale <= 0) {
        cout << "Invalid numberOfItemsForSale: " << numberOfItemsForSale << endl;
        return;
    }

    int maxRetries = 100; // limit the retries to prevent infinite loops
    int retryCount = 0;

    while (itemsForSale.size() < numberOfItemsForSale && retryCount < maxRetries) {
        for (size_t i = 0; i < allItems.size(); ++i) {
            int rarity = allItems[i]->getRarity();

            // make sure i didnt mess up on rarities
            if (rarity <= 0) {
                cout << "Invalid rarity, skipped: " << allItems[i]->getName() << endl;
                continue;
            }

            int randomChance = rand() % 100;

            // add based on each item's rarity
            if (randomChance < (100 / rarity)) {
                // no dupes
                bool alreadyInShop = false;
                for (const auto& itemForSale : itemsForSale) {
                    if (itemForSale.item == allItems[i]) {
                        alreadyInShop = true;
                        break;
                    }
                }

                // add to shop if not already there
                if (!alreadyInShop) {
                    //cout << "Added item: " << allItems[i]->getName()
                    //     << " (Value: " << allItems[i]->getValue()
                    //     << ", Rarity: " << rarity << ")" << endl;
                    itemsForSale.push_back({allItems[i], allItems[i]->getValue()});
                }
            }

            // if filled, stop
            if (itemsForSale.size() >= numberOfItemsForSale) {
                break;
            }
        }

        retryCount++;
    }

    if (itemsForSale.size() < numberOfItemsForSale) {
        cout << "Warning: Could not generate enough items for the shop. "
             << "Only " << itemsForSale.size() << " items added." << endl;
    } 
    else {
        //cout << "Successfully generated " << itemsForSale.size() << " items for sale." << endl;
    }
}

// sell items from inventory
void Shop::sellItems(Player* player, int &money) {
    int invSize = player->getItemCount() - 1;
    for (int i = invSize; i > -1; i--) {
        Item* currentItem = player->getItemFromInventory(i);
        if (currentItem && currentItem->isSellable()) {
            money += currentItem->getValue();
            //cout << "Selling at index: " << i << endl;
            player->deleteItemFromInventory(i);
            //player->setInventorySlot(i, new Item());
        }
    }
    cout << "Items sold successfully!" << endl;
}

// open the shop menu
void Shop::openShopMenu(Player* player, int& money) {
    cout << endl;
    cout << "Money: " << money << endl;
    cout << "Welcome to the Shop! Here are the items available for sale:" << endl;
    for (int i = 0; i < itemsForSale.size(); ++i) {
        cout << i + 1 << ". " << itemsForSale[i].item->getName()
                  << " - Price: " << itemsForSale[i].price << endl;
    }

    cout << "Enter the number of the item to buy, or 0 to exit: ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(itemsForSale.size())) {
        buyItem(player, choice - 1, money);
    } 
    else {
        cout << "Exiting shop menu." << endl;
    }
}

// buy an item
void Shop::buyItem(Player* player, int itemIndex, int &money) {
    if (itemIndex < 0 || itemIndex >= static_cast<int>(itemsForSale.size())) {
        cout << "Invalid choice." << endl;
        return;
    }

    ItemForSale& selectedItem = itemsForSale[itemIndex];
    if (money >= selectedItem.price) {
        if (player->getItemCount() < player->getInventorySize()) {
            Item* newItem = new Item(*selectedItem.item);
            newItem->setValue(selectedItem.price /= 2);
            player->addItemToInventory(newItem);
            money -= selectedItem.price;
            cout << "Item purchased successfully!" << endl;
        } 
        else {
            cout << "Inventory is full!" << endl;
        }
    } 
    else {
        cout << "Not enough money to buy this item." << endl;
    }
}

// get the lowest empty slot in the player's inventory
int Shop::getLowestEmptySlot(Player* player) {
    // for (int i = 0; i < player->getItemCount(); i++) {
    //     if (player->getItemFromInventory(i) == nullptr || player->getItemFromInventory(i)->getName() == "Empty") {
    //         return i;
    //     }
    // }
    // return -1; // No empty slots

    return player->getItemCount();
}
