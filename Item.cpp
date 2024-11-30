#include "Item.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Tile.h"
#include <string>

using namespace std;

Item::Item() : Entity() {
    value = 0;
    sellable = false;
    rarity = 0;
}
Item::Item(int _value, int _x, int _y, int _color, int _rarity, string _character, string _name, bool _sellable) : Entity(_x, _y, _color, _character, _name) {
    value = _value;
    sellable = _sellable;
    rarity = _rarity;
}

int Item::getValue() {return value;}

void Item::setValue(int _value) {value = _value;}

void Item::interact(Tile* tile, Player* player) {
    cout << "Item interact" << endl;
    cout << "Pick up Item? Y/N:" << endl;
    string input;
    cin >> input;
    if (input == "Y" || input == "y") {
        if (player->pickUpItem(this)) {
            tile->setInteractable(nullptr);
        }
        cout << "Item picked up!" << endl;
    } else {
        cout << "Item not picked up!" << endl;
    }
}

Item::~Item() {
    //cout << "Item destructor" << endl;
    
}

bool Item::isSellable() {
    return sellable;
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        value = other.value;
        sellable = other.sellable;
        setX(other.getX());
        setY(other.getY());
        setColor(other.getColor());
        setCharacter(other.getCharacter());
        setName(other.getName());
    }
    return *this;
}

int Item::getRarity() {
    return rarity;
}