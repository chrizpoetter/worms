#ifndef WURMFACTORY_H
#define WURMFACTORY_H

#include "Worm.h"
#include "Random.h"
#include <iostream>

class WurmFactory {
public:
//static factory method
    static std::shared_ptr<Worm> create(std::shared_ptr<Player> player, int id, std::shared_ptr<se::Random> random, int x, int XP) {
        //Worm erstellen
        return std::make_shared<Worm>(player, id ,random->getWormName(), x, XP);
    };
};


#endif // WURMFACTORY_H