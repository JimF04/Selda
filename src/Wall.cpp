#include "Wall.h"

Wall::Wall() : position({0, 0}), width(0), height(0), color(WHITE)
{
    // Constructor sin argumentos
}

Wall::Wall(Vector2 pos, int w, int h) : position(pos), width(w), height(h), color(WHITE)
{
    // Constructor con argumentos
}

void Wall::Draw() const
{
    DrawRectangle(position.x, position.y, width, height, color);
}

Rectangle Wall::GetCollisionRect() const
{
    return {position.x, position.y, static_cast<float>(width), static_cast<float>(height)};
}