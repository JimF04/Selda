
#include "Enemy.h"
#include <queue>
#include <cmath>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "raymath.h"
#include "../Hitbox.h"


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
void Enemy::FollowBreadcrumb(const Vector2& target) {
    // Calcula la dirección hacia la bola
    float directionX = target.x - position.x;
    float directionY = target.y - position.y;

    // Normaliza la dirección
    float length = sqrt(directionX * directionX + directionY * directionY);
    directionX /= length;
    directionY /= length;

    // Mueve al enemigo en la dirección de la bola
    position.x += directionX * speed;
    position.y += directionY * speed;
}


 bool Enemy::GetCollisionWithHitbox(const Hitbox& hitbox) const{
     return CheckCollisionCircleRec(position, radius, hitbox.GetRect());
}


void Enemy::SetEliminated(bool eliminated) {
    this ->eliminated = eliminated;
}

bool Enemy::IsEliminated() const {
    return eliminated;
}