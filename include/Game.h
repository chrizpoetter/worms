/* Game Klasse */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Map.h"
#include "Player.h"
#include "Worm.h"

class Game {
        private:
        friend class GameBuildDirector;
        // Aktuelle Map des Spiels
        std::shared_ptr<Map> mMap;
        // Vektor mit alle Spielern
        std::vector<std::shared_ptr<Player>> mPlayers;
        // Aktueller Spieler
        std::shared_ptr<Player> mCurrentPlayer;
        // Aktueller Wurm
        std::shared_ptr<Worm> mCurentWorm;

    public:
        Game(){};
        ~Game(){};
        // Gibt Anzahl Spieler aus
        int numPlayers();
        // Map printen
        void printMap();
        // Gibt zurück ob Spiel vorbei ist
        bool isGameOver();
        //Gibt Gewinner aus
        void printWinner();
        // Gibt Map aus
        std::shared_ptr<Map> getMap();
        // Gibt Vektor mit allen Spielern zurück
        std::vector<std::shared_ptr<Player>> getPlayers();
        // Printed alle Spieler
        void printPlayers();
        // Gibt aktuellen Spieler aus
        std::shared_ptr<Player> getCurrentPlayer();
        // Gibt aktuellen Wurm aus
        std::shared_ptr<Worm> getCurrentWorm();
        // setzt aktuellen Spieler
        void setCurrentPlayer(std::shared_ptr<Player> player);
        // Setzt aktuellen Wurm
        void setCurrentWorm(std::shared_ptr<Worm> worm);
};

#endif // GAME_H