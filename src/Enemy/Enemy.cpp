#include "Enemy.h"
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



void Enemy::FollowBreadcrumb(const std::vector<Vector2>& breadcrumbs) {
    // Verifica si hay al menos una "crumb" para seguir
    if (breadcrumbs.empty()) {
        return;
    }

    // Obtiene la última "crumb" (últimas coordenadas del jugador)
    Vector2 target = breadcrumbs.back();

    float distanceToPlayer = sqrt(pow(target.x - position.x, 2) + pow(target.y - position.y, 2));
    std::cout << "Distancia al jugador: " << distanceToPlayer << std::endl;
    // Imprime la distancia
    if(distanceToPlayer<15){
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

    }


}