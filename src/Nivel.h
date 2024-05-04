//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL_H
#define SELDA_NIVEL_H


#include "Mapa.h"
#include "raylib.h"

class Nivel {
public:
    Nivel(int screenWidth, int screenHeight);
    virtual void Update() = 0;
    virtual void Draw() = 0;
protected:
    int screenWidth;
    int screenHeight;
    Camera2D camera;
    Mapa mapa;
};


#endif //SELDA_NIVEL_H
