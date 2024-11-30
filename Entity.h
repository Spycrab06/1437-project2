#ifndef ENTITY_H
#define ENTITY_H

#include <string>


using namespace std;
class Tile;
class Map;
class Player;

class Entity {
    public:
        Entity();
        Entity(int, int, int, string, string);
        virtual ~Entity();
        void move(int _x, int _y, Map* _map, string type);

        int getX() const;
        int getY() const;
        int getColor() const;
        string getCharacter() const;
        string getName() const;

        void setColor(int _color);
        void setCharacter(string _character);
        void setX(int);
        void setY(int);
        void setName(string _name);

        virtual Entity& operator=(const Entity& other);
        virtual void interact(Tile* tile, Player* player);
        virtual void startMove(Map* map);
        virtual bool pickUpItem(Entity* item);
    private:
        int x, y;
        int color;
        string character;
        string name;
};

#endif