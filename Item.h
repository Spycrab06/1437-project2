#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Entity.h"
using namespace std;


class Map;
class Tile;
class Player;
class Living;

class Item : public Entity {
    public:
        Item();
        Item(int, int, int, int, int, int, string, string, string, bool, bool);
        ~Item() override;

        string toString() const;
        Item fromString(const string& data);

        int getValue();
        int getRarity();

        void setValue(int _value);
        bool isSellable();

        void interact(Tile* tile, Player* player) override;

        Item& operator=(const Item& other);

        bool getPassive() const;
        string getType() const;
        int getIncreaseAmount() const;

        void useItem(Living*);

    private:
        int value;
        bool sellable;
        int rarity;

        bool passive;
        string type;
        int increaseAmount;
};

#endif