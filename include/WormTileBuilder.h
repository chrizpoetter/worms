/* Worm Tile Builder Class */

#ifndef WORMTILEBUILDER_H
#define WORMTILEBUILDER_H

#include "TileBuilder.h"
#include "WormTile.h"

class WormTileBuilder : public TileBuilder {
    private:
        std::shared_ptr<WormTile> mWormTile;

    public:
        // Konstruktor resetet jedes mal Builder beim aufufen
        WormTileBuilder() {
            this->reset();
        }
        ~WormTileBuilder() override {}

        // Erstellt neues Objekt
        void reset() {
            this->mWormTile = std::make_unique<WormTile>();
        }

        // Weist dem WormTile einen Worm zu
        void setWorm(std::shared_ptr<Worm> worm) {
            mWormTile->mWorm = worm;
            return;
        }

        std::shared_ptr<ITile> buildTile() override {
            std::shared_ptr<ITile> result = std::move(mWormTile);
            this->reset();
            return result;
        }
};


#endif // WORMTILEBUILDER_H