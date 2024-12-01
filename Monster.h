#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Living.h"

using namespace std;

class Item;
class Map;
class Player;

class Monster : public Living {
    public:
        Monster();
        Monster(int, int, int, int, int, string, string, Player*, int, int, int, int, int);
        ~Monster() override;
        void startMove(Map* map, string inMove) override;

        void wander(Map* map);
        void stalk(Map* map);
        void attack(Map* map);

        Entity* getDrop();

        void interact(Tile* tile, Player* _player) override;
    private:
        Entity* drop;
        Player* player;

        bool wandering;
        int moveTimer;
        int currentTimer;
        int followDistance;
};

#endif


