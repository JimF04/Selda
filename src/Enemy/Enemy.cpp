#include "Enemy.h"
#include "../Algoritmos/AStar.h"
#include <queue>
#include <cmath>
#include <unistd.h>
#include <chrono>
#include <thread>
const int FRAME_WIDTH = 48;
const int FRAME_HEIGHT = 48;

Enemy::Enemy()
{
    position = {75, 300};
    radius = 7;
    color = YELLOW;
    speed = 1.25;
    distanceToPlayer;
    initial_position=position;


    spritesheet = LoadTexture("/home/jose/Selda/assets/chara_slime.png");

    sourceRec = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    frameCounter = 0;

    currentFrame = 0;

    frameSpeed = 8;


}
void Enemy::Draw() const
{
    DrawTextureRec(spritesheet, sourceRec, position, WHITE);
    //DrawCircleV(position, radius, color);
}

void Enemy::Move(int deltaX, int deltaY)
{
    position.x += deltaX;
    position.y += deltaY;

    // Lógica de animación: determinar dirección y ajustar sourceRec.y para el sprite
    if (deltaX > 0) {
        sourceRec.y = FRAME_HEIGHT * 3; // Animación hacia la derecha
    } else if (deltaX < 0) {
        sourceRec.y = FRAME_HEIGHT * 4; // Animación hacia la izquierda
    } else if (deltaY > 0) {
        sourceRec.y = FRAME_HEIGHT * 2; // Animación hacia abajo
    } else if (deltaY < 0) {
        sourceRec.y = FRAME_HEIGHT * 4; // Animación hacia arriba
    }

    UpdateAnimation(); // Actualizar la animación
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
        position.x += directionX * 0.05;
        position.y += directionY * 0.05;



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
        Move(directionX,0);
        Move(0,directionY);


    }


}



bool Enemy::FollowBreadcrumb(Vector2& breadcrumbs) {

    Vector2 target = breadcrumbs;
    distanceToPlayer = sqrt(pow(target.x - position.x, 2) + pow(target.y - position.y, 2));

    if (distanceToPlayer>30) {
        return false;
    }

    // Obtiene la última "crumb" (últimas coordenadas del jugador)

    // Imprime la distancia
    if(distanceToPlayer<30){
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


}

void Enemy::UpdateAnimation()
{
    frameCounter++;
    if (frameCounter >= frameSpeed)
    {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame > 2) // Si excede el número de frames de la animación
        {
            currentFrame = 0; // Reiniciar la animación
        }
        sourceRec.x = currentFrame * FRAME_WIDTH;
    }
}