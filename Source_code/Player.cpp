#include "Player.h"

Player::Player()
{
    this->playerPos = {STARTER_POS_X, STARTER_POS_Y};
    this->velocity = STARTER_VELOCITY;
    this->color = PLAYER_COLOR;
}

Player::~Player()
{
    
}

void Player::update()
{
    
}

void Player::drawOnMiniMap()
{
    
}

// ------------------
//      GETTERS
// ------------------

Vector2 Player::getPlayerPos()
{
    return this->playerPos;
}

float Player::getPlayerVel()
{
    return this->velocity;
}

Color Player::getColor()
{
    return this->color;
}

// ------------------
//      SETTERS
// ------------------

void Player::setPlayerPos(Vector2 new_playerPos)
{
    this->playerPos = new_playerPos;
}

void Player::setPlayerVel(float new_playerVel)
{
    this->velocity = new_playerVel;
}

void Player::setColor(Color new_color)
{
    this->color = new_color;
}