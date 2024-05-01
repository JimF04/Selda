//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_ENEMY_H
#define RAYLIB_TEMPLATE_ENEMY_H

#include "ball.h"
#include "raylib.h"

class Enemy
{
public:
    Enemy();
    void Draw() const;
    void Move(int deltaX, int deltaY); // Declaración del método Move
    Vector2 GetPosition() const;
    int GetRadius() const;
    void FollowBreadcrumb(const Vector2& target);

private:
    Vector2 position;
    int radius;
    Color color;
    int speed;
};


#endif //RAYLIB_TEMPLATE_ENEMY_H
