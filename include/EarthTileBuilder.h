/* Earth Tile Builder Class */

#ifndef EARTHTILEBUILDER_H
#define EARTHTILEBUILDER_H

#include "TileBuilder.h"
#include "EarthTile.h"

class EarthTileBuilder : public TileBuilder {
    private:
        std::shared_ptr<EarthTile> mEarthTile;

    public:
        // Konstruktor resetet jedes mal Builder beim aufufen
        EarthTileBuilder() {
            this->reset();
        }
        ~EarthTileBuilder() override {}

        // Erstellt neues Objekt
        void reset() {
            this->mEarthTile = std::make_unique<EarthTile>();
        }

        std::shared_ptr<ITile> buildTile() override {
            std::shared_ptr<ITile> result = std::move(this->mEarthTile);
            this->reset();
            return result;
        }
};


#endif // EARTHTILEBUILDER_H