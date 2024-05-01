#include "ball.h"

Ball::Ball()
{
    position = { 180, 130 };
    radius = 20;
    color = RED;
    playerTileX = 0;
    playerTileY = 0;
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