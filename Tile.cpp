#include <string>
#include <iostream>
#include "Tile.h"
#include "Entity.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class Entity;

//0: Black
//1: Blue
//2: Green
//3: Cyan
//4: Red
//5: Purple
//6: Yellow (Dark)
//7: Default white
//8: Gray/Grey
//9: Bright blue
//10: Brigth green
//11: Bright cyan
//12: Bright red
//13: Pink/Magenta
//14: Yellow
//15: Bright white
//Numbers after 15 are background colors

Tile::Tile() {
    x = 0;
    y = 0;
    entity = nullptr;
    monster = nullptr;
    interactable = nullptr;
}

Tile::Tile(int _x, int _y, Entity* _entity, Entity* _monster, Entity* _interactable) : x(_x), y(_y) {
    entity = _entity;
    monster = _monster;
    interactable = _interactable;
    cout << "specific tile constructor" << endl;  

}

Tile::Tile(int _x, int _y) {
    x = _x;
    y = _y;
    interactable = nullptr;
    entity = nullptr;
    monster = nullptr;
}

void Tile::printTile(bool hidden){
    if(hidden){
        changeColor(7);
        cout << "# ";
    }
    else if(entity != nullptr){
        changeColor(entity->getModColor());
        cout << entity->getModCharacter();
    }
    else if(monster != nullptr){
        changeColor(monster->getModColor());
        cout << monster->getModCharacter();
    }
    else if(interactable != nullptr){
        changeColor(interactable->getModColor());
        cout << interactable->getModCharacter();
    }
    else {
        changeColor(7);
        cout << ". ";
    }
    changeColor(-1);
}

string Tile::changeColor(int inColor) {
    string colorCode;
    switch (inColor) {
        case 0: colorCode = "\033[30m"; break;  // Black
        case 1: colorCode = "\033[34m"; break;  // Blue
        case 2: colorCode = "\033[32m"; break;  // Green
        case 3: colorCode = "\033[36m"; break;  // Cyan
        case 4: colorCode = "\033[31m"; break;  // Red
        case 5: colorCode = "\033[35m"; break;  // Magenta
        case 6: colorCode = "\033[33m"; break;  // Yellow
        case 7: colorCode = "\033[37m"; break;  // White
        case 8: colorCode = "\033[90m"; break;  // Bright Black (Gray)
        case 9: colorCode = "\033[94m"; break;  // Bright Blue
        case 10: colorCode = "\033[92m"; break; // Bright Green
        case 11: colorCode = "\033[96m"; break; // Bright Cyan
        case 12: colorCode = "\033[91m"; break; // Bright Red
        case 13: colorCode = "\033[95m"; break; // Bright Magenta
        case 14: colorCode = "\033[93m"; break; // Bright Yellow
        case 15: colorCode = "\033[97m"; break; // Bright White
        default: colorCode = "\033[0m"; break;  // Reset to default
    }
    cout << colorCode;
    return colorCode;
}

void Tile::startInteract() {
    if (monster != nullptr) {
        if (entity != nullptr) {
            monster->interact(this, dynamic_cast<Player*>(entity));
            //cout << "Interacting with monster" << endl;
        } 
        else {
            cout << "Invalid entity for interaction." << endl;
        }
    } 
    else if (interactable != nullptr) {
        if (entity != nullptr) {
            interactable->interact(this, dynamic_cast<Player*>(entity));
            //cout << "Interacting with item" << endl;
        } 
        else {
            cout << "Invalid entity for interaction." << endl;
        }
    } 
    else {
        cout << "Nothing to interact with" << endl;
    }
}

void Tile::setEntity(Entity* _entity) {
    entity = _entity;
}

Entity* Tile::getEntity() {return entity;}

void Tile::setMonster(Entity* _monster) {monster = _monster;}
Entity* Tile::getMonster() {return monster;}

void Tile::setInteractable(Entity* _interactable) {
    interactable = _interactable;}
Entity* Tile::getInteractable() {return interactable;}

int Tile::getX() {return x;}
int Tile::getY() {return y;}

void Tile::setX(int _x) {x = _x;}
void Tile::setY(int _y) {y = _y;}


Tile::~Tile() {
    if (interactable != nullptr) {
        delete interactable;
    }
    // deleting causes problems
    monster = nullptr;
    entity = nullptr;
}

int Tile::distanceToPlayerX(Player* player){
    int playerX = player->getX();
    int distanceX = abs(playerX - x);

    return distanceX;
}

int Tile::distanceToPlayerY(Player* player){
    int playerY = player->getY();
    int distanceY = abs(playerY - y);

    return distanceY;
}