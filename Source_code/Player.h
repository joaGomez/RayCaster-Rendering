#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#define STARTER_POS_X 100
#define STARTER_POS_Y 100
#define STARTER_VELOCITY 1.0f
#define PLAYER_COLOR YELLOW

#define TRANSFORM_POS_TO_MMAP(x) (x*MINIMAP_RESOLUTION/MAP_RESOLUTION + 10) 
// Transforms player position to minimap coordinates

class Player {
    public:
        Player();
        ~Player();

        // Functions
        void update(WallCells* world);
        void drawOnMiniMap();

        // Setters
        void setPlayerPos(Vector2 new_playerPos);
        void setPlayerVel(float new_playerVel);
        void setColor(Color new_color);

        // Getters
        Vector2 getPlayerPos();
        float getPlayerVel();
        Color getColor();

    private:
        Vector2 playerPos;
        Vector2 lookingDir;
        float velocity;
        Color color;
        float angle;
        

};

#endif // PLAYER_H