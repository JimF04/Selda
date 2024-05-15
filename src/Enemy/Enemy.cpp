
#include "Enemy.h"
#include "../Algoritmos/AStar.h"
#include <queue>
#include <cmath>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "raymath.h"
#include "../Hitbox.h"
const int FRAME_WIDTH = 48;
const int FRAME_HEIGHT = 48;


Enemy::Enemy()
{
    position = {100, 300};
    radius = 7;
    color = YELLOW;
    speed = 1.25;
    distanceToPlayer;
    initial_position=position;


    spritesheet = LoadTexture("../assets/chara_goblin.png");

    sourceRec = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    frameCounter = 0;

    currentFrame = 0;

    frameSpeed = 8;


}
void Enemy::Draw() const
{
    DrawTextureRec(spritesheet, sourceRec, {position.x-25,position.y-25}, WHITE);
//    DrawCircleV(position, radius, color);
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
    position = pos;
}

int Enemy::GetRadius() const
{
    return radius;
}




void Enemy::Find_player(Stack<Vector2> stack, int tile) {
    while (!stack.empty()) {
        Vector2 nextPoint = stack.top();
        stack.pop();

        // Ajusta las coordenadas multiplicándolas por el tamaño del tile
        nextPoint.x *= tile;
        nextPoint.y *= tile;

        // Calcula la dirección hacia el siguiente punto
        float directionX = nextPoint.x - position.x;
        float directionY = nextPoint.y - position.y;
        float length = sqrt(directionX * directionX + directionY * directionY);
        directionX /= length;
        directionY /= length;

        // Mueve al enemigo en la dirección de la "crumb"
//        position.x += directionX * 0.05;
//        position.y += directionY * 0.05;

        Move(static_cast<int>(round(directionX *0.75)),static_cast<int>((directionY *0.75)));




    }
}


void Enemy::Back_to_place(Stack<Vector2> stack, int tile){
    while (!stack.empty()) {
        Vector2 nextPoint = stack.top();
        stack.pop();

        // Ajusta las coordenadas multiplicándolas por el tamaño del tile
        nextPoint.x *= tile;
        nextPoint.y *= tile;

        // Calcula la dirección hacia el siguiente punto
        float directionX = nextPoint.x - position.x;
        float directionY = nextPoint.y - position.y;
        float length = sqrt(directionX * directionX + directionY * directionY);
        directionX /= length;
        directionY /= length;

        // Mueve al enemigo en la dirección de la "crumb"
        position.x += directionX * 0.05;
        position.y += directionY * 0.05;



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
