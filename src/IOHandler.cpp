#include "IOHandler.h"
#include "ActionCommand.h"
#include "MoveCommand.h"
#include "HelpCommand.h"
#include "QuitCommand.h"
#include "UserInput.h"
#include "MapCommand.h"
#include "ChooseCommand.h"
#include "StateCommand.h"
#include "math.h"


using namespace std;


IOHandler::IOHandler(std::string prompt, std::shared_ptr<Game> game) : mGame(game), mPrompt(prompt){
    std::cout << prompt << std::endl;
    
    // Fügt ein Kommand zur liste mCommands hinzu
    registerCommand("action", make_unique<ActionCommand>(mGame));
    registerCommand("state", make_unique<StateCommand>(mGame));
    registerCommand("move", make_unique<MoveCommand>(mGame));
    registerCommand("help", make_unique<HelpCommand>());
    registerCommand("map", make_unique<MapCommand>(mGame));
    registerCommand("choose", make_unique<ChooseCommand>(mGame));
    registerCommand("quit",make_unique<QuitCommand>());
}



// Funktion zum hinzufügen von Kommandos zur Liste mCommands
void IOHandler::registerCommand(const std::string& command_name, std::unique_ptr<ICommand> command_function) {
    mCommands[command_name] = std::move(command_function);
    return;
}



// Funktion aktualisiert aktuellen Wurm
void IOHandler::updateWorm(shared_ptr<Worm> worm) {
    mGame->setCurrentWorm(worm);
}



// Funktion aktualisiert aktuellen Spieler
void IOHandler::updatePlayer(shared_ptr<Player> player) {
    mGame->setCurrentPlayer(player);
}



// Funktion fragt User nach Input
void IOHandler::getUserInput() {
    vector<string> order;
    while (true) {
        //Ruft UserInput auf
        std::cout << endl << mPrompt << " ";
        order = readUserInput();
        //Überprüft ob Eingabe leer
        if (order.empty()) {
            std::cout << "No command entered, please insert command" << std::endl; 
            continue; //Startet While-Schleife von vorne
        }
        // Nimmt erstes Wort aus dem String
        std::string command_name = order[0];
        // Erstellt neuen sting ohne Command
        std::vector<std::string> args(order.begin() + 1, order.end());
        //Schaut ob eingegebenes Kommando In UserInput in Tabelle der Kommandos enthalten ist
        auto it = mCommands.find(command_name);
        if (it != mCommands.end()) {
            if(command_name == "action") {
                mWormFired = true;
            }
            it->second->execute(args);
            break;
        } 
        //Gibt Fehler aus falls Kommando nicht gefunden und startet Schleife neu
        else {
            std::cout << "[ERROR] invalid parameter!\n " << command_name << std::endl;
        }
    }    
}



// Game Loop
void IOHandler::run() {
 // Initialize player indices
    int currentPlayerIndex = 0;
    int currentWormIndex = 0;
    while (!mGame->isGameOver()) {

        for (auto player : mGame->getPlayers()) {
            mGame->printMap();
            // Players turn
            updatePlayer(player);
            nextTurn(currentWormIndex);
            if (mGame->isGameOver()) break; // SPIEL VORBEI

        }
        currentWormIndex++;
    }
    mGame->printWinner();
}



// Funktion führt einzelnen Schritt aus
void IOHandler::nextTurn(int &currentWormIndex) {
    // Get the current worm and cast it to Worm*
    currentWormIndex = currentWormIndex % mGame->getCurrentPlayer()->numWorms();
    // Lese Wurm aus Player aus
    auto currentWorm = mGame->getCurrentPlayer()->getWorms().at(currentWormIndex);
    updateWorm(currentWorm);
    // Reset conditions for the new turn
    mWormTookDamage = false;
    mWormFired = false;
    std::cout << "Player " << mGame->getCurrentPlayer()->getId() << " Worm " << currentWorm->getName() << " (" << currentWorm->getID() <<
     ") at (" <<currentWorm->getPos().x << "," << currentWorm->getPos().y << ") is ready" << endl;
    // Loop läuft bis Spieler Turn vorbei ist
    while (!mGame->isGameOver() && !mWormFired && !mWormTookDamage) {
        int oldXP = currentWorm->getXP();
        getUserInput();
        mGame->getMap()->letItFall();
        // Schaut ob Worm schaden henommen hat
        int newXP =  currentWorm->getXP();
        if (oldXP != newXP) mWormTookDamage = true;
    }
}