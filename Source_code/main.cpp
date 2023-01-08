#include "Game.h"

int main(int, char**) {
    Game* new_game = new Game(1);
    
    SetTargetFPS(30);
    int frame = 0;

    while(!WindowShouldClose()) {
        new_game->update();
        new_game->render();
    }

    CloseWindow();

    new_game->deleteVar();
    delete new_game;

    return 0;
}
