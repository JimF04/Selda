#include "Objetos.h"
#include "raylib.h"
#include "raymath.h"



#ifndef SELDA_COFRES_H
#define SELDA_COFRES_H
class Nivel1;

class Cofres{
public:
    Cofres(Nivel1* nivel1);
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
private:
    Vector2 position;
    Nivel1* nivelPtr;

};
#endif //SELDA_COFRES_H
