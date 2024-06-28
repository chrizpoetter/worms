#include <iostream>
#include "Map.h"
#include "AirTileBuilder.h"
#include "WormTileBuilder.h"

using namespace std;



Map::Map(std::vector<std::vector<std::shared_ptr<ITile>>> map, int width, int height) : mMap(map), mWidth(width), mHeight(height) {}


// Gibt Breite der Map aus
int Map::getWidth() {
    return mWidth;
}


// Gibt Höhe der Map aus
int Map::getHeight() {
    return mHeight;
}


// Gibt Map in Terminal aus
void Map::print() {
    cout << endl << "Current Map:" << endl << endl;
    // Gibt x-Koordinaten aus
    cout << ' ' << ' ';
    for (int i=0; i<mWidth; i++) { 
        int k = (i/10) * 10;
        cout << i-k;
    }
    cout << endl;
    // Gibt Map aus
    for (int y=0; y<mHeight; y++) {
        if (y<10) cout << ' ';
        cout << y; //y-Koordinate
        for (int x=0; x<mWidth; x++) {
            // Map Inhalt
            cout << mMap[x][y]->getImg(); 
        }
        if (y<10) cout << ' ';
        cout << y << endl; //y-Koordinate
    }
    // Gibt x-Koordinaten aus
    cout << ' ' << ' ';
    for (int i=0; i<mWidth; i++) { 
        int k = (i/10) * 10;
        cout << i-k;
    }
    cout << endl << endl << endl;
    return;
}


// Fügt Objekte in einer Spalte auf der Map hinzu
void Map::addWorm(shared_ptr<Worm> worm) {
    // Lese x und y aus Wurm aus
    int x = worm->getPos().x;
    int y = worm->getPos().y;
    // Erstelle Builder
    auto wormTileBuilder = make_shared<WormTileBuilder>();
    wormTileBuilder->setWorm(worm);
    auto wormTile = wormTileBuilder->buildTile();
    // Wurm faellt solange er bis auf einen soliden Block trifft
    while ( !(mMap[x][y]->getSolid() || y+1 >= mHeight) ) {
        mMap[x][y] = wormTile;
        if (y>0) destroyTile(x,y-1);
        worm->setPos(x,y);
        y++;
    }
    // Wurm ertrinkt wenn der Block Wasser ist
    if (mMap[x][y]->isWater()) {
        worm->drown();
        destroyTile(x,y-1);
    }
    return;
}


// Methode bewegt Wurm
void Map::moveWorm(shared_ptr<Worm> worm, int steps) {
    // Aktuelle Position vom Wurm
    int x = worm->getPos().x;
    int y = worm->getPos().y;
    // Holt aktuellen WormTile
    auto wormTile = mMap[x][y];

    // Wurm bleibt stehen
    if(steps==0) return;
    // Wurm geht nach RECHTS
    if(steps > 0) {
        if (steps > 3) steps = 3;
        for (int i=0; i<steps; i++) {
            // Checkt ob move ausserhalb der Map geht
            if (x+1 > mWidth-1) {
                worm->outOfMapDeath();
                destroyTile(x,y);
                return;
            }
            // Checkt ob Wurm klettern kann
            if (!canClimb(worm, true) && !mMap[x+1][y]->getSolid()) {
                cout << "[WARNING] can't move further" << endl;
                return;
            }

            int deltaY = 0;
            // Lässt Wurm klettern falls nötig
            if (mMap[x+1][y]->getSolid()) deltaY = -1;
            // Bestimmt Fallhöhe
            else deltaY = freeFall(x+1,y);
            // Bewegt Wurm einen nach rechts
            mMap[x+1][y+deltaY] = wormTile;
            // Überschreibt alte Stelle mit AirTile
            destroyTile(x,y);
            x++;
            y += deltaY;
            worm->setPos(x,y);
            if (mMap[x][y+1]->isWater()) {
                worm->drown();
                destroyTile(x, y);
                return;
            }
            if (worm->fallDamage(deltaY)) return;
            letItFall();
        }
    }
    // Wurm geht nach LINKS
    if (steps < 0) {
        if (steps < -3) steps = -3;
        for (int i=0; i>steps; i--) {
            // Checkt ob move ausserhalb der Map geht
            if (x-1 < 0) {
                worm->outOfMapDeath();
                destroyTile(x,y);
                return;
            }
            // Checkt ob Wurm klettern kann
            if (!canClimb(worm, false) && !mMap[x-1][y]->getSolid()) {
                cout << "[WARNING] can't move further" << endl;
                return;
            }

            int deltaY = 0;
            // Lässt Wurm klettern falls nötig
            if (mMap[x-1][y]->getSolid()) deltaY = -1;
            // Bestimmt Fallhöhe
            else deltaY = freeFall(x-1,y);
            // Bewegt Wurm einen nach rechts
            mMap[x-1][y+deltaY] = wormTile;
            // Überschreibt alte Stelle mit AirTile
            destroyTile(x,y);
            x--;
            y += deltaY;
            worm->setPos(x,y);
            if (mMap[x][y+1]->isWater()) {
                worm->drown();
                destroyTile(x, y);
                return;
            }
            if(worm->fallDamage(deltaY)) return;
            letItFall();
        }
    }
}


