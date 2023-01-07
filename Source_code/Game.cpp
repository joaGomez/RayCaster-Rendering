#include "Game.h"

Game::Game(int index)
{
    this->init(index);
}

Game::~Game()
{
    //delete this->gameview;
}

void Game::deleteVar()
{
    delete this->gameview->player;
    delete this->gameview;
}

void Game::init(int index)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RayCaster Rendering");
    this->gameview = new Gameview(index);
}

void Game::update()
{
    this->gameview->player->update();
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    this->gameview->render();
    EndDrawing();
}