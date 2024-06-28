#ifndef MELEE_H
#define MELEE_H

#include <iostream>
#include <memory>
#include "Game.h"
#include "IWeapons.h"

using namespace std;

class Melee : public IWeapons {
        private:
        std::shared_ptr<Game> mGame;
        
    public:
        Melee(std::shared_ptr<Game> game) : IWeapons("melee", 1, 50, 1), mGame(game) {}

        ~Melee(){}
        void shoot(int x, int y, std::string direction) override {
            if (mAmmo <= 0) {
                std::cout << "No ammo left!" << std::endl;
                return;
            }

            // Schaden durch Waffe
            mGame->getMap()->damageTile(x, y-1, mDamage, false);   // Up
            mGame->getMap()->damageTile(x+1, y-1, mDamage, false); // Upright
            mGame->getMap()->damageTile(x+1, y, mDamage, false);   // Right
            mGame->getMap()->damageTile(x+1, y+1, mDamage, false); // Downright
            mGame->getMap()->damageTile(x, y+1, mDamage, false);   // Down
            mGame->getMap()->damageTile(x-1, y-1, mDamage, false); // Downleft
            mGame->getMap()->damageTile(x-1, y, mDamage, false);   // Left
            mGame->getMap()->damageTile(x-1, y-1, mDamage, false); // Upleft
            
            removeAmmo();
        }
};  
    


#endif // MELEE_H