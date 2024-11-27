#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include "Entity.h"
using namespace std;

class Map;
class Building : public Entity {
    public:
        Building();
        Building(int, int, int, string, string);
        ~Building() override;

        void interact(Tile* tile, Entity* player) override;
    private:

};

#endif