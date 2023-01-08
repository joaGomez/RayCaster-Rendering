#ifndef GAME_H
#define GAME_H

#include "Gameview.h"

class Game {
    public:
        Game(int index);
        ~Game();

        // Variables


        // Functions
        void init(int index);
        void update();
        void render();
        void deleteVar();

        // Variables
        Gameview* gameview;
        Map* map;
        int window_width;
        int window_height;
        
    private:


};

#endif // GAME_H