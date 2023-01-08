#ifndef INITIALS_H
#define INITIALS_H

#include "raylib.h"
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <math.h>

#define MAP_COUNT 1     // How many levels there are

#define MAP_RESOLUTION 40  // Size for each map cell on the window distribution
#define MINIMAP_RESOLUTION 20    // Size for each cell shown on minimap
#define COLUMNS 20
#define ROWS 20


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



#endif  // INITIALS_H

