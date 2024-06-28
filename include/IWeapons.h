#ifndef IWEAPONS_H
#define IWEAPONS_H

#include <string>

class IWeapons {
    protected:
        std::string mName;
        int mAmmo;
        int mDamage;
        int mRadius;

    public:
        IWeapons(std::string name, int ammo, int damage, int radius) 
        : mName(name), mAmmo(ammo), mDamage(damage), mRadius(radius) {}

        std::string getName() const {return mName;}

        int getAmmo() const {return mAmmo;}

        int getDamage() const {return mDamage;}

        int getRadius() const {return mRadius;}

        void removeAmmo() {mAmmo--;}
        
    // Virtuelle Funktionen
    virtual ~IWeapons() {};
    virtual void shoot(int x, int y, std::string direction) = 0;
};

#endif // IWEAPONS_H