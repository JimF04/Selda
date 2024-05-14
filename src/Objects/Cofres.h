#include "Objetos.h"
#include "raylib.h"
#include "raymath.h"

#ifndef SELDA_COFRES_H
#define SELDA_COFRES_H
class Cofres{
public:
    Cofres();
    void UpdateAnimation();
    void Draw() const;
    void Still();


    Texture2D spritesheet;
    Rectangle sourcerec;
    Vector4 collisionBox;
    int framecounter;
    int currentframe;
    int framespeed;
    int time_for_crums;
private:
    Vector2 position;

};
#endif //SELDA_COFRES_H
