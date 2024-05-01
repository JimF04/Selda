//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_WALL_H
#define RAYLIB_TEMPLATE_WALL_H

#include "raylib.h"

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


#endif //RAYLIB_TEMPLATE_WALL_H
