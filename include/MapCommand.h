#ifndef MAPCOMMAND_H
#define MAPCOMMAND_H

#include "ICommand.h"


class MapCommand: public ICommand {
    public:
        MapCommand(std::shared_ptr<Game> game) : ICommand(game) {}
        ~MapCommand() override {}

        void execute(std::vector<std::string> args) override {
            mGame->printMap();
        }
};


#endif // MAPCOMMAND_H
