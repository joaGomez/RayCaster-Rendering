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
    float delta_angle = 0.001;
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

void Player::updateVision(Rays *ray, WallCells *world)
{
    // Variables
    float horizontalX, horizontalY, verticalX, verticalY; // First intersection point (horizontal/vertical lines)
    float verticalDistance, horizDistance;
    int x0, y0;
    int dof = 0;
    int mx, my, mp;
    

    // --------- VERTICAL LINES -----------

    int side = 0;
    verticalDistance = 100000;
    float Tan = -tanf(ray->angle);
    if (cosf(ray->angle) > 0.001) {
        verticalX = (((int)this->playerPos.x / MAP_RESOLUTION) * MAP_RESOLUTION) + MAP_RESOLUTION;
        verticalY = (this->playerPos.x - verticalX) * Tan + this->playerPos.y;
        x0 = MAP_RESOLUTION;
        y0 = -x0 * Tan;
    } // looking left
    else if (cosf(ray->angle) < -0.001) {
        verticalX = (((int)this->playerPos.x / MAP_RESOLUTION) * MAP_RESOLUTION) - 0.0001;
        verticalY = (this->playerPos.y - verticalX) * Tan + this->playerPos.y;
        x0 = -MAP_RESOLUTION;
        y0 = -x0 * Tan;
    } // looking right
    else {
        verticalX = this->playerPos.x;
        verticalY = this->playerPos.y;
        dof = COLUMNS;
    } // looking up or down. no hit

    while (dof < COLUMNS) {
        mx = (int)(verticalX) / MAP_RESOLUTION;
        my = (int)(verticalY) / MAP_RESOLUTION;
        mp = my * COLUMNS + mx;
        if (mp > 0 && mp < COLUMNS * ROWS && (world[mp].wall == true || world[mp].door == true)) {
            dof = COLUMNS;
            verticalDistance = cosf(ray->angle) * (verticalX - this->playerPos.x) - sinf(ray->angle) * (verticalY - this->playerPos.y);
        } // hit
        else {
            verticalX += x0;
            verticalY += y0;
            dof++;
        } // check next horizontal
    }

    // --------- HORIZONTAL LINES -----------

    dof = 0;
    horizDistance = 100000;
    float aTan = -1 / tanf(ray->angle);

    if (ray->angle > PI) { // Looking up
        horizontalY = (((int)this->playerPos.y / MAP_RESOLUTION) * MAP_RESOLUTION) - 0.001f;
        horizontalX = (this->playerPos.y - horizontalY) * aTan + this->playerPos.x;
        y0 = -MAP_RESOLUTION;
        x0 = -y0 * aTan;
    }
    else if (ray->angle < PI) { // Looking down
        horizontalY = (((int)this->playerPos.y / MAP_RESOLUTION) * MAP_RESOLUTION) + MAP_RESOLUTION;
        horizontalX = (this->playerPos.y - horizontalY) * aTan + this->playerPos.x;
        y0 = MAP_RESOLUTION;
        x0 = -y0 * aTan;
    }
    else if (ray->angle == 0 || ray->angle == PI) {
        horizontalX = this->playerPos.x;
        horizontalY = this->playerPos.y;
        dof = COLUMNS;
    }

    while (dof < COLUMNS) {
        mx = (int)(horizontalX) / MAP_RESOLUTION;
        my = (int)(horizontalY) / MAP_RESOLUTION;
        mp = my * COLUMNS + mx;

        if (mp > 0 && mp < (COLUMNS * ROWS) && (world[mp].wall == true || world[mp].door == true)) {
            dof = 20;
            horizDistance = cosf(ray->angle) * (horizontalX - this->playerPos.x) - sinf(ray->angle) * (horizontalY - this->playerPos.y);
        } // hit
        else {
            horizontalX += x0;
            horizontalY += y0;
            dof++;
        } // check next horizontal
    }

    if(verticalDistance < horizDistance) {
        ray->endPoint = {verticalX, verticalY};
    }
    else {  // Horizontal distance < vertical distance
        ray->endPoint = {horizontalX, horizontalY};
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

    for (auto ray : this->rays)
    {
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

void Player::drawRays2D(float posX, float posY)
{
    for (auto ray : this->rays)
    {
        float minimapPointX = TRANSFORM_POS_TO_MMAP(ray->endPoint.x);
        float minimapPointY = TRANSFORM_POS_TO_MMAP(ray->endPoint.y);

        DrawLine(posX, posY, minimapPointX, minimapPointY, ray->color);
    }
}

void Player::drawOnMiniMap()
{
    float posX = TRANSFORM_POS_TO_MMAP(this->playerPos.x);
    float posY = TRANSFORM_POS_TO_MMAP(this->playerPos.y);

    DrawCircle(posX, posY, MINIMAP_RESOLUTION / 4, this->color);
    drawRays2D(posX, posY);
}