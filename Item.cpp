#include "Item.h"
#include "Entity.h"
#include "Map.h"
#include "Tile.h"
#include <string>

using namespace std;

Item::Item() : Entity() {
    value = 0;
}
Item::Item(int _value, int _x, int _y, int _color, string _character, string _name) : Entity(_x, _y, _color, _character, _name) {
    value = _value;
}

int Item::getValue() {return value;}

void Item::setValue(int _value) {value = _value;}

void Item::interact(Tile* tile, Entity* player) {
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
    cout << "Item destructor" << endl;
}