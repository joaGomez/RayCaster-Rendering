#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#define STARTER_POS_X 100
#define STARTER_POS_Y 100
#define STARTER_VELOCITY 1.0f
#define PLAYER_COLOR RED


class Player {
    public:
        Player();
        ~Player();

        // Functions
        void update();
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
        float velocity;
        Color color;
        

};

#endif // PLAYER_H