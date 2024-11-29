#include <string>
#include <iostream>
#include <stdlib.h>
#include "Map.h"
#include "Tile.h"
#include "Player.h"

using namespace std;

Map::Map(){
    // shouldnt be used, but just in case
    // would be the same as the other one but just setting it to 10 or something
}

Map::Map(int _width, int _height){
    width = _width;
    height = _height;

    grid = new Tile*[height];

    for (int i = 0; i < height; i++) {
        grid[i] = new Tile[width];
        for (int j = 0; j < width; j++) {
            grid[i][j].setX(i);
            grid[i][j].setY(j);
        }
    }
}

Map::~Map(){
    delete[] grid;
}

void Map::printMap(Player* player){
    int playerX = player->getX();
    int playerY = player->getY();
    int sightRange = player->getSightRange();

    // height loop
    for(int i = 0; i < height; i++){
        bool printedSomething = false;

        // width loop
        for(int j = 0; j < width; j++){
            // get distance to player
            int distanceX = grid[i][j].distanceToPlayerX(player);
            int distanceY = grid[i][j].distanceToPlayerY(player);

            // if within sight range print it
            if (distanceX <= sightRange && distanceY <= sightRange) {
                grid[i][j].printTile(false);
                printedSomething = true;
            } 
            else {
                // printing hidden tile

                bool isEdgeX = (distanceX == sightRange + 1) && (distanceY <= sightRange + 1);
                bool isEdgeY = (distanceY == sightRange + 1) && (distanceX <= sightRange + 1);

                if (isEdgeX || isEdgeY) {
                    // if within a few tiles print it
                    grid[i][j].printTile(true);
                    printedSomething = true;
                } 
                else {
                    // dont print it
                }
            }
        }
        if(printedSomething){
            cout << endl;
        }
    }
}

int Map::getWidth() {return width;}
int Map::getHeight() {return height;}
Tile& Map::getTile(int x, int y) { return grid[x][y]; }



void Map::populateMap(){
    // define the types
    enum ItemType {TRAP, TREASURE, EXIT, ITEM_TYPE_COUNT};
    int baseCounts[ITEM_TYPE_COUNT] = {20, 10, 1};
    int variances[ITEM_TYPE_COUNT] = {20, 10, 3};

    // add varience
    int actualCounts[ITEM_TYPE_COUNT];
    for (int i = 0; i < ITEM_TYPE_COUNT; ++i) {
        actualCounts[i] = baseCounts[i] + (rand() % (variances[i] + 1));
    }

    // scatter items based on the counts

    // template
    /*
    for (int i = 0; i < actualCounts[___NEED_TO_CHANGE___]; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        // x, y, color, char, name
        grid[x][y].setInteractable(new Building(x, y, 0, ". ", "Template"));
    }
    */

    // trap
    for (int i = 0; i < actualCounts[TRAP]; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        grid[x][y].setInteractable(new Building(x, y, 4, "x ", "Trap"));
    }

    // treasure
    for (int i = 0; i < actualCounts[TREASURE]; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        grid[x][y].setInteractable(new Item(10, x, y, 6, "O ", "Treasure"));
    }

    // escape
    for (int i = 0; i < actualCounts[EXIT]; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        grid[x][y].setInteractable(new Building(x, y, 1, "E ", "Exit"));
    }

}

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