#ifndef HELP_H
#define HELP_H

#include <iostream>


void helpfunction(){
    std::cout << "\nAvailable Commands:\n"
                << "  move [left/right] [0..3]\n"
                <<"    Move your worm.\n"
                <<"  choose [weapon]\n"
                <<"    Select your weapon.\n"
                <<"  action [l/r/d/u/ld/rd/lu/ru]\n"
                <<"    Shoots current weapon.\n"
                <<"    Activates blowtorch.\n"
                <<"  action\n"
                <<"    Activates melee attack.\n"
                <<"  action [row] [col]\n"
                <<"    Teleports to coordinate.\n"
                <<"  action [col]\n"
                <<"    Airstrike.\n"
                <<"  action idle\n"
                <<"    Do nothing.\n"
                <<"  quit\n"
                <<"    End the game.\n"
                <<"  help\n"
                <<"    Display this help.\n"
                <<"  state\n"
                <<"    Print the current game state.\n";
}

#endif