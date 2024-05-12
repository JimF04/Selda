#include "Enemy.h"
#include "../Algoritmos/AStar.h"
#include <queue>
#include <cmath>
#include <unistd.h>
#include <chrono>
#include <thread>

Enemy::Enemy()
{
    position = {100, 300};
    radius = 7;
    color = YELLOW;
    speed = 1;
    distanceToPlayer;
}
void Enemy::Draw() const
{
    DrawCircleV(position, radius, color);
}

void Enemy::Move(int deltaX, int deltaY)
{
    position.x += deltaX;
    position.y += deltaY;
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
        Move(directionX,directionY);


    }
}



bool Enemy::FollowBreadcrumb(const std::vector<Vector2>& breadcrumbs) {

    Vector2 target = breadcrumbs.back();
    distanceToPlayer = sqrt(pow(target.x - position.x, 2) + pow(target.y - position.y, 2));

    if (breadcrumbs.empty() || distanceToPlayer>20) {
        return false;
    }

    // Obtiene la última "crumb" (últimas coordenadas del jugador)

    // Imprime la distancia
    if(distanceToPlayer<20){
        // Calcula la dirección hacia la "crumb"
        float directionX = target.x - position.x;
        float directionY = target.y - position.y;

        // Normaliza la dirección
        float length = sqrt(directionX * directionX + directionY * directionY);
        directionX /= length;
        directionY /= length;

        // Mueve al enemigo en la dirección de la "crumb"
        position.x += directionX * speed;
        position.y += directionY * speed;

        return true;
    }




}