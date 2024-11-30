#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Entity.h"
using namespace std;


class Map;
class Tile;
class Player;

class Item : public Entity {
    public:
        Item();
        Item(int, int, int, int, string, string, bool);
        ~Item() override;

        int getValue();

        void setValue(int _value);
        bool isSellable();

        void interact(Tile* tile, Player* player) override;
    private:
        int value;
        bool sellable;
        
};

#endif