// wall.h
#ifndef WALL_H
#define WALL_H

#include <raylib.h>

class Wall
{
public:
    Wall(); // Constructor sin argumentos
    Wall(Vector2 pos, int w, int h);
    void Draw() const;
    Rectangle GetCollisionRect() const;

private:
    Vector2 position;
    Color color;
    int width;
    int height;
};

#endif // WALL_H
