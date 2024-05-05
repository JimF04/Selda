#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "Enemy/Enemy.h"

// Declaración hacia adelante de Enemy
class Enemy;

class Ball {
public:
    Ball();
    void Draw() const;
    void Move(int deltaX, int deltaY);
    Vector2 GetPosition() const;
    int GetRadius() const;
    void setPosition(Vector2 pos);
    int GetLives() const;
    void DecreaseLives();
    bool CheckCollisionWithEnemy(const Enemy& enemy) const;
private:
    Vector2 position;
    int radius;
    Color color;
    int lives;
};

#endif // BALL_H
