#ifndef SELDA_COFRES_H
#define SELDA_COFRES_H


#include "Objetos.h"
#include "raylib.h"
#include "raymath.h"
#include "../Nivel.h"

class Cofres{
public:
    Cofres();
    void UpdateAnimation();
    void Draw() const;
    void Still();
    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPosition);
    void DrawCounter(Camera2D camera) const;

    Texture2D spritesheet;
    Rectangle sourcerec;
    Vector4 collisionBox;
    int framecounter;
    int currentframe;
    int framespeed;
    int time_for_crums;
    Camera2D camera;
    bool abierto = false;
private:
    Vector2 position;

};
#endif //SELDA_COFRES_H
