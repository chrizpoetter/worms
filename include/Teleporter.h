#ifndef TELEPORTER_H
#define TELEPORTER_H

#include <iostream>
#include <memory>
#include "IWeapons.h"
#include "Game.h"

using namespace std;

class Teleporter : public IWeapons {
    private:
        std::shared_ptr<Game> mGame;

    public:
        Teleporter(std::shared_ptr<Game> game) : IWeapons("teleporter", 1, 0, 1), mGame(game) {}
        ~Teleporter(){}

        void shoot(int x, int y, std::string direction) {
            if (mAmmo <= 0) {
                std::cout << "No more teleportations left!" << std::endl;
                return;
            }

            removeAmmo();
        }

};  

#endif // TELEPORTER_H