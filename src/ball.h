//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_BALL_H
#define RAYLIB_TEMPLATE_BALL_H

#include "raylib.h"
#include "Enemy/Enemy.h"



class Enemy;
class Ball
{
public:
    Ball();
    void Draw() const;
    void Move(int deltaX, int deltaY); // Declaración del método Move
    Vector2 GetPosition() const;
    int GetRadius() const;
    void setPosition(Vector2 pos);
    bool GetSafeRoom();
    void SetSafeRoom(bool safe);
    bool safeRoom;
    int GetLives() const;
    void DecreaseLives();
    bool CheckCollisionWithEnemy(const  Enemy& enemy) const;
    void ResetLives();

private:
    Vector2 position;
    int radius;
    Color color;
    int lives;
    static const int INNITIAL_LIVES = 5;
};


#endif //RAYLIB_TEMPLATE_BALL_H
