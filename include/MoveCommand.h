#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <iostream>
#include "ICommand.h"
#include "Worm.h"

class MoveCommand: public ICommand {
    public:
        MoveCommand(std::shared_ptr<Game> game) : ICommand(game) {}
        ~MoveCommand() override {}


        void execute(std::vector<std::string> args) override {
            int steps = 0;
            if (args.size() < 2) {
                std::cout << "Command must include direction and steps (i.e. 'move l 2') " << std::endl;
                return;
            }
            // Liest steps ein
            try {steps = stoi(args.at(1));}
            catch (...) {
                std::cout << "[Warning] Invalid number!" << std::endl;
                return;
            }
            // Kontrolliert ob Schritte zwischen 1 und 3 sind
            if ( steps < 0 || steps > 3) {
                std::cout << "Steps must be between 1 and 3." << std::endl;
                return; 
            }
            // Bestimmt Richtung‚
            if (args.at(0) == "r");
            else if (args.at(0) == "l") steps = steps * -1;
            else {
                std::cout << "Direction must be 'r' or 'l'" << std::endl;
                return;
            }
            mGame->getMap()->moveWorm(mGame->getCurrentWorm(), steps);
        }

};

#endif // MOVECOMMAND_H