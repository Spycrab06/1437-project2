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
        Living(int, int, int, int, int, int, string, string, int, int);
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

        void setMaxAnger(int _anger);
        void setCurrentAnger(int _anger);

        // gets
        int getStartHealth() const;
        int getModHealth() const;
        int getCurrentHealth() const;

        int getStartAttack();
        int getModAttack();

        int getStartSightRange();
        int getModSightRange();

        int getInventorySize();
        int getItemCount();

        int getMaxAnger();
        int getCurrentAnger();

        void changeCurrentAnger(int _anger);


        // other
        void startMove(Map* map, string) override;

        bool pickUpItem(Entity* item) override;
        Item* getItemFromInventory(int);
        void addItemToInventory(Item*);
        void deleteItemFromInventory(int);

        void deleteSpecificItem(Item*);

        vector<Item> getInventory() const;
        void setInventory(vector<Item>);

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

        // used player as aggro
        // used monster as anger
        int anger[2];

        void resetStats();
};

#endif