
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
    speed = 1;

    sourceRec = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    frameCounter = 0;

    currentFrame = 0;

    frameSpeed = 8;

    eliminated = false;

    initial_position = position;



    looping = true;
     llego = false;
    const float PATROL_RADIUS = 2.0f * TILE_SIZE;



}
void Enemy::Draw() const
{
    DrawTextureRec(spritesheet, sourceRec, {position.x-20,position.y-20}, WHITE);

}

void Enemy::Move(int deltaX, int deltaY) {
    position.x += deltaX;
    position.y += deltaY;

    // Determine which animation to play based on movement
    if (deltaX > 0) {
        // Moving right
        sourceRec.y = FRAME_HEIGHT * 3; // Row 4: Walk sideways
        // Reset any previous flips
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (deltaX < 0) {
        // Moving left
        sourceRec.y = FRAME_HEIGHT * 3; // Row 4: Walk sideways
        // Flip the sprite horizontally
        sourceRec.width = -FRAME_WIDTH; // Invert the width
    } else if (deltaY > 0) {
        // Moving down
        sourceRec.y = FRAME_HEIGHT * 2; // Row 3: Walk forward
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (deltaY < 0) {
        // Moving up
        sourceRec.y = FRAME_HEIGHT * 4; // Row 3: Walk forward
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (!IsKeyDown(KEY_L) && !IsKeyDown(KEY_K)) {
        // No movement, idle animation
        sourceRec.y = 0; // Row 1: Idle
        sourceRec.width = FRAME_WIDTH; // Reset the width
    }
    // Update the animation
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
    // Calculate the distance to the target tile
    float deltaX = (targetX * 16) - position.x; // Assuming each tile is 16x16 pixels
    float deltaY = (targetY * 16) - position.y;

    // Calculate the normalized direction vector
    float directionX = (deltaX != 0) ? (deltaX / abs(deltaX)) : 0;
    float directionY = (deltaY != 0) ? (deltaY / abs(deltaY)) : 0;

    // Move 'pixel' amount towards the target on each axis
    position.x += directionX * pixel;
    position.y += directionY * pixel;

    // Determine which animation to play based on movement
    if (deltaX > 0) {
        // Moving right
        sourceRec.y = FRAME_HEIGHT * 3; // Row 4: Walk sideways
        // Reset any previous flips
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (deltaX < 0) {
        // Moving left
        sourceRec.y = FRAME_HEIGHT * 3; // Row 4: Walk sideways
        // Flip the sprite horizontally
        sourceRec.width = -FRAME_WIDTH; // Invert the width
    } else if (deltaY > 0) {
        // Moving down
        sourceRec.y = FRAME_HEIGHT * 2; // Row 3: Walk forward
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (deltaY < 0) {
        // Moving up
        sourceRec.y = FRAME_HEIGHT * 4; // Row 3: Walk forward
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (!IsKeyDown(KEY_L) && !IsKeyDown(KEY_K)) {
        // No movement, idle animation
        sourceRec.y = 0; // Row 1: Idle
        sourceRec.width = FRAME_WIDTH; // Reset the width
    }

    // Update the animation
    UpdateAnimation();

    // Ensure the enemy doesn't overshoot the target
    if ((deltaX > 0 && position.x > targetX * 16) || (deltaX < 0 && position.x < targetX * 16)) {
        position.x = targetX * 16;
    }
    if ((deltaY > 0 && position.y > targetY * 16) || (deltaY < 0 && position.y < targetY * 16)) {
        position.y = targetY * 16;
    }
}


void Enemy::FollowPath(Stack<Vector2>& path) {
    if (!path.empty()) {
        Vector2 target = path.top(); // Obtén el próximo destino sin quitarlo del camino
        moveToTile(target.x, target.y, 1); // Ajusta el valor de 'pixel' según tu preferencia

        // Verifica si el enemigo ha llegado al centro del destino actual
        if (abs(position.x - target.x * 16) <= 0.5 && abs(position.y - target.y * 16) <= 0.5) {
            // Si el enemigo está lo suficientemente cerca del centro del destino actual, quita el destino del camino
            path.pop();
        }
    }
}

void Enemy::LoopPath(queue<Vector2> &path) {
    if (!path.empty() && halegado()) {
        Vector2 target = path.front(); // Obtén el próximo destino sin quitarlo del camino
        moveToTile(target.x, target.y, 1); // Ajusta el valor de 'pixel' según tu preferencia

        // Verifica si el enemigo ha llegado al centro del destino actual
        if (abs(position.x - target.x * 16) <= 0.5 && abs(position.y - target.y * 16) <= 0.5) {
            // Si el enemigo está lo suficientemente cerca del centro del destino actual, mueve el destino al final del camino
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

    // Obtiene la última "crumb" (últimas coordenadas del jugador)

    // Imprime la distancia
    if(distanceToPlayer<40 && distanceToPlayer>20){
        // Calcula la dirección hacia la "crumb"
        float directionX = target.x - position.x;
        float directionY = target.y - position.y;

        // Normaliza la dirección
        float length = sqrt(directionX * directionX + directionY * directionY);
        directionX /= length;
        directionY /= length;

        // Mueve al enemigo en la dirección de la "crumb"

        Move(directionX*speed,directionY*speed);

        return true;
    }

    if(distanceToPlayer<20){
        Ataque();

    }
}


void Enemy::Ataque(){
    sourceRec.y = FRAME_HEIGHT*5;
    UpdateAnimation();
}

void Enemy::UpdateAnimation() {
    frameCounter++;
    if (frameCounter >= frameSpeed) {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame > 2) // Si excede el número de frames de la animación
        {
            currentFrame = 0; // Reiniciar la animación
        }
        sourceRec.x = currentFrame * FRAME_WIDTH;
    }
}
bool Enemy::GetCollisionWithHitbox(const Hitbox &hitbox) const {
    return CheckCollisionCircleRec(position, radius, hitbox.GetRect());
}


void Enemy::SetEliminated(bool eliminated) {
    this->eliminated = eliminated;
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

    // Elegir dirección actual si no hay una dirección previa
    if (previousDeltaX == 0 && previousDeltaY == 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, directions.size() - 1);
        auto dir = directions[dis(gen)];
        previousDeltaX = dir.first;
        previousDeltaY = dir.second;
    }

    // Calcular nueva posición en la dirección actual
    int newX = position.x + previousDeltaX * TILE_SIZE;
    int newY = position.y + previousDeltaY * TILE_SIZE;

    // Verificar si puede moverse en la dirección actual
    if (newX >= 0 && newX < MAP_WIDTH * TILE_SIZE && newY >= 0 && newY < MAP_HEIGHT * TILE_SIZE && wall[newX / TILE_SIZE][newY / TILE_SIZE] == 0) {
        moveToTile(newX / TILE_SIZE, newY / TILE_SIZE, 1.0f);
    } else {
        // Si no puede moverse en la dirección actual, intentar girar a la derecha o izquierda
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        bool moved = false;
        for (int i = 0; i < 2; ++i) {
            int direction = dis(gen) == 0 ? 1 : -1; // Elegir girar a la derecha o izquierda aleatoriamente
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

        // Si no pudo girar a la derecha o izquierda, intentar moverse en cualquier dirección
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


