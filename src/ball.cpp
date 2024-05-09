#include "ball.h"
#include "raylib.h"
#include "raymath.h"


Ball::Ball()
{
    position = {400, 300};
    radius = 6;
    color = PINK;
    lives = 5;
}
int Ball::GetLives() const {
    return lives;
}
void Ball::DecreaseLives() {
    lives--;
}


void Ball::Draw() const
{
    DrawCircleV(position, radius, color);
}

void Ball::Move(int deltaX, int deltaY)
{
    position.x += deltaX;
    position.y += deltaY;
}

Vector2 Ball::GetPosition() const
{
    return position;
}

int Ball::GetRadius() const
{
    return radius;
}

void Ball::setPosition(Vector2 pos)
{
    position = pos;
}

bool Ball::CheckCollisionWithEnemy(const Enemy &enemy) const {
    float distance = Vector2Distance(position, enemy.GetPosition());
    return distance < radius + enemy.GetRadius();
}

bool Ball::GetSafeRoom()
{
    return safeRoom;
}

void Ball::SetSafeRoom(bool safe)
{
    safeRoom = safe;
}

void Ball::ResetLives() {
    lives = INNITIAL_LIVES;
}