#ifndef SELDA_OBJETOS_H
#define SELDA_OBJETOS_H

#include "raylib.h"
#include "raymath.h"

class Objetos{
public:
    Objetos();
    void drawTile();

    void setSize(int newSize);
    int getSize();

    void setPosition(Vector2 newPos);
    Vector2 getPosition();


protected:
    Texture2D spritesheet;
    int size;
    Vector2 pos;

    Vector2 tilepos;

};

#endif //SELDA_OBJETOS_H