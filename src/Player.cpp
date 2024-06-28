#include <iostream>
#include "Player.h"



using namespace std;



Player::Player(int id, char symbol) : mId(id), mSymbol(symbol) {}

char Player::getSymbol() {
    return mSymbol;
}



// Gibt Player ID aus
int Player::getId() {return mId;}


// Fügt Würmer (worm) zur Liste hinzu
void Player::attach(shared_ptr<Worm> worm)  {
    mWorms.push_back(worm);
}

// Entfernt Würmer (worm) von Liste 
void Player::detach(shared_ptr<Worm> worm)  {
    mWorms.erase(std::remove(mWorms.begin(), mWorms.end(), worm), mWorms.end());
}

// Benachrichtigt Würmer(worm)
void Player::notify()  {
    for (auto& worm : mWorms) {
        worm->update();
    }
}

// Gibt Anzahl an lebenden Würmern vom Spieler zurück
int Player::numWorms() {
    return mWorms.size();
}

std::vector<shared_ptr<Worm>> Player::getWorms() {
    return mWorms;
}

void Player::printWorms() {
    for (auto& worm : mWorms) {
        cout << "   " << worm->getName() << " (" << worm->getID() << ") " << worm->getXP() << " HP ("  << worm->getPos().x << "," << worm->getPos().y << ") " << worm->getSymbol() << endl;
    }
    cout << endl;
}
