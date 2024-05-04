//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL1_H
#define SELDA_NIVEL1_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../Ball.h"
#include "../Enemy/Enemy.h"
#include "../Mapa.h"

class Nivel1 {
public:
    Nivel1(int screenWidth, int screenHeight);
    void Update();
    void Draw();
private:
    int screenWidth;
    int screenHeight;
    Ball ball;
    Enemy enemigo;
    Camera2D camera;
    Mapa mapa;
};



#endif //SELDA_NIVEL1_H
