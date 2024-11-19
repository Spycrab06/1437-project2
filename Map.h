#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

class Player;
class Tile;
class Map {
    public:
        Map();
        Map(int, int);
        ~Map();

        void printMap(Player* player);

        int getWidth();
        int getHeight();
        Tile& getTile(int x, int y);

        void populateMap();

    private:
        int width;
        int height;
        Tile** grid;
};

#endif