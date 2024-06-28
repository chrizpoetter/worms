#ifndef QUITCOMMAND_H
#define QUITCOMMAND_H

#include "ICommand.h"
#include <iostream>

class QuitCommand: public ICommand {
    void execute(std::vector<std::string> args)override {
        std::cout << "Quit command executed. Quit Game." << std::endl;
        // Add your quit logic here, e.g., cleanup resources
        exit(0);
    }

};




#endif // QUITCOMMAND_H