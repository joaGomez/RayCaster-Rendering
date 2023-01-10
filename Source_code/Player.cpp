#include "Player.h"

Player::Player()
{
    this->init();
}

Player::~Player()
{
}

void Player::init()
{
    this->playerPos = {STARTER_POS_X, STARTER_POS_Y};
    this->velocity = STARTER_VELOCITY;
    this->color = PLAYER_COLOR;
    this->angle = 0.0f;
    this->lookingDir = {cosf(this->angle), sinf(this->angle)};
    this->fov = 1;
    for (int i = 0; i < this->fov; i++)
    {
        Rays *ray = new Rays{0, this->color, this->angle, Vector2Add(this->playerPos, Vector2Scale(this->lookingDir, 5))};
        this->rays.push_back(ray);
    }
}

void Player::validateMovement()
{
}

void Player::updateRays()
{
    float delta_angle = 0.01;
    int i = 0, aux = 0;
    int max_amplitud = (int)fov / 2;

    for (auto ray : this->rays)
    {
        if (i < this->fov / 2)
        {
            ray->angle = this->angle - max_amplitud * delta_angle;
            max_amplitud--;
        }
        else if (i == fov / 2)
        {
            ray->angle = this->angle;
        }
        else if (i > fov / 2)
        {
            ray->angle = this->angle + aux * delta_angle;
            aux++;
        }
        i++;
    }
}

void Player::update(WallCells *world)
{
    float deltaX = 0.0f, deltaY = 0.0f;

    if (IsKeyPressed(KEY_A) || IsKeyDown(KEY_A))
    {
        this->angle -= 0.1f;
        if (this->angle < 0)
        {
            this->angle += 2 * PI;
        }
        this->lookingDir = {cosf(this->angle), sinf(this->angle)};
    }
    if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_S))
    {
        deltaX -= this->lookingDir.x;
        deltaY -= this->lookingDir.y;
    }
    if (IsKeyPressed(KEY_D) || IsKeyDown(KEY_D))
    {
        this->angle += 0.1f;
        if (this->angle > 2 * PI)
        {
            this->angle -= 2 * PI;
        }
        this->lookingDir = {cosf(this->angle), sinf(this->angle)};
    }
    if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_W))
    {
        deltaX += this->lookingDir.x;
        deltaY += this->lookingDir.y;
    }

    this->playerPos = Vector2Add(this->playerPos, {deltaX * this->velocity, deltaY * this->velocity});

    this->updateRays();

    for(auto ray : this->rays) {
        updateVision(ray, world);
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
    // if(!no_pass_flag) {
    //     boss->move(0.0f, 0.0f);
    //     player->move(moveX, moveY);
    //     game_view->map1->vecVisibilityPolygonPoints.clear();
    // }
}

void Player::updateVision(Rays* ray, WallCells* world)
{
    // TODO: Fix bug, it freezes the program
    /*float rx, ry;       // First intersection point (horizontal lines)
    int x0, y0;
    int dof = 0;
    int mx, my, mp;
    float aTan = 0;

    if(ray->angle != 0) {
        float aTan = -1/tanf(ray->angle);
    }

    if(ray->angle > PI) {       // Looking up
        ry = (((int)this->playerPos.y / MAP_RESOLUTION) * MAP_RESOLUTION) - 0.001f;
        rx = (this->playerPos.y - ry) * aTan + this->playerPos.x;
        y0 = -MAP_RESOLUTION;
        x0 = -y0 * aTan;
    }
    else if(ray->angle < PI) {       // Looking down
        ry = (((int)this->playerPos.y / MAP_RESOLUTION) * MAP_RESOLUTION) + MAP_RESOLUTION;
        rx = (this->playerPos.y - ry) * aTan + this->playerPos.x;
        y0 = MAP_RESOLUTION;
        x0 = -y0 * aTan;
    }
    else if(ray->angle == 0 || ray->angle == PI) {
        rx = this->playerPos.x;
        ry = this->playerPos.y;
        dof = 20;
    }

    while(dof < 20) {
        mx=(int)(rx)>>6; my=(int)(ry)>>6; mp = my * COLUMNS + mx;                          
        if(mp>0 && mp < (COLUMNS * ROWS) && world[mp].wall == true) { 
            dof = 8; 
            ray->distance = cosf(ray->angle) * (rx - this->playerPos.x) - sinf(ray->angle)*(ry - this->playerPos.y);
        }       //hit         
        else { 
            rx += x0; 
            ry += y0; 
            dof++;
        }                                               //check next horizontal
    }

    ray->endPoint = {rx, ry};*/

}

void Player::drawRays2D(float posX, float posY)
{
    for (auto ray : this->rays)
    {
        float minimapPointX = TRANSFORM_POS_TO_MMAP(ray->endPoint.x);
        float minimapPointY = TRANSFORM_POS_TO_MMAP(ray->endPoint.y);

        DrawLine(posX, posY, minimapPointX , minimapPointY, ray->color);
    }
}

void Player::drawOnMiniMap()
{
    float posX = TRANSFORM_POS_TO_MMAP(this->playerPos.x);
    float posY = TRANSFORM_POS_TO_MMAP(this->playerPos.y);

    DrawCircle(posX, posY, MINIMAP_RESOLUTION / 4, this->color);
    drawRays2D(posX, posY);
}