#ifndef AIRSTRIKE_H
#define AIRSTRIKE_H

#include <iostream>
#include "IWeapons.h"
#include "Worm.h"
#include "Game.h"

using namespace std;

class Airstrike : public IWeapons {
    private:
    std::shared_ptr<Game> mGame;

    public:
        Airstrike(std::shared_ptr<Game> game) : IWeapons("airstrike", 1, 20, 1), mGame(game) {}
        ~Airstrike(){}


        void shoot(int x, int y, std::string direction) override {
            if (mAmmo <= 0) {
            std::cout << "No ammo left!" << std::endl;
            return;
            }

            // Schaden durch Waffe
            mGame->getMap()->damageTile(x, y, mDamage, true);   // Impact point

            // Das Blöcke fallen
            mGame->getMap()->dealFall(x, y);   // Impact point

            removeAmmo();
        }
    };  

#endif //AIRSTRIKE_H