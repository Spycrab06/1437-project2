#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() : Living() {
    inventorySize = 4;
    inventory = new Item[inventorySize];
    for (int i = 0; i < inventorySize; i++) {
        inventory[i] = Item();
    }
}

Player::Player(int _health, int _attack, int _x, int _y, int _color, string _character, string _name, int _sight) : Living(_health, _attack, _x, _y, _color, _character, _name) {
    itemCount = 0;
    inventorySize = 4;
    inventory = new Item[inventorySize];
    for (int i = 0; i < inventorySize; i++) {
       inventory[i] = Item();
    }

    sightRange = _sight;
}

Player::~Player() {
    delete[] inventory;
}

void Player::startMove(Map* map){
    string direction;
    cout << endl << endl;
    cout << "Enter a direction to move (w, a, s, d): ";
    cin >> direction;

    // check if only one char was entered
    if (direction.length() != 1) {
        cout << "Invalid input! Please enter a single character (w, a, s, d)." << endl;
        return;
    }

    char dir = toupper(direction[0]);

    int newX = getX();
    int newY = getY();

    // x and y are flipped, no clue why
    switch (dir) {
        case 'W': // up
            newX -= 1;
            break;
        case 'A': // left
            newY -= 1;
            break;
        case 'S': // down
            newX += 1;
            break;
        case 'D': // right
            newY += 1;
            break;
        default:
            cout << "Invalid direction!" << endl;
            return;
    }
    // move player
    move(newX, newY, map, "player");
}

bool Player::pickUpItem(Entity* item) {
    cout << "Player pickUpItem" << endl;
    if (itemCount >= inventorySize) {
        cout << "Inventory full!" << endl;
        return false;
    }
    
    inventory[itemCount] = *dynamic_cast<Item*>(item);
    itemCount++;
    return true;
}

int Player::getItemCount() {
    return itemCount;
}

int Player::getSightRange(){
    return sightRange;
}

void Player::setSightRange(int _sight){
    sightRange = _sight;
}