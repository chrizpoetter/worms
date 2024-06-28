/* Earth Tile Class */

#ifndef EARTHTILE_H
#define EARTHTILE_H

#include "ITile.h"

class EarthTile : public ITile {
    private:
        char mSymbol = 'E';
        int mXP = 1;
        bool mSolid = true;
        bool mWater = false;
        bool mMovable = false;
        bool mWorm = false;

    public:
        ~EarthTile() override {}; 
        // Gibt Symbol bzw. Bild des Blocks aus
        char getImg() override { return this->mSymbol; }
        // Gibt an ob der Block fest ist
        bool getSolid() override {return this->mSolid;}
        // Gibt an ob der der Block Wasser ist
        bool isWater() override {return this->mWater;}
        // Gibt an ob Block beweglich ist
        bool isMovable() override {return this->mMovable;}
        // Gibt an ob Block Wurm ist
        bool isWorm() override {return this->mWorm;}
        // Gibt Block Schaden
        // Gibt TRUE zurück falls Block kaputt, ansonsten FALSE
        bool hit(bool destroyTiles, int damage) override {
            if (destroyTiles) mXP -= damage;
            if (mXP > 0) return false;
            return true;
        }

};


#endif // EARTHTILE_H