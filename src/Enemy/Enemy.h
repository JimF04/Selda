//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_ENEMY_H
#define RAYLIB_TEMPLATE_ENEMY_H

#include "../ball.h"
#include "raylib.h"
#include "../DataStructures/Stack.h"
#include "../Hitbox.h"

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
    //void Find_player(Stack<Vector2> stack, int i);
    void Back_to_place(Stack<Vector2> stack, int tile);
    Vector2 initial_position;
    void Ataque();
    void moveToTile(int targetX, int targetY, float pixel);
    void FollowPath(Stack<Vector2>& path);


    Texture2D spritesheet;
    Rectangle sourceRec;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    void UpdateAnimation();
    bool GetCollisionWithHitbox(const Hitbox& hitbox) const;
    void SetEliminated(bool eliminated);
    bool IsEliminated() const;

    Vector2 position;
private:
    int radius;
    Color color;
    float speed;
    
    bool eliminated;
};


#endif //RAYLIB_TEMPLATE_ENEMY_H
