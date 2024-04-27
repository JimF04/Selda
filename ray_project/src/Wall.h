#ifndef WALL_H
#define WALL_H

#include <raylib.h>

class Wall
{
public:
    Wall();
    void Draw() const;
    void Move(int deltaX, int deltaY); // Declaración del método Move
    Rectangle GetCollisionRect() const;
private:
    Vector2 position;
    Color color;
    int width;
    int height;
};

#endif // BALL_H
