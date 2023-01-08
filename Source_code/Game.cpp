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
    this->gameview = new Gameview(index);
    this->window_height = this->gameview->map->mapRows * MAP_RESOLUTION;
    this->window_width = this->gameview->map->mapColumns * MAP_RESOLUTION;
    InitWindow(this->window_width, this->window_height, "RayCaster Rendering");
}

void Game::update()
{
    this->gameview->update();
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    this->gameview->render();
    EndDrawing();
}