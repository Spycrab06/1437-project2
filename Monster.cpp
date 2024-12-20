#include <string>
#include <iostream>
#include <cstdlib>
#include "Monster.h"
#include "Player.h"
#include "Map.h"
#include "Tile.h"

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
//10: Bright green
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
    followDistance = 3;
}

Monster::Monster(int _health, int _attack, int _x, int _y, int _color, string _character, string _name, Player* _player, int _moveTimer, int _sight, int _followDist, int _angerThreshold, int _invSize) : Living(_health, _attack, _x, _y, _color, _sight, _character, _name, _invSize, _angerThreshold) {
    // value, x, y, color, character, name
    //drop = new Item();
    drop = nullptr;
    player = _player;
    wandering = false;
    followDistance = _followDist;
    moveTimer = _moveTimer;
    currentTimer = 0;
}

Monster::~Monster() {
    delete drop;
    player = nullptr;
}

void Monster::startMove(Map* map, string inMove){
    // get player's position
    int playerX = player->getX();
    int playerY = player->getY();

    int distanceX = abs(playerX - getX());
    int distanceY = abs(playerY - getY());
    if(getCurrentAnger() <= player->getCurrentAnger()){
        setCurrentAnger(player->getCurrentAnger());
        //cout << "aggro " << anger << endl;
    }

    if(distanceX <= getModSightRange() && distanceY <= getModSightRange()){
        wandering = false;
    }
    else{
        wandering = true;
    }

    if (currentTimer <= 0)
    {
        if (getCurrentAnger() >= getMaxAnger()  && wandering == false)
        {
            attack(map);
        }
        else if (wandering == false && getCurrentAnger() > 3)
        {
            stalk(map);
        }
        else
        {
            wander(map);
        }
        currentTimer = moveTimer;
    }
    else
    {
        currentTimer--;
    }
    //cout << "anger: " << anger << endl;
}

void Monster::wander(Map* map) {
    // get random direction
    int direction = rand() % 4;
    int newX = getX();
    int newY = getY();

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
    if (playerX > getX()) {
        newX++;
    }
    if (playerY < getY()) {
        newY--;
    } 
    if (playerY > getY()) {
        newY++;
    }
    // move monster

    if(playerX == newX && playerY == newY){
        interact(&map->getTile(newX, newY), player);
    }
    move(newX, newY, map, "monster");
}

Entity* Monster::getDrop() {
    return drop;
}

void Monster::interact(Tile* tile, Player* _player) {
    enum Choice { ROCK, PAPER, SCISSORS };
    cout << "Monster attacks player" << endl;
    string choice;
    cout << "Enter your choice (0 = ROCK, 1 = PAPER, 2 = SCISSORS): ";
    cin >> choice;
    try{
        stoi(choice);
    }
    catch(invalid_argument e){
        cout << "Invalid choice, picking randomly" << endl;
        choice = to_string(rand() % 3);
    }
    Choice playerChoice = static_cast<Choice>(stoi(choice));
    Choice monsterChoice = static_cast<Choice>(rand() % 3);

    if (playerChoice == monsterChoice) {

        cout << "tie" << endl;
    } 
    else if ((playerChoice == ROCK && monsterChoice == SCISSORS) ||
               (playerChoice == PAPER && monsterChoice == ROCK) ||
               (playerChoice == SCISSORS && monsterChoice == PAPER)) {

        cout << "you win" << endl;
        changeCurrentAnger(-10);
        takeDamage(_player->getModAttack());
        if(getCurrentHealth() <= 0){
            tile->setMonster(nullptr);
        }
    } 
    else {
        cout << "the monster wins" << std::endl;
        _player->takeDamage(getModAttack());
    }
}