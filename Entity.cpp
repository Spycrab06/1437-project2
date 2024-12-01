#include <string>
#include "Entity.h"
#include "Map.h"
#include "Tile.h"

using namespace std;

Entity::Entity() {
    x = 0;
    y = 0;
    for(int i = 0; i < 2; i++){
        color[i] = 1;
        character[i] = "N ";
    }
    name = "Empty";
}

Entity::Entity(int _x, int _y, int _color, string _character, string _name) {
    x = _x;
    y = _y;
    
    // sets both start and the modified variables
    for(int i = 0; i < 2; i++){
        color[i] = _color;
        character[i] = _character;
    }
    name = _name;
}

int Entity::getX() const {return x;}
int Entity::getY() const {return y;}

int Entity::getStartColor() const {return color[0];}
int Entity::getModColor() const {return color[1];}
string Entity::getStartCharacter() const {return character[0];}
string Entity::getModCharacter() const {return character[1];}

string Entity::getName() const {return name;}

void Entity::setStartColor(int _color) {color[0] = _color;}
void Entity::setModColor(int _color) {color[1] = _color;}
void Entity::setStartCharacter(string _character) {character[0] = _character;}
void Entity::setModCharacter(string _character) {character[1] = _character;}

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

void Entity::startMove(Map* map, string inMove) {
    cout << "Entity startMove" << endl;
}

void Entity::interact(Tile* tile, Player* player) {
    cout << "Entity interact" << endl;
}

bool Entity::pickUpItem(Entity* item) {
    cout << "Entity pickUpItem" << endl;
    return true;
}

Entity& Entity::operator=(const Entity& other) {
    x = other.x;
    y = other.y;
    for(int i = 0; i < 2; i++){
        color[i] = other.color[i];
        character[i] = other.character[i];
    }
    name = other.name;
    return *this;
}

Entity::~Entity() {
    //cout << "Entity destructor" << endl;
}