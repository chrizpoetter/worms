/* Interface for Tiles */
#ifndef ITILE_H
#define ITILE_H

#include <memory>
#include "IObserver.h"

class ITile {
    public:
        virtual ~ITile() = default; 
        virtual char getImg() = 0;
        virtual bool getSolid() = 0;
        virtual bool isWater() = 0;
        virtual bool isMovable() = 0;
        virtual bool isWorm() = 0;
        virtual bool hit (bool destroyTiles, int damage) = 0;

};

#endif // ITILE_H