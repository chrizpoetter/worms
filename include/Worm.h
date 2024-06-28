#ifndef WORM_H
#define WORM_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "IWeapons.h"
#include "Player.h"


class Player;

// Struct für Position vom Wurm
struct Pos {
    int x, y;
};



class Worm : public std::enable_shared_from_this<Worm> {
    
private:
    int mId;
    int mXP;
    char mTeam;
    std::string mCurrentWeapon;
    Pos mPos;

    std::string mName;
    std::shared_ptr<Player> mPlayer;
    //std::vector<std::unique_ptr<IWeapons>> mWeapons;
    std::unordered_map<std::string, std::unique_ptr<IWeapons> > mWeapons;



public:
    // Konstruktor
    Worm(std::shared_ptr<Player> player, int id, std::string mName, int x, int XP);
    // Destruktor
    ~Worm();
    // Initilaliser
    void initialize(std::shared_ptr<Worm> worm);



    // Getter und Setter Methoden
    // Methoden zum Zugriff auf die Eigenschaften des Wurms
    std::string getName() const;
    // Methode um XP anzuzeigen
    int getXP();
    // Gibt ID zurück
    int getID();
    // Methoden um XP zu ändern
    void setXP(int newXP);
    // Methode um dem Wurm Schaden hinzuzufügen
    // gibt true zurück wenn der Wurm tot ist
    bool setDamage(int damage);
    // Methode gibt Sturzschaden
    bool fallDamage(int height);
    // Methode gibt Sturzschaden
    void hitDamage(int damage);
    // Methode um den Wurm Namen auszugeben
    std::string getName();
    // Methode um Wurm Symbol zu bekommen
    char getSymbol();
    // Methode zum setzten der neuen Koordinaten
    void setPos(int x, int y);
    // Methode um Koordinaten auszulesen
    Pos getPos();


    // Möglichkeiten fuer den Wurm zu sterben
    // Methode das der Wurm stirbt
    void die();
    // Methode das der Wurm ertrinkt
    void drown();
    // Methode das der Wurm aus der Map faellt
    void outOfMapDeath();
    // Methode das der Wurm durch fallschaden stirbt
    void fallDeath();
    // Methode wo Wurm durch Waffe stirbt
    void killed();


    // Methode update die implementiert werden muss, zurzeit macht sie nichts
    void update() {};
    // Fügt Waffe hinzu
    void addWeapon(std::unique_ptr<IWeapons> weapon);
    // Benutzt aktuelle Waffe
    void useWeapon(int x, int y, std::string direction);
    // Benutzt Waffe über string Eingabe
    void useWeapon(int x, int y, std::string direction, std::string weapon);
    // Printet Inventar
    void printInventory();
    // Wählt Waffe 
    void chooseWeapon(std::string weaponName);
    // Fügt Waffe zur Liste hinzu
    void registerWeapon(const std::string& weapon_name, std::unique_ptr<IWeapons> weapon_function);




};

#endif // WORM_H