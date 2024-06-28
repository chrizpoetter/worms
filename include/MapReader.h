/* Map Reader Class */

#ifndef MAPREADER_H
#define MAPREADER_H

#include <memory>
#include <string>
#include <vector>


class MapReader  {
    private:
        int mWidth;
        int mHeight;
        std::unique_ptr<std::vector<char>> mMapTileCodes;

    public:
        ~MapReader(){}
        
        // Funktion gibt Hoehe der Map wieder
        int getHeight();
        // Funktion gibt Breite der Map wieder
        int getWidth();
        // Funktion gibt Tile Code an Stelle x,y zurueck
        char getTileCode(int x, int y);
        // Funktion liest Map File ein
        void readMapFromFile(std::string fileName);
        
};

#endif // MAPREADER_H