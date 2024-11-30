#include <string>
#include "Living.h"
#include "Map.h"

using namespace std;

Living::Living() : Entity() {
    health = 10;
    attack = 1;
}

Living::Living(int _health, int _attack, int _x, int _y, int _color, string _character, string _name) : Entity(_x, _y, _color, _character, _name) {
    health = _health;
    attack = _attack;
}

void Living::setHealth(int _health) {health = _health;}
void Living::setAttack(int _attack) {attack = _attack;}
void Living::takeDamage(int damage) {health -= damage;}

int Living::getHealth() {return health;}
int Living::getAttack() {return attack;}

void Living::startMove(Map* map) {
    cout << "Living startMove" << endl;
}

bool Living::pickUpItem(Entity* item) {
    cout << "Living pickUpItem" << endl;
    return true;
}

Living::~Living() {
    //cout << "Living destructor" << endl;
}