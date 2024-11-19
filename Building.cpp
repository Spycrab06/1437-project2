#include "Building.h"
#include "Entity.h"
#include "Map.h"
#include <string>

using namespace std;

Building::Building() : Entity() {

}

Building::Building(int _x, int _y, int _color, string _character, string _name) : Entity(_x, _y, _color, _character, _name) {
    
}

void Building::interact(Tile* tile, Entity* player) {
    cout << "Building interact" << endl;

    
}