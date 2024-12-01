#include <string>
#include "Living.h"
#include "Map.h"
#include "Item.h"

using namespace std;

Living::Living() : Entity() {
    setInventorySize(4);
    inventory.reserve(inventorySize);
    for(int i = 0; i < 3; i++){
        health[i] = 10;
    }
    for(int i = 0; i < 2; i++){
        attack[i] = 1;
        sightRange[i] = 3;
        anger[i] = 0;
    }
}

Living::Living(int _health, int _attack, int _x, int _y, int _color, int _sight, string _character, string _name, int _invSize) : Entity(_x, _y, _color, _character, _name) {
    setInventorySize(_invSize);
    inventory.reserve(inventorySize);
    

    for(int i = 0; i < 3; i++){
        health[i] = _health;
    }
    for(int i = 0; i < 2; i++){
        attack[i] = _attack;
        sightRange[i] = _sight;
    }

    anger[0] = 10;
    anger[1] = 0;
}

void Living::setStartHealth(int _health) {health[0] = _health;}
void Living::setModHealth(int _health) {health[1] = _health;}
void Living::setCurrentHealth(int _health) {health[2] = _health;}

void Living::setStartAttack(int _attack) {attack[0] = _attack;}
void Living::setModAttack(int _attack) {attack[1] = _attack;}

void Living::setStartSightRange(int _sight) {sightRange[0] = _sight;}
void Living::setModSightRange(int _sight) {sightRange[1] = _sight;}

void Living::takeDamage(int damage) {health[2] -= damage;}

int Living::getStartHealth() const {return health[0];}
int Living::getModHealth() const {return health[1];}
int Living::getCurrentHealth() const {return health[2];}

int Living::getStartAttack() {return attack[0];}
int Living::getModAttack() {return attack[1];}

int Living::getStartSightRange() {return sightRange[0];}
int Living::getModSightRange() {return sightRange[1];}

void Living::startMove(Map* map, string inMove) {
    cout << "Living startMove" << endl;
}

bool Living::pickUpItem(Entity* item) {
    cout << "Living pickUpItem" << endl;
    return true;
}

Living::~Living() {
    //cout << "Living destructor" << endl;
    inventory.clear();
}

int Living::statCheck(){
    if(getName() == "Player" && getCurrentHealth() <= 0){
        throw false;
    }
    else if(getName() == "Monster" && getCurrentHealth() <= 0){
        // tells main that this monster is dead
        return 1;
    }

    resetStats();

    for(const Item& item : inventory){
        if(item.getPassive()){
            if(item.getType() == "Health"){
                setModHealth(getStartHealth() + item.getIncreaseAmount());
            }
            else if(item.getType() == "Attack"){
                setModAttack(getStartAttack() + item.getIncreaseAmount());
            }
            else if(item.getType() == "Sight"){
                setModSightRange(getStartSightRange() + item.getIncreaseAmount());
            }
            else if(item.getType() == "Hat"){
                setModCharacter(item.getStartCharacter());
            }
            else if(item.getType() == "Dye"){
                setModColor(item.getStartColor());
            }
        }
    }

    if(getCurrentHealth() > getModHealth()){
        setCurrentHealth(getModHealth());
    }

    return 0;
}

// inventory stuff

int Living::getItemCount() {
    return inventory.size();
}

Item* Living::getItemFromInventory(int index){
    return &inventory[index];
}

void Living::deleteItemFromInventory(int index) {
    if (index >= 0 && index < inventory.size()) {
        inventory.erase(inventory.begin() + index);
    } 
    else {
        cerr << "Error: Invalid index " << index << " for inventory size " << inventory.size() << endl;
    }
}

int Living::getInventorySize(){
    return inventorySize;
}

void Living::setInventorySize(int _size){
    inventorySize = _size;
}

void Living::addItemToInventory(Item* item){
    inventory.emplace_back(*item);
}

void Living::setCurrentAnger(int _anger){
    anger[1] = _anger;
}

int Living::getCurrentAnger(){
    return anger[1];
}

void Living::setMaxAnger(int _anger){
    anger[0] = _anger;
}

int Living::getMaxAnger(){
    return anger[0];
}

void Living::changeCurrentAnger(int _anger){
    anger[1] += _anger;
}

void Living::resetStats(){
    setModHealth(getStartHealth());
    setModAttack(getStartAttack());
    setModSightRange(getStartSightRange());
    setModCharacter(getStartCharacter());
    //setModColor(getStartColor()); hidden for dye interaction
}

void Living::deleteSpecificItem(Item* item){
    for(int i = 0; i < inventory.size(); i++){
        if(&inventory[i] == item){
            inventory.erase(inventory.begin() + i);
        }
    }
}

vector<Item> Living::getInventory() const {
    return inventory;
}

void Living::setInventory(vector<Item> _inventory){
    inventory = _inventory;
}