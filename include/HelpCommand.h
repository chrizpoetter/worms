#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "ICommand.h"
#include "Help.h"

class HelpCommand: public ICommand {
    public:
        ~HelpCommand() override {}

        void execute(std::vector<std::string> args) override {
            helpfunction();
        }
};

#endif // HELPCOMMAND_H