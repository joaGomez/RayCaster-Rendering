#include "Gameview.h"

Gameview::Gameview(int index)
{
    this->init(index);
}

Gameview::~Gameview()
{
    // delete this->player;
    // delete this->map;
}

void Gameview::init(int index)
{
    this->map = new Map(index);
    this->player = new Player();
}

void Gameview::update()
{
    player->update(this->map->world);
}

void Gameview::render()
{
    map->renderMap(player->playerPos);
    map->drawMiniMap();
    player->drawOnMiniMap();
}