#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <string>
#include <memory>
#include <unordered_map>
#include "ICommand.h"
#include "Game.h"


class IOHandler {
    private:
        std::shared_ptr<Game> mGame;
        std::unordered_map<std::string, std::unique_ptr<ICommand> > mCommands;
        bool mWormFired;
        bool mWormTookDamage;
        std::string mPrompt; 


    public:

        IOHandler(std::string prompt, std::shared_ptr<Game> game);
        void registerCommand(const std::string& command_name, std::unique_ptr<ICommand> command_function);
        void run();
        void nextTurn(int &currenWormIndex);
        bool hasActionCommandExecuted() const;
        void getUserInput();
        void updateWorm(std::shared_ptr<Worm> worm);
        void updatePlayer(std::shared_ptr<Player> player);
};


#endif // IOHANDLER_H