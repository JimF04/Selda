
#include "Enemy.h"
#include "../Algoritmos/AStar.h"
#include <queue>
#include <cmath>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "raymath.h"
#include "../Hitbox.h"
#include <unistd.h>
#include <random>
#include <algorithm>

const int FRAME_WIDTH = 48;
const int FRAME_HEIGHT = 48;

Enemy::Enemy(){
    radius = 7;
    color = YELLOW;

    sourceRec = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    frameCounter = 0;

    currentFrame = 0;

    frameSpeed = 8;

    eliminated = false;

    initial_position = position;

    currentDirection = IDLE;

    looping = true;
    llego = false;
    const float PATROL_RADIUS = 2.0f * TILE_SIZE;

    lastDirectionChangeTime = 0.0f;
    srand(time(NULL));



}
void Enemy::Draw() const
{
    DrawTextureRec(spritesheet, sourceRec, {position.x-20,position.y-20}, WHITE);

}

void Enemy::Move(int deltaX, int deltaY) {
    position.x += deltaX;
    position.y += deltaY;


    if (deltaX > 0) {
        currentDirection = RIGHT;

        sourceRec.y = FRAME_HEIGHT * 3;

        sourceRec.width = FRAME_WIDTH;
    } else if (deltaX < 0) {
        currentDirection = LEFT;

        sourceRec.y = FRAME_HEIGHT * 3;

        sourceRec.width = -FRAME_WIDTH;
    } else if (deltaY > 0) {
        currentDirection = DOWN;

        sourceRec.y = FRAME_HEIGHT * 2;

        sourceRec.width = FRAME_WIDTH;
    } else if (deltaY < 0) {
        currentDirection = UP;

        sourceRec.y = FRAME_HEIGHT * 4;
        sourceRec.width = FRAME_WIDTH;
    } else if (!IsKeyDown(KEY_L) && !IsKeyDown(KEY_K)) {
        currentDirection = IDLE;

        sourceRec.y = 0;
        sourceRec.width = FRAME_WIDTH;
    }

    UpdateAnimation();
}

Vector2 Enemy::GetPosition() const
{
    return position;
}

void Enemy::setPosition(Vector2 pos)
{
    position.x = pos.x * 16;
    position.y = pos.y * 16;

    initial_position = position;
}

int Enemy::GetRadius() const
{
    return radius;
}

void Enemy::moveToTile(int targetX, int targetY, float pixel) {
    float deltaX = (targetX * 16) - position.x;
    float deltaY = (targetY * 16) - position.y;


    float directionX = (deltaX != 0) ? (deltaX / abs(deltaX)) : 0;
    float directionY = (deltaY != 0) ? (deltaY / abs(deltaY)) : 0;


    position.x += directionX * pixel;
    position.y += directionY * pixel;


    if (deltaX > 0) {
        currentDirection = RIGHT;

        sourceRec.y = FRAME_HEIGHT * 3;

        sourceRec.width = FRAME_WIDTH;
    } else if (deltaX < 0) {
        currentDirection = LEFT;

        sourceRec.y = FRAME_HEIGHT * 3;

        sourceRec.width = -FRAME_WIDTH;
    } else if (deltaY > 0) {
        currentDirection = DOWN;

        sourceRec.y = FRAME_HEIGHT * 2;
        sourceRec.width = FRAME_WIDTH;
    } else if (deltaY < 0) {
        currentDirection = UP;

        sourceRec.y = FRAME_HEIGHT * 4;
        sourceRec.width = FRAME_WIDTH;
    } else if (!IsKeyDown(KEY_L) && !IsKeyDown(KEY_K)) {
        currentDirection = IDLE;

        sourceRec.y = 0;
        sourceRec.width = FRAME_WIDTH;
    }


    UpdateAnimation();


    if ((deltaX > 0 && position.x > targetX * 16) || (deltaX < 0 && position.x < targetX * 16)) {
        position.x = targetX * 16;
    }
    if ((deltaY > 0 && position.y > targetY * 16) || (deltaY < 0 && position.y < targetY * 16)) {
        position.y = targetY * 16;
    }
}


void Enemy::FollowPath(Stack<Vector2>& path) {
    if (!path.empty()) {
        Vector2 target = path.top();
        moveToTile(target.x, target.y, speed);

        // Verifica si el enemigo ha llegado al centro del destino actual
        if (abs(position.x - target.x * 16) <= 0.5 && abs(position.y - target.y * 16) <= 0.5) {
            path.pop();
        }
    }
}

void Enemy::LoopPath(queue<Vector2> &path) {
    if (!path.empty() && halegado()) {
        Vector2 target = path.front();
        moveToTile(target.x, target.y, speed);


        if (abs(position.x - target.x * 16) <= 0.5 && abs(position.y - target.y * 16) <= 0.5) {

            path.pop();
            path.push(target);
        }
    }
}


bool Enemy::FollowBreadcrumb(Vector2& breadcrumbs) {

    Vector2 target = breadcrumbs;
    distanceToPlayer = sqrt(pow(target.x - position.x, 2) + pow(target.y - position.y, 2));

    if (distanceToPlayer>40) {
        return false;
    }


    if(distanceToPlayer<40 && distanceToPlayer>20){

        float directionX = target.x - position.x;
        float directionY = target.y - position.y;


        float length = sqrt(directionX * directionX + directionY * directionY);
        directionX /= length;
        directionY /= length;


        Move(directionX*speed,directionY*speed);

        return true;
    }

    if(distanceToPlayer<20){
        Ataque();

    }
}

