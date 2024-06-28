#ifndef CHOOSECOMMAND_H
#define CHOOSECOMMAND_H

#include "ICommand.h"
#include "Worm.h"

class ChooseCommand: public ICommand {
    public:
        ChooseCommand(std::shared_ptr<Game> game) : ICommand(game) {}
        ~ChooseCommand() override {}

        void execute(std::vector<std::string> args) override {
            std::string  weaponName = args.at(0);
            mGame->getCurrentWorm()->chooseWeapon(weaponName);
        }

};

#endif // CHOOSECOMMAND_H