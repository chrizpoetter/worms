/* Worm Tile Class */

#ifndef WORMTILE_H
#define WORMTILE_H

#include "ITile.h"
#include "Worm.h"

class WormTile : public ITile {
    private:
        friend class WormTileBuilder;
        std::shared_ptr<Worm> mWorm;
        bool mSolid = true;
        bool mWater = false;
        bool mMovable = true;
        bool mBoolWorm = true;

    public:

        ~WormTile() override {};
        // TODO: Implementieren wenn Wurm Klasse so weit ist
        char getImg() override {
            return this->mWorm->getSymbol(); 
        }
        // Gibt an ob der Block fest ist
        bool getSolid() override {return this->mSolid; }
        // Gibt XP an
        int getXP() { return mWorm->getXP(); }
        // Gibt an ob der der Block Wasser ist
        bool isWater() override {return this->mWater; }
        // Gibt an ob Block beweglich ist
        bool isMovable() override {return this->mMovable;}
        // Gibt an ob Block Wurm ist
        bool isWorm() override {return this->mBoolWorm;}
        // Gibt Pointer zu Wurm
        std::shared_ptr<Worm> getWorm() {return this->mWorm;}
        // Gibt Block Schaden
        // Gibt TRUE zurück false Block kaputt, ansonsten FALSE
        bool hit(bool destroyTiles, int damage) override {
            int XP = getXP();
            XP -= damage;
            mWorm->hitDamage(damage);
            if (XP > 0) return false;
            return true;
            }

};


#endif // WORMTILE_H