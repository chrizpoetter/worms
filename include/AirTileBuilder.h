/* Air Tile Builder Class */

#ifndef AIRTILEBUILDER_H
#define AIRTILEBUILDER_H

#include "TileBuilder.h"
#include "AirTile.h"

class AirTileBuilder : public TileBuilder {
    private:
        std::shared_ptr<AirTile> mAirTile;

    public:
        // Konstruktor resetet jedes mal Builder beim aufufen
        AirTileBuilder() {
            this->reset();
        }
        ~AirTileBuilder() override {}

        // Erstellt neues Objekt
        void reset() {
            this->mAirTile = std::make_unique<AirTile>();
        }

        std::shared_ptr<ITile> buildTile() override {
            std::shared_ptr<ITile> result = std::move(this->mAirTile);
            this->reset();
            return result;
        }
};


#endif // AIRTILEBUILDER_H