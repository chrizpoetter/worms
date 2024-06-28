#include <iostream>
#include <string>
#include "GameBuildDirector.h"
#include "Random.h"
#include "WurmFactory.h"
#include "Player.h"
#include "Map.h"
#include "MapReader.h"
#include "MapBuildDirector.h"
#include "ITile.h"
#include "WormTileBuilder.h"
#include "IWeapons.h"
#include "Bazooka.h"
#include "Gun.h"
#include "Teleporter.h"
#include "Blowtorch.h"
#include "Melee.h"
#include "Airstrike.h"



using namespace std;

// Konstruktor erstellt neues Objekt der Klasse Game
GameBuildDirector::GameBuildDirector() {
    this->mGame = make_shared<Game>();
}

// Erstellt das Spiel
shared_ptr<Game> GameBuildDirector::construct(std::shared_ptr<INIReader> ini_reader) {
    string worm_name_file = ini_reader->Get("general","WORM_NAMES","../assets/worm_names.txt");
    shared_ptr<se::Random> random = make_unique<se::Random>(worm_name_file);

    constructMap(ini_reader);
    constructPlayer(ini_reader);
    constructWorm(ini_reader, random);
    
    return mGame;
}

// Erstellt die Würmer
void GameBuildDirector::constructWorm (shared_ptr<INIReader> ini_reader, shared_ptr<se::Random> random) {
    int num_worms = ini_reader->GetInteger("player","NUM_WORMS",3);
    int id = 1;
    int XP = 100;
    //Schleife über alle Spieler in Vektor player
    for(auto player : mGame->mPlayers) {  
        //Schleife über alle Anzahl der Würmer aus num_worms aus INI-Datei           
        for(int i=0; i < num_worms; i++) {
            // Zufällige Position an der der Wurm spawnt
            int x = random->getRandomInt(0, mGame->mMap->getWidth()-1);
            // Erstellt den Wurm
            shared_ptr<Worm> worm = WurmFactory::create(player, id, random, x, XP);
            worm->initialize(worm);
            mGame->mMap->addWorm(worm);        
            ++id;
            constructWeapons(worm);        
        }
    }
    return;
}


// Erstellt die Player
void GameBuildDirector::constructPlayer(shared_ptr<INIReader> ini_reader) {
    // lädt Anzahl der Spieler
    int num_players = ini_reader->GetInteger("player","NUM_PLAYER",2);      
    // Schleife so lange wie spieler vorhanden sind
    for (int i=0; i < num_players; i++){ 
        // Lädt Symbol des Spielers       
        string player = "PLAYER" + to_string(i);
        // Lädt Symbol als String
        string strSymbol = ini_reader->Get("player",player, "x");
        // Wandelt String in char array und nimmt ersten Char
        char symbol = strSymbol.c_str()[0];       
        // Erstelle Player
        shared_ptr<Player> newPlayer = make_shared<Player> (i+1, symbol);     
        // Speichert neuen Spieler in Vektorliste
        mGame->mPlayers.push_back(newPlayer);         
    }
    return;
}



// Erstellt die Map
void GameBuildDirector::constructMap(shared_ptr<INIReader> ini_reader) {
    // Liest Dateipfad der Map Datei ein
    string mapFileName = ini_reader->Get("general","MAP","../assets/map.txt");
    auto mapReader = make_unique<MapReader>();
    mapReader->readMapFromFile(mapFileName);
    // Erstell Map Build Director
    unique_ptr<MapBuildDirector> mapDirector = make_unique<MapBuildDirector>();
    // Erstellt 2D Vector, wo die Map gespeichert wird
    vector<vector<shared_ptr<ITile>>> mapVector (mapReader->getWidth(), vector<shared_ptr<ITile>> (mapReader->getHeight()));
    // Füllt die Map mit Tiles
    for (int y=0; y<mapReader->getHeight(); y++) {
        for (int x=0; x<mapReader->getWidth(); x++) {
            // Holt sich den Tile Code an Stelle x,y
            char tileCode = mapReader->getTileCode(x,y);
            // Oeffnet konkreten Tile Builder
            auto tileBuilder = mapDirector->setBuilder(tileCode);
            mapVector[x][y] = tileBuilder->buildTile();
        }
    }
    // Erstellt Map Objekt und ordent es dem Game zu
    mGame->mMap =  make_shared<Map>(mapVector, mapReader->getWidth(),mapReader->getHeight());
    return;
}



// Methode zum des Inventars der Würmer
void GameBuildDirector::constructWeapons(std::shared_ptr<Worm> worm) {
    // Fügt Waffen zu den Würmern hinzu
    worm->addWeapon(make_unique<Gun>(mGame));
    worm->addWeapon(make_unique<Bazooka>(mGame));
    worm->addWeapon(make_unique<Teleporter>(mGame));
    worm->addWeapon(make_unique<Blowtorch>(mGame));
    worm->addWeapon(make_unique<Melee>(mGame));
    worm->addWeapon(make_unique<Airstrike>(mGame));
}