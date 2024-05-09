#include "ball.h"

Ball::Ball()
{
    position = {400, 300};
    radius = 6;
    color = PINK;
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

bool Ball::GetSafeRoom()
{
    return safeRoom;
}

void Ball::SetSafeRoom(bool safe)
{
    safeRoom = safe;
}