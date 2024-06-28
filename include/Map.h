#ifndef MAP_H 
#define MAP_H

#include <vector>
#include <memory>
#include <string>
#include "ITile.h"
#include "WormTile.h"
#include "Worm.h"

using std::shared_ptr;

class Map {
    private:
        int mWidth;
        int mHeight;
        std::vector<std::vector<shared_ptr<ITile>>> mMap;

    public: 
        // Konstuktor
        Map(std::vector<std::vector<shared_ptr<ITile>>> map, int width, int height);
        // Gibt Map in Terminal aus
        void print();
        // Gibt Breite der Map aus
        int getWidth();
        // Gibt Höhe der Map aus
        int getHeight();
        // Fügt ein Objekt an Stelle x,y auf de Map hinzu
        void addWorm(shared_ptr<WormTile> tile, int x, int y);
        // Fügt Objekt an in der x-Reihe auf de Map hinzu
        void addWorm(shared_ptr<Worm> worm);
        // Methode bewegt Wurm
        void moveWorm(std::shared_ptr<Worm> worm, int x);
        // Methode gibt zurück wie viele Blöcke zum nächsten soliden Block
        // und schaut ob der Block überhaupt beweglich ist
        int gravity(int x, int y);
        // Methode die zurück gibt wie viele Blöcke bis zum nächsten soliden Block
        int freeFall(int x, int y);
        // Methode die durch die Map iterriert und alles Fallen lässt
        void letItFall();
        // Methode die prüft ob Wurm Klettern kann
        // direction -1 nach links +1 nach rechts
        bool canClimb(std::shared_ptr<Worm> worm, bool direction);
        // Lässt ein Objekt Fallen nachdem ein Block dadrunter zerstört worden ist
        void dealFall(int x, int y);
        // Damage Tile
        void damageTile(int x, int y, int damage, bool allTiles);
        // Methode ersetzt Tile durch AirTile
        void destroyTile(int x, int y);
        // Methode gibt an ob Solider Block
        bool isSolidBlock(int x, int y);
        

};

#endif // MAP_H