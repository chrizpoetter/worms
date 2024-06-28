#ifndef BAZOOKA_H
#define BAZOOKA_H


#include <iostream>
#include <memory>
#include "Game.h"
#include "IWeapons.h"

class Bazooka : public IWeapons {
    private:
        std::shared_ptr<Game> mGame;
        
    public:
        Bazooka(std::shared_ptr<Game> game) : IWeapons("bazooka", 1, 40, 1), mGame(game) {}

        ~Bazooka(){}
        void shoot(int x, int y, std::string direction) override {
            if (mAmmo <= 0) {
                std::cout << "No ammo left!" << std::endl;
                return;
            }

            // Schaden durch Waffe
            mGame->getMap()->damageTile(x, y, mDamage, true);   // Impact point
            mGame->getMap()->damageTile(x, y-1, mDamage, true); // Up
            mGame->getMap()->damageTile(x+1, y, mDamage, true); // Right
            mGame->getMap()->damageTile(x, y+1, mDamage, true); // Down
            mGame->getMap()->damageTile(x-1, y, mDamage, true); // Left
            

            // Das Blöcke fallen
            mGame->getMap()->dealFall(x, y);   // Impact point
            mGame->getMap()->dealFall(x, y-1); // Up
            mGame->getMap()->dealFall(x+1, y); // Right
            mGame->getMap()->dealFall(x, y+1); // Down
            mGame->getMap()->dealFall(x-1, y); // Left

            removeAmmo();
        }
    
};  

#endif // BAZOOKA_H