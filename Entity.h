#ifndef ENTITY_H
#define ENTITY_H

#include <string>


using namespace std;
class Tile;
class Map;

class Entity {
    public:
        Entity();
        Entity(int, int, int, string, string);

        void move(int _x, int _y, Map* _map, string type);

        int getX();
        int getY();
        int getColor();
        string getCharacter();
        string getName();

        void setColor(int _color);
        void setCharacter(string _character);
        void setX(int);
        void setY(int);
        void setName(string _name);
        Entity& operator=(const Entity& other);

        virtual void interact(Tile* tile, Entity* player);
        virtual void startMove(Map* map);
        virtual bool pickUpItem(Entity* item);
    private:
        int x, y;
        int color;
        string character;
        string name;
};

#endif