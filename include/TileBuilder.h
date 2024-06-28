/* Interface for TileBuilder */

#ifndef TILEBUILDER_H
#define TILEBUILDER_H

#include <memory>
#include "ITile.h"

class TileBuilder {
    public:
        // Virtuelle Funktionen
        virtual ~TileBuilder(){};
        virtual std::shared_ptr<ITile> buildTile() = 0;
};

#endif // TILEBUILDER_H