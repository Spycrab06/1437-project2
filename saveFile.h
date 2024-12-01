#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <vector>
#include <string>
#include "Item.h"

class SaveFile {
public:
    SaveFile(int quota, int money, int health, const vector<Item>& inventory);

    void save(const string& filename) const;
    void load(const string& filename);

    int getQuota() const;
    int getMoney() const;
    int getHealth() const;
    const vector<Item>& getInventory() const;

    void setInventory(const vector<Item>& inventory);

private:
    int quota;
    int money;
    int health;
    vector<Item> inventory;
};

#endif