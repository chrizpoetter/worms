/* Water Tile Builder Class */

#ifndef WATERTILEBUILDER_H
#define WATERTILEBUILDER_H

#include "TileBuilder.h"
#include "WaterTile.h"

class WaterTileBuilder : public TileBuilder {
    private:
        std::shared_ptr<WaterTile> mWaterTile;

    public:
        // Konstruktor resetet jedes mal Builder beim aufufen
        WaterTileBuilder() {
            this->reset();
        }
        ~WaterTileBuilder() override {}

        // Erstellt neues Objekt
        void reset() {
            this->mWaterTile = std::make_unique<WaterTile>();
        }

        std::shared_ptr<ITile> buildTile() override {
            std::shared_ptr<ITile> result = std::move(this->mWaterTile);
            this->reset();
            return result;
        }
};


#endif // WATERTILEBUILDER_H