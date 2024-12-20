#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Living.h"
#include <vector>

using namespace std;

class Item;
class Map;

class Player : public Living {
    public:
        Player();
        Player(int, int, int, int, int, string, string, int, int);
        ~Player() override;
        void startMove(Map* map, string) override;
        bool pickUpItem(Entity* item) override;
        int getAggro();
        
    private:
};

#endif