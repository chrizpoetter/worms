#ifndef BLOWTORCH_H
#define BLOWTORCH_H

#include <iostream>
#include <memory>
#include <map>
#include "IWeapons.h"
#include "Game.h"

using namespace std;

class Blowtorch : public IWeapons {
private:
    std::shared_ptr<Game> mGame;

public:
    Blowtorch(std::shared_ptr<Game> game) : IWeapons("blowtorch", 1, 35, 1), mGame(game) {}

    ~Blowtorch(){}



    // Funktion zum Suchen nach einem String in der Map und Rückgabe des passenden int
    int findKeyByValue(const std::map<std::string, int>& map, const std::string& value) {
        for (const auto& pair : map) {
            if (pair.first == value) {
                return pair.second;
            }
        }
        return -1; // Rückgabe eines ungültigen Werts, falls der String nicht gefunden wurde
    }



    void shoot(int x, int y, std::string direction) override {
        if (mAmmo <= 0) {
            std::cout << "No ammo left!" << std::endl;
            return;
        }

        // Definieren der Map
        std::map<std::string, int> directionMap = {
            {"l",1},
            {"r",2},
            {"d",3},
            {"u",4},
            {"ld",5},
            {"rd",6},
            {"lu",7},
            {"ru",8}
        };

        int dir = findKeyByValue(directionMap, direction);

        switch(dir) {
            case 1: //left
                //schaden durch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x-1, y, mDamage, true);   
                mGame->getMap()->damageTile(x-2, y, mDamage, true); 
                mGame->getMap()->damageTile(x-3, y, mDamage, true); 
                mGame->getMap()->damageTile(x-4, y, mDamage, true); 
                 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x-1, y);
                mGame->getMap()->dealFall(x-2, y);
                mGame->getMap()->dealFall(x-3, y);
                mGame->getMap()->dealFall(x-4, y);
                
                break;
            case 2: //right
                //Schaden durch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x+1, y, mDamage, true);   
                mGame->getMap()->damageTile(x+2, y, mDamage, true); 
                mGame->getMap()->damageTile(x+3, y, mDamage, true); 
                mGame->getMap()->damageTile(x+4, y, mDamage, true); 
                 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x+2, y);
                mGame->getMap()->dealFall(x+3, y);
                mGame->getMap()->dealFall(x+4, y);
                mGame->getMap()->dealFall(x+5, y);
                break;
            case 3: //down
                //Schaden durch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x, y+1, mDamage, true);   
                mGame->getMap()->damageTile(x, y+2, mDamage, true); 
                mGame->getMap()->damageTile(x, y+3, mDamage, true); 
                mGame->getMap()->damageTile(x, y+4, mDamage, true); 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x, y+1);
                mGame->getMap()->dealFall(x, y+2);
                mGame->getMap()->dealFall(x, y+3);
                mGame->getMap()->dealFall(x, y+4);

                break;
            case 4: //up
                //Schaden duch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x, y-1, mDamage, true);   
                mGame->getMap()->damageTile(x, y-2, mDamage, true); 
                mGame->getMap()->damageTile(x, y-3, mDamage, true); 
                mGame->getMap()->damageTile(x, y-4, mDamage, true); 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x, y-1);
                mGame->getMap()->dealFall(x, y-2);
                mGame->getMap()->dealFall(x, y-3);
                mGame->getMap()->dealFall(x, y-4);
                break;

            case 5: //left-down
                //Schaden duch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x-1, y+1, mDamage, true);   
                mGame->getMap()->damageTile(x-2, y+2, mDamage, true); 
                mGame->getMap()->damageTile(x-3, y+3, mDamage, true); 
                mGame->getMap()->damageTile(x-4, y+4, mDamage, true); 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x-1, y+1);
                mGame->getMap()->dealFall(x-2, y+2);
                mGame->getMap()->dealFall(x-3, y+3);
                mGame->getMap()->dealFall(x-4, y+4);
                break;

            case 6: //right-down
                //Schaden durch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x+1, y+1, mDamage, true);   
                mGame->getMap()->damageTile(x+2, y+2, mDamage, true); 
                mGame->getMap()->damageTile(x+3, y+3, mDamage, true); 
                mGame->getMap()->damageTile(x+4, y+4, mDamage, true); 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x+1, y+1);
                mGame->getMap()->dealFall(x+2, y+2);
                mGame->getMap()->dealFall(x+3, y+3);
                mGame->getMap()->dealFall(x+4, y+4);
                break;
            case 7: //left-up
                //Schaden durch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x-1, y+1, mDamage, true);   
                mGame->getMap()->damageTile(x-2, y+2, mDamage, true); 
                mGame->getMap()->damageTile(x-3, y+3, mDamage, true); 
                mGame->getMap()->damageTile(x-4, y+4, mDamage, true); 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x-1, y+1);
                mGame->getMap()->dealFall(x-2, y+2);
                mGame->getMap()->dealFall(x-3, y+3);
                mGame->getMap()->dealFall(x-4, y+4);
                break;
            case 8: //right-up
                //Schaden duch Waffe
                mGame->getMap()->damageTile(x, y, mDamage, true);
                mGame->getMap()->damageTile(x+1, y-1, mDamage, true);   
                mGame->getMap()->damageTile(x+2, y-2, mDamage, true); 
                mGame->getMap()->damageTile(x+3, y-3, mDamage, true); 
                mGame->getMap()->damageTile(x+4, y-4, mDamage, true); 

                //dass Blöcke fallen
                mGame->getMap()->dealFall(x, y);
                mGame->getMap()->dealFall(x+1, y-1);
                mGame->getMap()->dealFall(x+2, y-2);
                mGame->getMap()->dealFall(x+3, y-3);
                mGame->getMap()->dealFall(x+4, y-4);
                break;
        }
        removeAmmo();

    }
};

#endif //BLOWTORCH_H