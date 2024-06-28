#include <fstream>
#include <iostream>
#include "MapReader.h"


using namespace std;

// Lese Map aus einer Datei ein
void MapReader::readMapFromFile(string fileName) {
    // Oeffnet Input Datei; Gibt einen Fehler zurueck, wenn diese nicht geofnnet werden kann 
    ifstream infile(fileName);
    if(!infile.good()) {
        throw ("Map Datei konnte nicht geoeffnet werden!");
        return;
    }
    // Liest Input Datei aus
    // Die erste Zeile MUSS den folgenden Inhalt haben: #SWORMS
    string inputline;
    getline(infile, inputline);
    if (inputline != "#SWORMS") {
        throw ("Map Datei hat das falsche Format!");
        return;
    }
    // Liest Datei bis "SIZE:" vorkommt
    do {
        getline(infile, inputline);
    } while(inputline.find("SIZE:") == -1);
    // Loescht SIZE: aus dem string
    inputline.erase(0,5);
    // Liest die Breite und Hoehe der Map aus
    int width, height;
    sscanf(inputline.c_str(), "%i %i", &width, &height);
    // Speichert Breite und Hoehe
    mWidth = width;
    mHeight = height;
    // Liest Datei bis "MAP:" kommt
    do {
        getline(infile, inputline);
    } while(inputline.find("MAP:") == -1);
    // Liest Map ein; Erstellt ein char array mit Inhalt der Map
    auto mapTileCodes = make_unique<vector<char>>();
    for (int i=0; i<height; i++) {
        getline(infile, inputline);
        for (int j=0; j<width; j++) {
            mapTileCodes->push_back(inputline.at(j));
        }
    }
    // Schliesst Datei
    infile.close();
    // Vector uebergeben
    mMapTileCodes = std::move(mapTileCodes);
    return;
}


// Gibt Tile Code an Stelle x,y zurueck
// und checkt ob x und y gueltig sind
char MapReader::getTileCode(int x, int y) {
    if (x<0 && x>=mWidth) {throw ("Ungültige Eingabe bei Tile Codes auslesen!");}
    if (y<0 && y>=mHeight) {throw ("Ungültige Eingabe bei Tile Codes auslesen!");}
    return mMapTileCodes->at(x+mWidth*y);
}

int MapReader::getHeight() {return this->mHeight; }

int MapReader::getWidth() { return this-> mWidth; }