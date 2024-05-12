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
    void Back_to_place(Stack<Vector2> stack, int tile);
    Vector2 initial_position;


    Texture2D spritesheet;
    Rectangle sourceRec;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    void UpdateAnimation();

    Vector2 position;
private:
    int radius;
    Color color;
    float speed;
};


#endif //RAYLIB_TEMPLATE_ENEMY_H
