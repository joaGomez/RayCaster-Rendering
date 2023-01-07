#ifndef MAP_H
#define MAP_H

#include "Player.h"

#define MAP_RESOLUTION 10  // Size for each map cell on the window distribution


struct WallEdges
{
	float sx, sy; // Start coordinate
	float ex, ey; // End coordinate
};

struct WallCells
{
	int edge_id[4];
	bool edge_exist[4];
	bool wall = false;
    bool door = false;
};


class Map {
    public:
        Map(int index);
        ~Map();

        // Variables
        WallCells* world;
        int mapColumns = 20;
        int mapRows = 20;


        // Functions
        bool init(int index);       // Initializes map distribution
        void drawMiniMap();  
        void renderMap(Vector2 playerPosition);


    private:
        std::string fileName;
        std::filesystem::path path;

};

#endif // MAP_H