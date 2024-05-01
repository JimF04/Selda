//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_MAPA_H
#define RAYLIB_TEMPLATE_MAPA_H

#include "raylib.h"
#include "ball.h"
#include "Wall.h"
#include "Enemy.h"
#include <json/json.h>

class Mapa {
public:
    Mapa(int screenWidth, int screenHeight);
    void Update();
    void Draw();

private:
    int screenWidth;
    int screenHeight;
    Color darkGreen;
    Ball ball;
    Wall pared;
    Enemy enemigo;
    Camera2D camera;
    void DrawMap();
};

#endif //RAYLIB_TEMPLATE_MAPA_H
