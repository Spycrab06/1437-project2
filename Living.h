#ifndef LIVING_H
#define LIVING_H

#include <string>

#include "Entity.h"
#include "Item.h"
using namespace std;

class Map;
class Living : public Entity {
    public:
        Living();
        Living(int, int, int, int, int, string, string);
        ~Living() override;


        void setHealth(int _health);
        void setMovement(int _movement);
        void setAttack(int _attack);
        void takeDamage(int damage);

        int getHealth();
        int getAttack();

        void startMove(Map* map) override;
        bool pickUpItem(Entity* item) override;

    private:
        int health;
        int attack;
};

#endif