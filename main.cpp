#include <iostream>
#include <vector>

#include "Map.h"
#include "Entity.h"
#include "Living.h"
#include "Item.h"
#include "Building.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "Shop.h"

using namespace std;

// dungeon stuff
bool dungeonLoop(Player* player){
    // create and populate main important dungeon stuff
    vector<Monster*> monsters;
    Map* mainMap = new Map(30, 30);
    mainMap->populateMap();

    // create player
    int randX = rand() % mainMap->getWidth();
    int randY = rand() % mainMap->getHeight();
    // health, attack, x, y, color, character, name
    player->setX(randX);
    player->setY(randY);
    mainMap->getTile(randX, randY).setEntity(player);

    // create monsters
    int initialNumMonsters = 3;
    for (int i = 0; i < initialNumMonsters; ++i) {
        int monsterX = rand() % mainMap->getWidth();
        int monsterY = rand() % mainMap->getHeight();
        // health, attack, x, y, color, character, name, player, moveTimer, sight, followDist, angerThreshold
        Monster* monster = new Monster(3, 1, monsterX, monsterY, 12, "M ", "Monster", player, 1, 4, 2, 10);
        monsters.push_back(monster);
    }

    // variables to track
    int turn = 1;
    bool playerAlive = true;

    // main dungeon loop
    while(playerAlive){
        try
        {
            player->startMove(mainMap);
            for (Monster* monster : monsters) {
                monster->startMove(mainMap);
            }
            mainMap->printMap(player);
            player->statCheck();

            // every set number of turns, add a new monster
            if(turn % 20 == 0){
                int monsterX = rand() % mainMap->getWidth();
                int monsterY = rand() % mainMap->getHeight();
                Monster* newMonster = new Monster(3, 1, monsterX, monsterY, 12, "M ", "Monster", player, 1, 4, 2, 10);
                monsters.push_back(newMonster);
            }

            turn++;
        }
        // using this as an interrupt for the loop if something should stop it
        catch(bool e)
        {
            // gets thrown from structure if player exits
            if(e == true)
            {
                cout << "You exited the dungeon!" << endl;
                break;
            }
            // gets thrown from player in statCheck if player dies
            else{
                cout << "You died!" << endl;
                playerAlive = false;
                break;
            }
        }
    }

    for (Monster* monster : monsters) {
        delete monster;
    }
    delete mainMap;
    return playerAlive;
}

bool shopLoop(Player* player, int& money){
    Shop* shop = new Shop("items.txt");


    // Main game loop
    while (true) {
        cout << "\n=== Welcome to the Game Shop ===" << endl;
        cout << "1. View Shop and Buy Items" << endl;
        cout << "2. Sell Items from Inventory" << endl;
        cout << "3. View Inventory" << endl;
        cout << "4. Exit Shop" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (!cin) {
            // Handle invalid input
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                shop->openShopMenu(player, money);
                break;
            case 2:
                shop->sellItems(player, money);
                break;
            case 3:
                cout << "\n=== Player Inventory ===\n";
                for (int i = 0; i < player->getItemCount(); ++i) {
                    if (player->getItemFromInventory(i) != nullptr) {
                        cout << i + 1 << ". " << player->getItemFromInventory(i)->getName()
                             << " (Value: " << player->getItemFromInventory(i)->getValue() << ")\n";
                    } else {
                        cout << i + 1 << ". [Empty Slot]\n";
                    }
                }
                cout << "Money: " << money << endl;;
                break;
            case 4:
                cout << "Goodbye" << endl;
                return 0;
            default:
                cout << "invalid choice. try again." << endl;
                break;
        }
    }
}

int main()
{
    srand(time(0));
    Player* player = new Player(5, 1, 0, 0, 3, "P ", "Player", 3);
    int money = 50;

    // if player survives, returns true, if not, returns false
    while(dungeonLoop(player)){
        shopLoop(player, money);
    }

    delete player;

    return 0;
}