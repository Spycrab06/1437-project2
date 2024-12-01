#include "Item.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Living.h"
#include "Tile.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Item::Item() : Entity() {
    value = 0;
    sellable = false;
    rarity = 0;
    increaseAmount = 0;
    type = "None";
    passive = false;
}
Item::Item(int _value, int _x, int _y, int _color, int _rarity, int _increase, string _type, string _character, string _name, bool _sellable, bool _passive) : Entity(_x, _y, _color, _character, _name) {
    value = _value;
    sellable = _sellable;
    rarity = _rarity;
    increaseAmount = _increase;
    type = _type;
    passive = _passive;
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

        setStartColor(other.getStartColor());
        setModColor(other.getModColor());
        
        setStartCharacter(other.getStartCharacter());
        setModCharacter(other.getModCharacter());

        setName(other.getName());
    }
    return *this;
}

int Item::getRarity() {return rarity;}

bool Item::getPassive() const {return passive;}
string Item::getType() const {return type;}
int Item::getIncreaseAmount() const {return increaseAmount;}

void Item::useItem(Living* entity) {
    bool used = false;
    if(passive != true){
        if(type == "Health"){
            if(entity->getCurrentHealth() + increaseAmount <= entity->getModHealth()){
                entity->setCurrentHealth(entity->getCurrentHealth() + increaseAmount);
                cout << "You used the " << getName() << " and healed " << increaseAmount << " health!" << endl;
                used = true;
            }
            else if(entity->getCurrentHealth() == entity->getModHealth()){
                cout << "You are already full health" << endl;
            }
            else{
                entity->setCurrentHealth(entity->getModHealth());
                cout << "You used the " << getName() << "and healed to full" << endl;
                used = true;
            }
        }
        else if(type == "Anger"){
            entity->changeCurrentAnger(increaseAmount);
            cout << "You sprayed the " << getName() << "! it smells." << endl;
            used = true;
        }
        else if(type == "Dye"){
            cout << "Oh No! you dropped the " << getName() << " and covered yourself!" << endl;
            entity->setModColor(getStartColor());
        }
        else if(type == "Duck"){
            cout << "Quack" << endl;
        }
        else if(type == "Luck"){
            cout << "Rubbing the dice makes you feel lucky" << endl;
        }
        else if(type == "Treasure"){
            cout << "Doesnt seem to do anything, but looks valuble" << endl;
        }
    }
    else{
        cout << "The " << getName() << " seems to do nothing" << endl;
    }

    if(used == true){
        entity->deleteSpecificItem(this);
    }
}

// converts the item to a string
string Item::toString() const {
    stringstream ss;
    ss << value << " "
       << sellable << " "
       << rarity << " "
       << passive << " "
       << type << " "
       << increaseAmount << " "
       << getStartCharacter() << " "
       << getStartColor() << " "
       << getName();
    return ss.str();
}

// creates an Item object from a string
Item Item::fromString(const string& data) {
    stringstream ss(data);
    int _value, _rarity, _increaseAmount, _color;
    bool _sellable, _passive;
    string _type, _character, _name;

    ss >> _value >> _sellable >> _rarity >> _passive >> _type >> _increaseAmount >> _character >> _color;
    getline(ss, _name); // to read names with spaces

    return Item(_value, 0, 0, _color, _rarity, _increaseAmount, _type, _character, _name, _sellable, _passive);
}
