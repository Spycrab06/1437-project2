#include <string>
#include <iostream>
#include "Player.h"
#include "Item.h"

using namespace std;

Player::Player() : Living() {
}

Player::Player(int _health, int _attack, int _x, int _y, int _color, string _character, string _name, int _sight, int _invSize) : Living(_health, _attack, _x, _y, _color, _sight, _character, _name, _invSize, 0) {
}

Player::~Player() {
    //cout << "Player destructor" << endl;
}

void Player::startMove(Map* map, string inMove) {
    string direction;

    if(inMove == ""){
        string direction;
        cout << endl << endl;
        cout << "Enter a direction to move (w, a, s, d): ";
        cin >> direction;
    }
    else{
        direction = inMove;
    }

    // check if only one char was entered
    if (direction.length() != 1) {
        cout << "Invalid input! Please enter a single character (w, a, s, d)." << endl;
        return;
    }

    char dir = toupper(direction[0]);

    int newX = getX();
    int newY = getY();

    // x and y are flipped, no clue why
    switch (dir)
    {
    case 'W':      // up
        newY -= 1; // CHANGE THIS LINE (was newX)
        break;
    case 'A':      // left
        newX -= 1; // CHANGE THIS LINE (was newY)
        break;
    case 'S':      // down
        newY += 1; // CHANGE THIS LINE (was newX)
        break;
    case 'D':      // right
        newX += 1; // CHANGE THIS LINE (was newY)
        break;
    }
    // move player
    move(newX, newY, map, "player");
}

bool Player::pickUpItem(Entity* item) {
    if (getItemCount() >= getInventorySize()) {
        cout << "Inventory full!" << endl;
        return false;
    }
    changeCurrentAnger(2);
    //inventory[inventory.size() + 1] = *dynamic_cast<Item*>(item);
    addItemToInventory(dynamic_cast<Item*>(item));
    return true;
}