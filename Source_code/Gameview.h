#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Player.h"
#include "Map.h"

class Gameview {
    public:
        Gameview(int index);
        ~Gameview();

        // Variables
        Map* map;
        Player* player;

        // Functions
        void init(int index);
        void update();
        void render();

    private:

};

#endif // GAMEVIEW_H