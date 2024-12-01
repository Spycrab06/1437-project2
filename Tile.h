#ifndef TILE_H
#define TILE_H

#include <string>
#include <stdlib.h>
#include "Item.h"
#include "Building.h"

using namespace std;
class Entity;
class Map;
class Tile {
    public:
        Tile(int, int, Entity*, Entity*, Entity*);
        Tile(int, int);
        Tile();
        ~Tile();

        void printTile(bool);
        string changeColor(int colorCode);

        void setEntity(Entity* _entity);
        Entity* getEntity();

        void setMonster(Entity* _monster);
        Entity* getMonster();

        void setInteractable(Entity* interactable);
        Entity* getInteractable();

        int getX();
        int getY();
        void setX(int _x);
        void setY(int _y);

        void startInteract();

        int distanceToPlayerX(Player* player);
        int distanceToPlayerY(Player* player);

    private:
        // this is player, i just dont want to rename it
        Entity* entity;
        Entity* monster;
        Entity* interactable;

        int x, y;
};

#endif