void Enemy::Ataque(){
    sourceRec.y = FRAME_HEIGHT*5;
    ataques +=1;
    UpdateAnimation();

}

void Enemy::UpdateAnimation() {
    frameCounter++;
    if (frameCounter >= frameSpeed) {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame > 3)
        {
            currentFrame = 0;
        }
        sourceRec.x = currentFrame * FRAME_WIDTH;
    }
    duracion +=1;
}
bool Enemy::GetCollisionWithHitbox(const Hitbox &hitbox) const {
    return CheckCollisionCircleRec(position, radius, hitbox.GetRect());
}


void Enemy::SetEliminated(bool eliminated) {
    this->eliminated = eliminated;
    muerto = true;
}

bool Enemy::IsEliminated() const {
    return eliminated;

}

Vector2 Enemy::Get_inial_position(){
    return initial_position;


}

bool Enemy::halegado(){
    return llego;
}

void Enemy::set_llego(bool dime){
    llego = dime;
}

void Enemy::Animacion_random(){

    sourceRec.y = FRAME_HEIGHT*4;
    UpdateAnimation();
}



void Enemy::MoveRandomly(const int wall[MAP_WIDTH][MAP_HEIGHT]) {
    // Posibles direcciones de movimiento (deltaX, deltaY)
    const std::vector<std::pair<int, int>> directions = {
            {1, 0},  // Derecha
            {0, 1},  // Abajo
            {-1, 0}, // Izquierda
            {0, -1}  // Arriba
    };


    if (previousDeltaX == 0 && previousDeltaY == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, directions.size() - 1);
        auto dir = directions[dis(gen)];
        previousDeltaX = dir.first;
        previousDeltaY = dir.second;
    }


    int newX = position.x + previousDeltaX * TILE_SIZE;
    int newY = position.y + previousDeltaY * TILE_SIZE;


    if (newX >= 0 && newX < MAP_WIDTH * TILE_SIZE && newY >= 0 && newY < MAP_HEIGHT * TILE_SIZE && wall[newX / TILE_SIZE][newY / TILE_SIZE] == 0) {
        moveToTile(newX / TILE_SIZE, newY / TILE_SIZE, 1.0f);
    } else {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        bool moved = false;
        for (int i = 0; i < 2; ++i) {
            int direction = dis(gen) == 0 ? 1 : -1;
            int currentIndex = (std::find(directions.begin(), directions.end(), std::make_pair(previousDeltaX, previousDeltaY)) - directions.begin());
            int newDirIndex = (currentIndex + direction) % directions.size();
            if (newDirIndex < 0) newDirIndex += directions.size();
            auto newDir = directions[newDirIndex];

            int tryX = position.x + newDir.first * TILE_SIZE;
            int tryY = position.y + newDir.second * TILE_SIZE;

            if (tryX >= 0 && tryX < MAP_WIDTH * TILE_SIZE && tryY >= 0 && tryY < MAP_HEIGHT * TILE_SIZE && wall[tryX / TILE_SIZE][tryY / TILE_SIZE] == 0) {
                previousDeltaX = newDir.first;
                previousDeltaY = newDir.second;
                moveToTile(tryX / TILE_SIZE, tryY / TILE_SIZE, 1.0f);
                moved = true;
                break;
            }
        }


        if (!moved) {
            std::vector<std::pair<int, int>> mutableDirections = directions;
            std::shuffle(mutableDirections.begin(), mutableDirections.end(), gen);
            for (const auto& dir : mutableDirections) {
                int tryX = position.x + dir.first * TILE_SIZE;
                int tryY = position.y + dir.second * TILE_SIZE;
                if (tryX >= 0 && tryX < MAP_WIDTH * TILE_SIZE && tryY >= 0 && tryY < MAP_HEIGHT * TILE_SIZE && wall[tryX / TILE_SIZE][tryY / TILE_SIZE] == 0) {
                    previousDeltaX = dir.first;
                    previousDeltaY = dir.second;
                    moveToTile(tryX / TILE_SIZE, tryY / TILE_SIZE, 1.0f);
                    break;
                }
            }
        }
    }
}


void Enemy::changeDirection(Direction newDirection) {
    currentDirection = newDirection;


    switch (currentDirection) {
        case RIGHT:
            sourceRec.y = FRAME_HEIGHT * 3;
            sourceRec.width = FRAME_WIDTH;
            break;
        case LEFT:
            sourceRec.y = FRAME_HEIGHT * 3;
            sourceRec.width = -FRAME_WIDTH;
            break;
        case DOWN:
            sourceRec.y = FRAME_HEIGHT * 2;
            sourceRec.width = FRAME_WIDTH;
            break;
        case UP:
            sourceRec.y = FRAME_HEIGHT * 4;
            sourceRec.width = FRAME_WIDTH;
            break;
        case IDLE:
            sourceRec.y = 0;
            sourceRec.width = FRAME_WIDTH;
            break;
    }
}

void Enemy::updateDir(float deltaTime) {
    lastDirectionChangeTime += deltaTime;

    if (lastDirectionChangeTime >= changeInterval) {

        Direction newDirection = static_cast<Direction>(rand() % 4);
        changeDirection(newDirection);


        lastDirectionChangeTime = 0.0f;
    }
}

