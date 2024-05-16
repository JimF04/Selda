#ifndef SELDA_JARRONES_H
#define SELDA_JARRONES_H
#include "Objetos.h"
#include "raylib.h"
#include "raymath.h"

class Jarrones{

public:
    Jarrones();
    void Updateanimation();
    void Draw() const;
    Vector2 GetPosition() const;
    void SetPosition(Vector2 newposition);
    void Anim();
//    void Draw() const override;
    Texture2D spriteshet;
    Rectangle sourcerec;
    Vector4 collisionbox;
    int framecounter;
    int currentframe;
    int framespeed;
    int time_for_crums;
    Camera camera;
    bool abierto;

private:
    Vector2 position;

};
#endif //SELDA_JARRONES_H
