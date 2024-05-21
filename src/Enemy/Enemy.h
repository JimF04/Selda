//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_ENEMY_H
#define RAYLIB_TEMPLATE_ENEMY_H

#include "../ball.h"
#include "raylib.h"
#include "../DataStructures/Stack.h"
#include "../DataStructures/Vector.h"
#include "../Hitbox.h"
#include "../Mapa.h"
#include <glog/logging.h>

#include <queue>

class Enemy
{
public:
    Enemy();
    virtual void Draw() const;
    virtual void Move(int deltaX, int deltaY);
    Vector2 GetPosition() const;
    int GetRadius() const;
    bool FollowBreadcrumb(Vector2& breadcrumbs);
    void setPosition(Vector2 pos);
    float distanceToPlayer;
    void Back_to_place(Stack<Vector2> stack, int tile);
    Vector2 initial_position;
    virtual void Ataque();
    void moveToTile(int targetX, int targetY, float pixel);
    void FollowPath(Stack<Vector2>& path);
    void LoopPath(queue<Vector2>& path);

    Texture2D spritesheet;
    Rectangle sourceRec;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    void UpdateAnimation();
    virtual bool GetCollisionWithHitbox(const Hitbox& hitbox) const;
    void SetEliminated(bool eliminated);
    bool IsEliminated() const;

    Vector2 position;
    Vector2 Get_inial_position();
    bool looping;
    bool llego;
    bool halegado();

    void set_llego(bool dime);
    void MoveRandomly(const int wall[MAP_WIDTH][MAP_HEIGHT]);
    void Animacion_random();

    float speed = 1.0f;
    int lives = 1;
    int damage = 1;

    int getDamage(){
        return damage;
    };

    void setSpeed(float speed){
        this->speed = speed;
    };

    void setLives(int lives){
        this->lives = lives;
    };

    void setDamage(int damage){
        this->damage = damage;
    };

protected:
    int radius;
    Color color;

    bool eliminated;

    int previousDeltaX;
    int previousDeltaY;

    void animacion_random();
};



#endif //RAYLIB_TEMPLATE_ENEMY_H
