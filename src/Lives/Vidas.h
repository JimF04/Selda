#ifndef VIDAS_H
#define VIDAS_H
#include "raymath.h"
#include "raylib.h"
class Vidas {
public:
    Vidas(int initialLives);
    void DecreaseLife();
    int GetLives() const;
    bool IsAlive() const;
    void ResetLives();
    void Draw() const;
    Texture2D spriteshit;
    Rectangle surceRec;
private:
    int lives;
    int initialLives;
    Vector2 position;
};

#endif // VIDAS_H
