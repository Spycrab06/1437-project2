#include <iostream>
#include <vector>

#include "Map.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

int main()
{
    srand(time(0));
    Map* newMap = new Map(15, 15);

    // health, attack, x, y, color, character, name
    
    newMap->populateMap();
    int randX = rand() % newMap->getWidth();
    int randY = rand() % newMap->getHeight();
    Player* player = new Player(10, 1, randX, randY, 3, "P ", "Player", 3);
    newMap->getTile(randX, randY).setEntity(player);



    // create monsters
    int initialNumMonsters = 2;
    vector<Monster*> monsters;
    for (int i = 0; i < initialNumMonsters; ++i) {
        int monsterX = rand() % newMap->getWidth();
        int monsterY = rand() % newMap->getHeight();
        // health, attack, x, y, color, character, name, player, moveTimer, sight, followDist, angerThreshold
        Monster* monster = new Monster(10, 1, monsterX, monsterY, 12, "M ", "Monster", player, 1, 4, 2, 10);
        monsters.push_back(monster);
    }

    newMap->printMap(player);

    int turn = 1;

    while(true){
        player->startMove(newMap);
        for (Monster* monster : monsters) {
            monster->startMove(newMap);
        }
        newMap->printMap(player);


        // every 10 turns add a new monster
        if(turn % 20 == 0){
            int monsterX = rand() % newMap->getWidth();
            int monsterY = rand() % newMap->getHeight();
            Monster* newMonster = new Monster(10, 1, monsterX, monsterY, 12, "M ", "Monster", player, 1, 4, 2, 10);
            monsters.push_back(newMonster);
        }

        turn++;
    }

    delete player;
    for (Monster* monster : monsters) {
        delete monster;
    }
    delete newMap;

    return 0;
}