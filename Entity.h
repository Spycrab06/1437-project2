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
        int getStartColor() const;
        int getModColor() const;
        string getStartCharacter() const;
        string getModCharacter() const;
        string getName() const;

        void setStartColor(int _color);
        void setModColor(int _color);

        void setStartCharacter(string _character);
        void setModCharacter(string _character);

        void setX(int);
        void setY(int);
        void setName(string _name);

        virtual Entity& operator=(const Entity& other);
        virtual void interact(Tile* tile, Player* player);
        virtual void startMove(Map* map, string inMove);
        virtual bool pickUpItem(Entity* item);
    private:
        int x, y;
        
        // 0: start color
        // 1: mod color
        int color[2];
        string character[2];

        string name;
};

#endif