#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "Enemy/Enemy.h"
#include "Hitbox.h"

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
    bool GetSafeRoom();
    void SetSafeRoom(bool safe);
    bool safeRoom;

    int GetLives() const;
    void DecreaseLives();
    bool CheckCollisionWithEnemy(const Enemy& enemy) const;
private:
    Vector2 position;
    int radius;
    Color color;
    int lives;
    Hitbox hitbox; // Agregar el objeto Hitbox como un miembro de la clase Ball
};


#endif // BALL_H
