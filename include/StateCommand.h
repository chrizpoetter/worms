#ifndef STATECOMMAND_H
#define STATECOMMAND_H

#include "ICommand.h"
#include "Player.h"
#include "Worm.h"
#include <iostream>

class StateCommand: public ICommand {
    public:
        StateCommand(std::shared_ptr<Game> game) : ICommand(game) {}
        ~StateCommand(){}

        void execute(std::vector<std::string> args) override {
            std::cout << "current player: " << mGame->getCurrentPlayer()->getId() << std::endl;
            std::cout << "current worm: " << mGame->getCurrentWorm()->getName() << " (" <<mGame->getCurrentWorm()->getID() << ")" << std::endl;
            mGame->getCurrentWorm()->printInventory();
            mGame->printPlayers();        
        }
};



#endif // STATECOMMAND_H






