#include "Map.h"

Map::Map(int index)
{
    if(this->init(index)) {
        std::cout << "Map successfully created." << std::endl;
    }
    else {
        std::cout << "Map could not be created." << std::endl;
    }
}

Map::~Map()
{

}

bool Map::init(int index)
{
    this->fileName = "Map_" + std::to_string(index) + ".txt";
    this->path = std::filesystem::current_path().parent_path();
    this->path.concat("\\Levels");

    std::filesystem::current_path(this->path);

    this->world = new WallCells[this->mapRows * this->mapColumns];

    // Reads map distribution
    std::ifstream file(this->fileName);
    std::string line;
    int j = 0;      // Rows

    if(file.is_open()) {
        // TODO: PROBLEM READING THE FILE
        int index = 0;
        while(getline(file, line)) {
            for(int i = 0 ; i < line.length() ; i++) {
                if(line[i] == '0') {
                    index++;
                }
                else if(line[i] == '1') {
                    this->world[index].wall = true;
                    index++;
                }
                else if(line[i] == '2') {
                    this->world[index].door = true;
                    index++;
                }
            }
        }


        /*while(getline(file, line)) {
            for(int i = 0 ;  i < line.length() ; i++) {
                if(line[i] == '1' ) {
                    this->world[ j * this->mapColumns + i ].wall = true;
				    //this->existingWalls.push_back({j * MAP_RESOLUTION, i * MAP_RESOLUTION});
                }
                else if(line[i] == '2' ) {
                    this->world[ j * this->mapColumns + i ].door = true;
				    //this->existingWalls.push_back({j * MAP_RESOLUTION, i * MAP_RESOLUTION});
                }
            }
            j++;
        }*/
        return true;
    }
    else {
        return false;
    }
}

void Map::drawMiniMap()
{
    BeginDrawing();
    ClearBackground(BLACK);
    Color color;
    for(int i = 0 ; i < 20 ; i++ ) {
        for(int j = 0 ; j < 20 ; j++ ) {        // Draw every map cell
            if(this->world[i*this->mapRows+j].wall) {
                color = WHITE;
            }
            else if(this->world[i*this->mapRows+j].door) {
                color = RED;
            } 
            else {
                color = BLACK;
            }
            DrawRectangle( j * MAP_RESOLUTION, i * MAP_RESOLUTION, 
            MAP_RESOLUTION, MAP_RESOLUTION, color);
        }
    }

    DrawFPS(10, 10);

    EndDrawing();
}

void Map::renderMap(Vector2 playerPos)
{

}