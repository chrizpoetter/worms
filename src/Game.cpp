#include <iostream>
#include "Game.h"
#include "Player.h"

using namespace std;



int Game::numPlayers() {
    return mPlayers.size();
}



// Printed Map
void Game::printMap() {
    mMap->print();
    return;
}



// Gibt zurück ob Spiel vorbei ist
bool Game::isGameOver() {
    for (auto player : mPlayers) {
        if (player->numWorms() == 0) return true;
    }
    return false;
}


// Gibt Gewinner aus
void Game::printWinner() {
    bool draw = true;
    // Checkt ob Game ein Unentschieden ist
    for (const auto& player : mPlayers) {
        if (player->numWorms() != 0) {
            draw = false;
        }
    }
    if (draw) {
        cout << "END: Draw!" << endl;
        return;
    }
    // Gibt Gewinner aus.
    for (const auto& player : mPlayers) {
        if (player->numWorms() == 0) {
            for (auto& otherPlayer : mPlayers) {
                if (otherPlayer != player) {
                    std::cout << "END: Player " << otherPlayer->getId() << " wins!" << std::endl;
                    return;
                }
            }
        }
    }
}



// Printed alle Spieler
void Game::printPlayers() {
    for (auto& player : mPlayers) {
        cout << "worms of player " << player->getId() << endl;
        player->printWorms();
    }
    cout << endl;
}



// Gibt Map zurück
std::shared_ptr<Map> Game::getMap() {return mMap;}



// Gibt Player aus
std::vector<std::shared_ptr<Player>> Game::getPlayers() {return mPlayers;}



// Gibt aktuellen Spieler zurück
std::shared_ptr<Player> Game::getCurrentPlayer() {return mCurrentPlayer;}



// Gibt aktuellen Wurm zurück
shared_ptr<Worm> Game::getCurrentWorm() {return mCurentWorm;}



// Gibt aktuellen Spieler zurück
void Game::setCurrentPlayer(std::shared_ptr<Player> player) { mCurrentPlayer = player; }



// Gibt aktuellen Wurm zurück
void Game::setCurrentWorm(shared_ptr<Worm> worm) { mCurentWorm = worm; }