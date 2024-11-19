#include <string>
#include <iostream>
#include <cstdlib>
#include "Monster.h"
#include "Player.h"

using namespace std;

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

Monster::Monster() : Living() {
    drop = nullptr;
    player = nullptr;
    wandering = false;
    moveTimer = 1;
    currentTimer = 0;
    sight = 6;
    followDistance = 3;
}

Monster::Monster(int _health, int _attack, int _x, int _y, int _color, string _character, string _name, Player* _player, int _moveTimer, int _sight, int _followDist, int _angerThreshold) : Living(_health, _attack, _x, _y, _color, _character, _name) {
    // value, x, y, color, character, name
    //drop = new Item();
    drop = nullptr;
    player = _player;
    wandering = false;
    followDistance = _followDist;
    moveTimer = _moveTimer;
    sight = _sight;
    anger = 0;
    currentTimer = 0;
    angerThreshold = _angerThreshold;
}

Monster::~Monster() {
    delete drop;
    player = nullptr;
}

void Monster::startMove(Map* map){
    // get player's position
    int playerX = player->getX();
    int playerY = player->getY();

    int distanceX = abs(player->getX() - getX());
    int distanceY = abs(player->getY() - getY());

    if(distanceX <= sight && distanceY <= sight){
        wandering = false;
        //setColor(4);
    }
    else{
        wandering = true;
        //setColor(14);
    }

    if(currentTimer <= 0){
        if(anger > angerThreshold){
            attack(map);
            cout << "Monster attacking" << endl;
        }
        else if(wandering == false){
            stalk(map);
            cout << "Monster stalking" << endl;
        }
        else{
            wander(map);
            cout << "Monster wandering" << endl;
        }
        currentTimer = moveTimer;
    }
    else{
        currentTimer--;
    }

}

void Monster::wander(Map* map) {
    // get random direction
    int direction = rand() % 4;
    int newX = getX();
    int newY = getY();

    cout << direction << endl;
    switch (direction) {
        case 0:
            newX -= 1;
            break;
        case 1:
            newY -= 1;
            break;
        case 2:
            newX += 1;
            break;
        case 3:
            newY += 1;
            break;
        default:
            cout << "Invalid monster move direction" << endl;
    }

    // move monster
    move(newX, newY, map, "monster");
}

void Monster::stalk(Map* map) {
    // get player's position
    int playerX = player->getX();
    int playerY = player->getY();

    int newX = getX();
    int newY = getY();

    // calc distance to player
    int distanceX = playerX - getX();
    int distanceY = playerY - getY();


    bool moveIn = rand() % 2 == 0;

    // move towards if distance is greater than 3

    // -x is up
    // +x is down
    // -y is left
    // +y is right

    // move towards if the distance is greater than followDistance
    if (abs(distanceX) > followDistance) {
        if (distanceX > 0) {
            newX += 1; // down
        } 
        else {
            newX -= 1; // up
        }
    }

    if (abs(distanceY) > followDistance) {
        if (distanceY > 0) {
            newY += 1; // right
        } 
        else {
            newY -= 1; // left
        }
    }

    // move away if the distance is less than followDistance
    if (abs(distanceX) < followDistance) {
        if (distanceX > 0) {
            newX -= 1; // up
        } 
        else {
            newX += 1; // down
        }
    }

    if (abs(distanceY) < followDistance) {
        if (distanceY > 0) {
            newY -= 1; // left
        } 
        else {
            newY += 1; // right
        }
    }

    if (abs(distanceX) == followDistance && abs(distanceY) == followDistance) {
        // circular movement so it doesnt sit still
        int direction = rand() % 4;
        switch (direction) {
            case 0:
                newX -= 1; // Move up
                break;
            case 1:
                newY += 1; // Move right
                break;
            case 2:
                newX += 1; // Move down
                break;
            case 3:
                newY -= 1; // Move left
                break;
        }
    }

    // randomly move in and out of follow distance
    if (moveIn) {
        if (abs(distanceX) == followDistance) {
            newX += (distanceX > 0) ? 1 : -1;
        }
        if (abs(distanceY) == followDistance) {
            newY += (distanceY > 0) ? 1 : -1;
        }
    } else {
        if (abs(distanceX) == followDistance) {
            newX += (distanceX > 0) ? -1 : 1;
        }
        if (abs(distanceY) == followDistance) {
            newY += (distanceY > 0) ? -1 : 1;
        }
    }
    
    // move monster
    move(newX, newY, map, "monster");
}

void Monster::attack(Map* map) {
    // get player's position
    int playerX = player->getX();
    int playerY = player->getY();

    int newX = getX();
    int newY = getY();

    // move towards player
    if (playerX < getX()) {
        newX--;
    } 
    else if (playerX > getX()) {
        newX++;
    }
    else if (playerY < getY()) {
        newY--;
    } 
    else if (playerY > getY()) {
        newY++;
    }
    // move monster
    move(newX, newY, map, "monster");
}

Entity* Monster::getDrop() {
    return drop;
}