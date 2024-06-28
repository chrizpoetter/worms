#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "INIReader.h"
#include "Worm.h"

class Worm;

class Player {
    private:
        int mId;
        char mSymbol;
        std::vector<std::shared_ptr<Worm>> mWorms; 
    public:
        // Konstruktor Player
        Player(int id, char symbol);
        // Destruktor Player     
        ~Player(){}

        // Gibt die Spieler Id wieder
        int getId();
        // Gibt das Symbol des Wurmes zurück
        char getSymbol();
        // Fügt Würmer (Observer) zur Liste hinzu
        void attach(std::shared_ptr<Worm> worm);
        // Entfernt Würmer (Observer) von Liste 
        void detach(std::shared_ptr<Worm> worm);
        // Benachrichtigt Würmer(Observer)
        void notify();
        // Gibt Anzahl an lebenden Würmern vom Spieler zurück
        int numWorms();
        // Gibt die Würmer zurück
        std::vector<std::shared_ptr<Worm>> getWorms(); 
        // Printed Würmer
        void printWorms();
};

#endif // PLAYER_H
