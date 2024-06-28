#ifndef GUN_H
#define GUN_H

#include <iostream>
#include <memory>
#include "Game.h"
#include "IWeapons.h"

using namespace std;

class Gun : public IWeapons {
     private:
        std::shared_ptr<Game> mGame;
        
    public:
        Gun(std::shared_ptr<Game> game) : 
        IWeapons("gun", 100000 , 25, 1), mGame(game) {}

        ~Gun(){}
        void shoot(int x, int y, std::string direction) override {
            // Schaden durch Waffe
            mGame->getMap()->damageTile(x, y, mDamage, true);   // Impact point
         
            // Das Blöcke fallen
            mGame->getMap()->dealFall(x, y);   // Impact point
      
            removeAmmo();
        }
};


#endif // GUN_H