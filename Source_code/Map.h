#ifndef MAP_H
#define MAP_H

#include "Player.h"


class Map {
    public:
        Map(int index);
        ~Map();

        // Variables
        WallCells* world;
        int mapColumns = COLUMNS;
        int mapRows = ROWS;


        // Functions
        bool init(int index);       // Initializes map distribution
        void drawMiniMap();  
        void renderMap(Vector2 playerPosition);


    private:
        std::string fileName;
        std::filesystem::path path;

};

#endif // MAP_H