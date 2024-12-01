#include "Building.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include <string>

using namespace std;

Building::Building() : Entity() {

}

Building::Building(int _x, int _y, int _color, string _character, string _name) : Entity(_x, _y, _color, _character, _name) {
    
}

void Building::interact(Tile* tile, Player* player) {
    if(getName() == "Trap"){
        cout << "You stepped on a trap!" << endl;
        player->takeDamage(1);
    }
    else if(getName() == "Exit"){
        string input;
        cout << "You found an exit, do you want to exit? (Y/N)" << endl;
        cin >> input;
        if(input == "Y" || input == "y"){
            throw true;
        }
    }
}

Building::~Building() {
    //cout << "Building destructor" << endl;
}