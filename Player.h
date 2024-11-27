#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Living.h"

using namespace std;

class Item;
class Map;

class Player : public Living {
    public:
        Player();
        Player(int, int, int, int, int, string, string, int);
        ~Player() override;
        void startMove(Map* map) override;

        //void move(int _x, int _y, Map* _map) override;
        bool pickUpItem(Entity* item) override;
        int getSightRange();
        int getItemCount();

        void setSightRange(int);
    private:
        int inventorySize;
        int itemCount;
        Item* inventory;
        int sightRange;
};

#endif