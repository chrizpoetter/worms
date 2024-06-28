// Interface for Commands

#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <vector>
#include <memory>
#include <string>
#include "Game.h"

class ICommand {
    protected:
        std::shared_ptr<Game> mGame;

    public:
        ICommand(){}
        ICommand(std::shared_ptr<Game> game) : mGame(game) {}
        virtual ~ICommand() {}
        virtual void execute (std::vector<std::string> args) = 0; 
    
};

#endif // ICOMMAND_H