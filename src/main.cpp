#include "GameBuildDirector.h"
#include "IOHandler.h"
#include "INIReader.h"

#include <memory>
#include <iostream>

//using namespace se;
using namespace std;

int main(int argc, char* argv[]){

    string config_file;

    if (argc < 2) {
        cout << "No config file provided as command line argument!" << endl;
        cout << "Please provide a valid config file for our game:" << endl;
        getline(cin, config_file);
    }
    else {
        config_file = argv[1];
    }

    auto ini_reader = make_shared<INIReader>(config_file);
    if (ini_reader->ParseError() == -1) {
        cerr << "Could not open the config.ini file" << endl;
        return -1;
    } else if (ini_reader->ParseError() != 0) {
        cerr << "Error while parsing the config.ini file" << endl;
        return -1;
    }


   // Starting Game
    try {
        auto game_build = make_unique<GameBuildDirector>();

        auto game = game_build->construct(ini_reader);
        
        auto iohandler = make_unique<IOHandler>(ini_reader->Get("general","PROMPT",">"), std::move(game));
        iohandler->run();

    } catch(const std::exception& e) {
        cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}
