#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#define STARTER_POS_X 100
#define STARTER_POS_Y 100
#define STARTER_VELOCITY 8.0f
#define PLAYER_COLOR YELLOW

#define TRANSFORM_POS_TO_MMAP(x) (x*MINIMAP_RESOLUTION/MAP_RESOLUTION + 10) 
// Transforms player position to minimap coordinates




class Player {
    public:
        Player();
        ~Player();

        // Functions
        void init();
        void update(WallCells* world);
        void updateRays();
        void updateVision(Rays* ray, WallCells* world);
        void drawOnMiniMap();
        void drawRays2D(float posX, float posY);
        void validateMovement();

        // Variables
        Vector2 playerPos;
        Vector2 lookingDir;
        float velocity;
        Color color;
        float angle;
        int fov;    // Number of rays display
        std::vector<Rays*> rays;

    private:
    
};

#endif // PLAYER_H