//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_ENEMY_H
#define RAYLIB_TEMPLATE_ENEMY_H

#include "../ball.h"
#include "raylib.h"
#include "../DataStructures/Stack.h"

class Enemy
{
public:
    Enemy();
    void Draw() const;
    void Move(int deltaX, int deltaY); // Declaración del método Move
    Vector2 GetPosition() const;
    int GetRadius() const;
    bool FollowBreadcrumb(Vector2& breadcrumbs);
    void setPosition(Vector2 pos);
    float distanceToPlayer;
    void Find_player(Stack<Vector2> stack, int i);

private:
    Vector2 position;
    int radius;
    Color color;
    int speed;
};


#endif //RAYLIB_TEMPLATE_ENEMY_H
