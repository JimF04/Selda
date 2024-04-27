#include "wall.h"

Wall::Wall()
{
    position = {500, 300};
    color = WHITE;
    width = 50;
    height = 50;

}

void Wall::Draw() const
{
     DrawRectangle(position.x, position.y, width, height, color);
}

Rectangle Wall::GetCollisionRect() const
{
    return { position.x, position.y, (float)width, (float)height };
}
