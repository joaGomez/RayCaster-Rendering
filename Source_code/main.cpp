#include "Game.h"

int main(int, char**) {
    Game* new_game = new Game(1);
    
    SetTargetFPS(30);
    float frame = 0.0f;

    while(!WindowShouldClose()) {
        new_game->render();
        new_game->update();
    }

    CloseWindow();

    new_game->deleteVar();
    delete new_game;

    return 0;
}
