#ifndef GAMEBUILDDIRECTOR_H
#define GAMEBUILDDIRECTOR_H

#include <memory>
#include "Game.h"
#include "Random.h"
#include "INIReader.h"
#include "Worm.h"
#include "Player.h"




class GameBuildDirector {
    private:
        std::shared_ptr<Game> mGame;

    public:
        GameBuildDirector();
        ~GameBuildDirector(){};

        // Methode zum erstellen des Spieles
        std::shared_ptr<Game> construct(std::shared_ptr<INIReader> ini_reader);
        // Methode zum erstellen der Spieler
        void constructPlayer(std::shared_ptr<INIReader> ini_reader);
        // Methode zum erstellen der Map
        void constructMap(std::shared_ptr<INIReader> ini_reader);
        // Methode zum erstellen der Würmer
        void constructWorm(std::shared_ptr<INIReader> ini_reader, std::shared_ptr<se::Random> random);
        // Methode zum des Inventars der Würmer
        void constructWeapons(std::shared_ptr<Worm> worm);

};




#endif // GAMEBUILDDIRECTOR_H