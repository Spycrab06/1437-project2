#ifndef LIVING_H
#define LIVING_H

#include <string>

#include "Entity.h"
#include "Item.h"
#include <vector>
using namespace std;

class Map;
class Living : public Entity {
    public:
        Living();
        Living(int, int, int, int, int, int, string, string, int);
        ~Living() override;

        // sets
        void setStartHealth(int _health);
        void setModHealth(int _health);
        void setCurrentHealth(int _health);

        void setStartAttack(int _attack);
        void setModAttack(int _attack);
        void takeDamage(int damage);

        void setStartSightRange(int _sight);
        void setModSightRange(int _sight);

        void setInventorySize(int _size);

        // gets
        int getStartHealth();
        int getModHealth();
        int getCurrentHealth();

        int getStartAttack();
        int getModAttack();

        int getStartSightRange();
        int getModSightRange();

        int getInventorySize();
        int getItemCount();


        // other
        void startMove(Map* map) override;

        bool pickUpItem(Entity* item) override;
        Item* getItemFromInventory(int);
        void addItemToInventory(Item*);
        void deleteItemFromInventory(int);

        // check health and also if items give stat boosts
        int statCheck();

    private:
        // mainly used for player, can be used for monster drops
        int inventorySize;
        vector<Item> inventory;

        // 0: start sight
        // 1: mod sight
        int sightRange[2];

        // 0: start health
        // 1: mod health
        // 2: current health
        int health[3];

        // 0: start attack
        // 1: mod attack
        int attack[2];
};

#endif