// Methode gibt zurück wie viele Blöcke zum nächsten soliden Block
// und schaut ob der Block überhaupt beweglich ist
int Map::gravity(int x, int y) {
    if(!mMap[x][y]->isMovable()) return -1;
    return freeFall(x,y);
}


// Methode die zurück gibt wie viele Blöcke bis zum nächsten soliden Block
int Map::freeFall(int x, int y) {
    int deltaY=0;
    while(!(mMap[x][y+1]->getSolid() || y >= mHeight-1)) {
        ++deltaY;
        ++y;
    }
    return deltaY;
}


// Methode die prüft ob Wurm Klettern kann
// direction FALSE nach links/ TRUE nach rechts
bool Map::canClimb(shared_ptr<Worm> worm, bool direction) {
    // Bricht ab, wenn y kleiner 0
    if (worm->getPos().y-1 < 0) return false;
    // Checkt was überdem Wurm ist
    auto aboveTile = mMap[worm->getPos().x][worm->getPos().y-1];
    if( (!aboveTile->isMovable()) && aboveTile->getSolid() ) return false;
    // Checkt Block rechts vom Wurm
    if(direction) {
        if (mMap[worm->getPos().x+1][worm->getPos().y-1]->getSolid()) return false;
    }
    // Checkt Block links vom Wurm
    else if (mMap[worm->getPos().x-1][worm->getPos().y-1]->getSolid()) return false;
    // Gibt true zurück wenn in Gehrichtung nichts über dem Block ist
    return true;
}


// Geht mit Schaden von Tiles um. Schaut auch auf Schwerkraft
void Map::dealFall(int x, int y) {
    // Schaut ob alle Werte innerhalb der Map sind
    if ( x<0 || x>mWidth-1 || y<0 || y>mHeight-1) return;
    // Gibt die Fallhöhe eines beweglichen Objektes an
    int deltaY = gravity(x,y);
    if (deltaY <= 0) return;
    // Lässt Objekt fallen
    mMap[x][y+deltaY] = mMap[x][y];
    std::shared_ptr<WormTile> wormTile = std::dynamic_pointer_cast<WormTile>(mMap[x][y + deltaY]);
    if (wormTile) {
        wormTile->getWorm()->setPos(x,y+deltaY);
        wormTile->getWorm()->fallDamage(deltaY);
        // Lässt Wurm ertrinken wenn er auf wasser steht
        if (mMap[x][y+deltaY+1]->isWater()) {
            wormTile->getWorm()->drown();
            destroyTile(x, y+deltaY);
        }
    }
    destroyTile(x,y);
}


// Methode die durch die Map iterriert und alles Fallen lässt
void Map::letItFall() {
    for (int x=0; x<mWidth; x++) {
        for (int y=mHeight-1; y>0; y--) {
            dealFall(x,y);
        }
    }
}


// Methode fügt Damage zu Tiles hinzu
void Map::damageTile(int x, int y, int damage, bool allTiles) {
    // Schaut ob alle Werte innerhalb der Map sind
    if ( x<0 || x>mWidth-1 || y<0 || y>mHeight-1) return;
    if (mMap[x][y]->hit(allTiles, damage)) destroyTile(x,y);
}


// Methode ersetzt Tile durch AirTile
void Map::destroyTile(int x, int y) {
    auto airTileBuilder = make_shared<AirTileBuilder>();
    mMap[x][y] = airTileBuilder->buildTile();
}


// Methode gibt an ob Solider Block
bool Map::isSolidBlock(int x, int y) {
    if (mMap[x][y]->getSolid()) return true;
    return false;
}