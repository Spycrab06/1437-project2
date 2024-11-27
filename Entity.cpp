#include <string>
#include "Entity.h"
#include "Map.h"
#include "Tile.h"

using namespace std;

Entity::Entity() {
    x = 0;
    y = 0;
    color = 1;
    character = "N ";
    name = "Null";
}

Entity::Entity(int _x, int _y, int _color, string _character, string _name) {
    x = _x;
    y = _y;
    color = _color;
    character = _character;
    name = _name;
}

int Entity::getX() {return x;}
int Entity::getY() {return y;}
int Entity::getColor() {return color;}
string Entity::getCharacter() {return character;}
string Entity::getName() {return name;}

void Entity::setColor(int _color) {color = _color;}
void Entity::setCharacter(string _character) {character = _character;}
void Entity::setX(int _x) {x = _x;}
void Entity::setY(int _y) {y = _y;}
void Entity::setName(string _name) {name = _name;}

void Entity::move(int _x, int _y, Map* _map, string type) {
    // Check if in bounds
    if (_x >= 0 && _x < _map->getWidth() && _y >= 0 && _y < _map->getHeight()) {
        Tile& currentTile = _map->getTile(getX(), getY());
        Tile& newTile = _map->getTile(_x, _y);
        
        // manage the entities
        if (&newTile != nullptr) {

            // move entity to new tile
            if(type == "player"){
                newTile.setEntity(this);
                currentTile.setEntity(nullptr);

                newTile.startInteract();
            }
            else if(type == "monster"){
                newTile.setMonster(this);
                currentTile.setMonster(nullptr);
            }
            else if(type == "interactable"){
                newTile.setInteractable(this);
                currentTile.setInteractable(nullptr);
            }
            else{
                cout << "Invalid type" << endl;
            }

            // update internal
            setX(_x);
            setY(_y);
        } 
        else {
            cout << "move failed due to null tile reference" << endl;
        }
    } 
    else {
        cout << "Move out of bounds" << endl;
    }
}

void Entity::startMove(Map* map) {
    cout << "Entity startMove" << endl;
}

void Entity::interact(Tile* tile, Entity* player) {
    cout << "Entity interact" << endl;
}

bool Entity::pickUpItem(Entity* item) {
    cout << "Entity pickUpItem" << endl;
    return true;
}

Entity& Entity::operator=(const Entity& other) {
    x = other.x;
    y = other.y;
    color = other.color;
    character = other.character;
    name = other.name;
    return *this;
}

Entity::~Entity() {
    cout << "Entity destructor" << endl;
}