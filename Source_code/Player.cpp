#include "Player.h"

Player::Player()
{
    this->playerPos = {STARTER_POS_X, STARTER_POS_Y};
    this->velocity = STARTER_VELOCITY;
    this->color = PLAYER_COLOR;
    this->angle = 0.0f;
    this->lookingDir = {cosf(this->angle), sinf(this->angle)};
}

Player::~Player()
{
    
}

void Player::update(WallCells* world)
{
    float deltaX = 0.0f, deltaY = 0.0f;

    if(IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) {
        this->angle -= 0.1f;
        if(this->angle < 0) {
            this->angle += 2*PI;
        }
        this->lookingDir = {cosf(this->angle), sinf(this->angle)};
    }
    if(IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) {
        deltaX -= this->lookingDir.x;
        deltaY -= this->lookingDir.y;
    }
    if(IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) {
        this->angle += 0.1f;
        if(this->angle > 2*PI) {
            this->angle -= 2*PI;
        }
        this->lookingDir = {cosf(this->angle), sinf(this->angle)};
    }
    if(IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) {
        deltaX += this->lookingDir.x;
        deltaY += this->lookingDir.y;
    }

    // TODO: Validate movement -> make possible move + looking direction

    /*bool no_pass_flag = false;
    for(int i = 0 ; i < ROWS ; i++) {
        for(int j = 0 ; j < COLUMNS ; j++) {
            if(world[ROWS * i + j].wall) {
                //Vector2 playerPossiblePos = Vector2Add(player->position, {moveX*player->speed, moveY*player->speed});
                //if((playerPossiblePos.x >= (j * SCALE) && playerPossiblePos.x <= (j * SCALE + SCALE) && playerPossiblePos.y >= (i * SCALE) && playerPossiblePos.y <= (i * SCALE + SCALE)))
                //{
                //    std::cout << "No se puede pasar" << std::endl;
                //    no_pass_flag = true;
                //}
            }
            else if(world[ROWS * i + j].door) {

            }
        }
    }*/
    //if(!no_pass_flag) {
    //    boss->move(0.0f, 0.0f);
    //    player->move(moveX, moveY);
    //    game_view->map1->vecVisibilityPolygonPoints.clear();
    //}

}

void Player::drawOnMiniMap()
{
    float posX = TRANSFORM_POS_TO_MMAP(this->playerPos.x);
    float posY = TRANSFORM_POS_TO_MMAP(this->playerPos.y);
    
    DrawCircle(posX, posY, MINIMAP_RESOLUTION/4, this->color);
    DrawLine(posX, posY, posX + this->lookingDir.x*5, posY + this->lookingDir.y*5, this->color);
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