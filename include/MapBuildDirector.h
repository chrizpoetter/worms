/* Map Build Director */

#ifndef MAPBUILDDIRECTOR_H
#define MAPBUILDDIRECTOR_H

#include <memory>
#include "TileBuilder.h"
#include "EarthTileBuilder.h"
#include "AirTileBuilder.h"
#include "WaterTileBuilder.h"

class MapBuildDirector {
    private:
        std::unique_ptr<TileBuilder> builder;

    public:

        // Definiert spezifischen Tile Builder
        std::unique_ptr<TileBuilder> setBuilder(char tileCode) {
            // Gibt EarthTileBuilder bei 'E' zurueck
            if (tileCode == 'E') {
                return std::make_unique<EarthTileBuilder>();
            }
            // Gibt WaterTileBuilder bei 'W' zurueck
            if (tileCode == 'W') {
                return std::make_unique<WaterTileBuilder>();
            }
            // Gibt AirTileBuilder bei 'A' zurueck
            if (tileCode == 'A') {
                return std::make_unique<AirTileBuilder>();
            }
            // Gibt Error zurueck falls nicht uebereinstimmt
            throw ("Unbekannter Tile Code in Map Datei!");
            return nullptr;
        }




};


#endif // MAPBUILDDIRECTOR_H