#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>
#include "Worm.h"


using namespace std;


// Konstruktor
Worm::Worm(shared_ptr<Player> player, int id, string name, int x, int XP) : mPlayer(player), mId(id), mName(name), mXP(XP) {
    mPos.x = x;
    mPos.y = 0;
    cout << mName << " (" << mId << ") erscheint bei (" << mPos.x << "," << mPos.y << ")" << endl;
}


// Destruktor
Worm::~Worm() {}



void Worm::initialize(shared_ptr<Worm> worm) {
    mPlayer->attach(shared_from_this());
}



void Worm::setXP(int newXP) {
    mXP = newXP;
}


int Worm::getXP()  {
    return mXP;
}


//Gibt ID zurück
int Worm::getID() {return mId;}


// Methode um dem Wurm Schaden hinzuzufügen
// gibt true zurück wenn der Wurm tot ist
bool Worm::setDamage(int damage) {
    mXP -= damage;
    if(mXP > 0) return false;
    return true;
}


// Methode gibt Sturzschaden
bool Worm::fallDamage(int height) {
    if (height <= 1) return false;
    height -= 1;
    int damage = height*10;
    cout << mName << " (" << mId << ") took " << damage << "hp fall damage." << endl;
    if(setDamage(damage)) fallDeath();
    return true;
}


// Methode gibt Sturzschaden
void Worm::hitDamage(int damage) {
    cout << mName << " (" << mId << ") took " << damage << "hp damage." << endl;
    if(setDamage(damage)) return killed();
}


char Worm::getSymbol() {
    return mPlayer->getSymbol();
}


// Gibt Namen aus
string Worm::getName() {return mName;}


// Methode zum setzten der neuen Koordinaten
void Worm::setPos (int x,  int y) {
    mPos.x = x;
    mPos.y = y;
}


// Methode um Koordinaten auszulesen
Pos Worm::getPos() {
    return mPos;
}


// Methode das der Wurm stirbt
void Worm::die() {
    // Löscht Wurm aus der Liste vom Player
    mPlayer->detach(shared_from_this());
}


// Methode das der Wurm ertrinkt
void Worm::drown() {
    cout << mName << " (" << mId << ") drowned." << endl;
    die();
}


// Methode das der Wurm aus der Map faellt
void Worm::outOfMapDeath() {
    cout << mName << " (" << mId << ") fell out of Map." << endl;
    die();
}


// Methode das der Wurm aus der Map faellt
void Worm::fallDeath() {
    cout << mName << " (" << mId << ") fell out of Map." << endl;
    die();
}


// Methode wo Wurm durch Waffe stirbt
void Worm::killed() {
    cout << mName << " (" << mId << ") died." << endl;
    die();
}


// Fügt Waffe hinzu
void Worm::addWeapon(unique_ptr<IWeapons> weapon) {
    string weaponName = weapon->getName();
    registerWeapon(weaponName, std::move(weapon));
}


// Benutzt aktuelle Waffe
void Worm::useWeapon(int x, int y, string direction) {
    auto it = mWeapons.find(mCurrentWeapon);
    if (it != mWeapons.end()) {
        if (it->second->getAmmo() <= 0 ) {
            cout << "[WARNING] no ammunition!" << endl;
            return;
        }
        it->second->shoot(x,y,direction);
        return;
    } 
}


// Benutzt Waffe über string Eingabe
void Worm::useWeapon(int x, int y, string direction, string weapon) {
    auto it = mWeapons.find(weapon);
    if (it != mWeapons.end()) {
        if (it->second->getAmmo() <= 0 ) {
            cout << "[WARNING] no ammunition!" << endl;
            return;
        }
        it->second->shoot(x,y,direction);
        return;
    } 
}


// Printed Inventar
void Worm::printInventory() {
    cout << endl << "weapons of current worm:" << endl;

    for (auto& weapon : mWeapons) {
        cout << "   " << weapon.second->getName() << " (Ammunition: " << weapon.second->getAmmo() << ")";
        if(weapon.second->getName() == mCurrentWeapon) cout << " *";
        // currnt weapon
        cout << endl;
    }
    cout << endl;
}



// Wählt Waffe
void Worm::chooseWeapon(string weaponName) {
    auto it = mWeapons.find(weaponName);
    if (it != mWeapons.end()) {
        mCurrentWeapon = it->first;
        cout << "Chose weapon " << it->second->getName() << " Ammunition: " << it->second->getAmmo() << endl;
        if (it->second->getAmmo() <= 0 ) cout << "[WARNING] no ammunition!" << endl;
        return;
    } 
    cout << "[WARNING] no valid weapon!" << endl;
}



// Funktion zum hinzufügen von Kommandos zur Liste mCommands
void Worm::registerWeapon(const std::string& weaponName, std::unique_ptr<IWeapons> weaponFunction) {
    mWeapons[weaponName] = std::move(weaponFunction);
    return;
}