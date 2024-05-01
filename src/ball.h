//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_BALL_H
#define RAYLIB_TEMPLATE_BALL_H

#include "raylib.h"

class Ball
{
public:
    Ball();
    void Draw() const;
    void Move(int deltaX, int deltaY); // Declaración del método Move
    Vector2 GetPosition() const;
    int GetRadius() const;
    int playerTileX;
    int playerTileY;
    Vector2 position;
    int radius;
private:

    Color color;
};


#endif //RAYLIB_TEMPLATE_BALL_H
