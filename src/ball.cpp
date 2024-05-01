#include "ball.h"

Ball::Ball()
{
    position = {400, 300};
    radius = 20;
    color = RED;
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