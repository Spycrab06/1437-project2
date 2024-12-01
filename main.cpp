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
#include "saveFile.h"

using namespace std;

void spawnMonster(vector<Monster*> monsters, Map* mainMap, Player* player){
    int monsterX = rand() % mainMap->getWidth();
    int monsterY = rand() % mainMap->getHeight();
    int randHealth = rand() % 5 + 1;
    int randFollowDist = rand() % 3 + 1;
    int randAngerThreshold = rand() % 6 + 8;
    // int _health, int _attack, int _x, int _y, int _color, string _character, string _name, Player* _player, int _moveTimer, int _sight, int _followDist, int _angerThreshold, int _invSize) : Living(_health, _attack, _x, _y, _color, _sight, _character, _name, _invSize)
    Monster* monster = new Monster(randHealth, 1, monsterX, monsterY, 12, "M ", "Monster", player, 1, 4, randFollowDist, randAngerThreshold, 1);
    monsters.push_back(monster);
}

void playerMenu(Player* player, Map* map){
    // print threat
    // print health
    // print inventory
    // interact with inventory or move
    cout << endl << endl;
    cout << "=== Player Menu ===" << endl;
    cout << "Health: " << player->getCurrentHealth() << "/" << player->getModHealth() << endl;
    cout << "Aggro: " << player->getCurrentAnger() << endl;
    cout << "Inventory: " << endl;
    
    // prints the inventory, and if the item is sellable it will print the value
    for (int i = 0; i < player->getItemCount(); i++) {
        Item* item = player->getItemFromInventory(i);
        cout << i << ". " << item->getName();
        if (item->isSellable()) {
            cout << " (Value: " << item->getValue() << ")";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Enter a number to interact with inventory or move (W,A,S,D): ";
    string choice;
    cin >> choice;

    // if choice is not a number, pass it to player move
   try{
        if(stoi(choice) == 0 || stoi(choice) == 1 || stoi(choice) == 2 || stoi(choice) == 3){
            player->getItemFromInventory(stoi(choice))->useItem(player);
        }
    }
    catch(invalid_argument e){
        player->startMove(map, choice);
    }
}

// dungeon stuff
bool dungeonLoop(Player* player){
    // create and populate main important dungeon stuff
    vector<Monster*> monsters;
    int randMapX = rand() % 10 + 15;
    int randMapY = rand() % 10 + 15;
    //int randMapSize = rand() % 8 + 8;
    Map* mainMap = new Map(randMapX, randMapY);
    mainMap->populateMap();

    // create player
    int randX = rand() % (mainMap->getWidth());
    int randY = rand() % (mainMap->getHeight());
    // health, attack, x, y, color, character, name
    player->setX(randX);
    player->setY(randY);
    mainMap->getTile(randX, randY).setEntity(player);

    // create monsters
    int initialNumMonsters = 2;
    for (int i = 0; i < initialNumMonsters; ++i) {
        spawnMonster(monsters, mainMap, player);
    }

    // variables to track
    int turn = 1;
    bool playerAlive = true;

    mainMap->printMap(player);

    // main dungeon loop
    while(playerAlive){
        try
        {
            player->statCheck();

            // loop through monsters and check items and if they are dead
            for (auto it = monsters.begin(); it != monsters.end(); it++) {
                Monster* monster = *it;
                if (monster->statCheck() == 1) {
                    // if it died, delete it
                    delete monster;
                    it = monsters.erase(it);
                }
            }
            // clears the console
            for(int i = 0; i < 25; i++){
                cout << endl;
            }


            mainMap->printMap(player);
            playerMenu(player, mainMap);

            for (Monster* monster : monsters) {
                monster->startMove(mainMap, "");
            }

            // every set number of turns, add a new monster
            if(turn % 20 == 0){
                spawnMonster(monsters, mainMap, player);
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
    Shop* shop = new Shop("items.txt", 4);

    // Main game loop
    while (true) {
        cout << endl << "=== Welcome to the Game Shop ===" << endl;
        cout << "1. View Shop and Buy Items" << endl;
        cout << "2. Bulk Sell Valubles" << endl;
        cout << "3. Sell Specific Item" << endl;
        cout << "4. View Inventory" << endl;
        cout << "5. Exit Shop" << endl;
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
                cout << "Inventory: " << endl;
                for (int i = 0; i < player->getItemCount(); i++) {
                    Item* item = player->getItemFromInventory(i);
                    cout << i << ". " << item->getName() << " (Value: " << item->getValue() << ")";
                    cout << endl;
                }

                cout << "Enter the number of the item to sell: ";
                int itemIndex;
                cin >> itemIndex;
                if (itemIndex >= 0 && itemIndex < player->getItemCount()) {
                    money += player->getItemFromInventory(itemIndex)->getValue();
                    player->deleteItemFromInventory(itemIndex);
                    cout << "Item sold!" << endl;
                } 
                else {
                    cout << "Invalid item index." << endl;
                }
                break;
            case 4:
                cout << "\n=== Player Inventory ===\n";
                for (int i = 0; i < player->getItemCount(); ++i) {
                    if (player->getItemFromInventory(i)) {
                        cout << i + 1 << ". " << player->getItemFromInventory(i)->getName()
                             << " (Value: " << player->getItemFromInventory(i)->getValue() << ")\n";
                    } 
                    else {
                        cout << i + 1 << ". [Empty Slot]\n";
                    }
                }
                cout << "Money: " << money << endl;;
                break;
            case 5:
                cout << "Goodbye" << endl;
                return 0;
            default:
                cout << "invalid choice. try again." << endl;
                break;
        }
    }
}

void resetPlayerStats(Player* player){
    if(player->getCurrentHealth() + 2 <= player->getModHealth()){
        player->setCurrentHealth(player->getCurrentHealth() + 2);
    }
    else{
        player->setCurrentHealth(player->getModHealth());        
    }

    player->setCurrentAnger(0);
}

void saveGame(const Player* player, int money, int quota) {
    SaveFile saveFile(quota, money, player->getCurrentHealth(), player->getInventory());
    saveFile.save("savefile.dat");
    cout << "Game saved!" << endl;
}

bool loadGame(Player* player, int& money, int& quota) {
    SaveFile saveFile(0, 0, 0, {});
    saveFile.load("savefile.dat");
    if (saveFile.getQuota() == 0 && saveFile.getMoney() == 0 && saveFile.getHealth() == 0) {
        return false; // Failed to load
    }

    quota = saveFile.getQuota();
    money = saveFile.getMoney();
    player->setCurrentHealth(saveFile.getHealth());
    player->setInventory(saveFile.getInventory());
    cout << "Game loaded!" << endl;
    return true;
}

int main()
{
    srand(time(0));
    // (int _health, int _attack, int _x, int _y, int _color, string _character, string _name, int _sight, int _invSize)
    Player* player = new Player(5, 1, 0, 0, 3, "P ", "Player", 3, 4);
    int money = 10;
    int quota = 19999;
    cout << endl;
    cout << "Do you want to load the game? (y/n): " << endl;
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (!loadGame(player, money, quota)) {
            cout << "Failed to load game. Starting a new game." << endl;
        }
    }


    // if player survives, returns true, if not, returns false
    while(dungeonLoop(player)){
        resetPlayerStats(player);
        saveGame(player, money, quota);
        shopLoop(player, money);
    }

    delete player;

    return 0;
}