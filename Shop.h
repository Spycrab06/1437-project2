#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <string>
#include "Item.h"
#include "Player.h"

class Shop {
public:
    Shop(const std::string& itemFile);
    ~Shop();

    void sellItems(Player* player, int &money);
    void openShopMenu(Player* player, int &money);
    void buyItem(Player* player, int itemIndex, int &money);

private:
    void loadItemsFromFile(const string& filePath);
    void generateItemsForSale();
    int getLowestEmptySlot(Player* player);

    struct ItemForSale {
        Item* item;
        int price;
        float weight;
    };

    std::vector<std::vector<ItemForSale>> itemsArray; // 2D array of items
    std::vector<ItemForSale> itemsForSale; // Items available for sale
    std::vector<Item*> allItems; // All items loaded from file
    int numberOfItemsForSale;
};

#endif
