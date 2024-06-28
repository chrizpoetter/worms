/* Air Tile Class */

#ifndef AIRTILE_H
#define AIRTILE_H

#include "ITile.h"

class AirTile : public ITile {
    private:
        char mSymbol = ' ';
        bool mSolid = false;
        bool mWater = false;
        bool mMovable = false;
        bool mWorm = false;

    public:
        ~AirTile() override {};
        // Gibt Symbol bzw. Bild des Blocks aus
        char getImg() override { return this->mSymbol;}
        // Gibt an ob der Block fest ist
        bool getSolid() override {return this->mSolid;}
        // Gibt an ob der der Block Wasser ist
        bool isWater() override {return this->mWater;}
        // Gibt an ob Block beweglich ist
        bool isMovable() override {return this->mMovable;}
        // Gibt an ob Block Wurm ist
        bool isWorm() override {return this->mWorm;}
        // Gibt Block Schaden, Schaden ist immer Null
        // Gibt TRUE zurück false Block kaputt, ansonsten FALSE
        bool hit (bool destroyTiles, int damage) override {return false;}
};


#endif // AIRTILE_H