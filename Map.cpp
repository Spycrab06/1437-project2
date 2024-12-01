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

Map::~Map() {
    for (int i = 0; i < height; i++) {
        delete[] grid[i];  // Delete each row
    }
    delete[] grid;  // Delete array of pointers
}

void Map::printMap(Player* player){
    int sightRange = player->getModSightRange();

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



void Map::populateMap() {
    // define the types
    enum ItemType {TRAP, TREASURE, MAGIC, BERRIES, EXIT, ITEM_TYPE_COUNT};
    int baseCounts[ITEM_TYPE_COUNT] = {25, 15, 0, 0, 1};
    int variances[ITEM_TYPE_COUNT] = {30, 20, 5, 5, 3};

    // add varience
    int actualCounts[ITEM_TYPE_COUNT];
    for (int i = 0; i < ITEM_TYPE_COUNT; ++i) {
        actualCounts[i] = baseCounts[i] + (rand() % (variances[i] + 1));
    }

    // trap
    for (int i = 0; i < actualCounts[TRAP]; ++i) {
        int y = rand() % height;  // First dimension
        int x = rand() % width;   // Second dimension
        grid[y][x].setInteractable(new Building(x, y, 4, "x ", "Trap"));
    }

    // treasure
    for (int i = 0; i < actualCounts[TREASURE]; ++i) {
        int y = rand() % height;
        int x = rand() % width;
        int randValue = rand() % 10 + 5;
        grid[y][x].setInteractable(new Item(randValue, x, y, 6, 1, 1, "Treasure", "O ", "Treasure", true, false));
    }

    // magic treasure
    for (int i = 0; i < actualCounts[MAGIC]; ++i) {
        int y = rand() % height;
        int x = rand() % width;
        int randValue = rand() % 5 + 15;
        grid[y][x].setInteractable(new Item(randValue, x, y, 5, 1, 1, "Treasure", "U ", "Magic-Treasure", true, false));
    }

    // magic berries
    for (int i = 0; i < actualCounts[BERRIES]; ++i) {
        int y = rand() % height;
        int x = rand() % width;
        int randValue = rand() % 8 + 3;
        grid[y][x].setInteractable(new Item(randValue, x, y, 10, 1, -6, "Anger", "Q ", "Berries", true, false));
    }

    // escape
    for (int i = 0; i < actualCounts[EXIT]; ++i) {
        int y = rand() % height;
        int x = rand() % width;
        grid[y][x].setInteractable(new Building(x, y, 1, "E ", "Exit"));
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