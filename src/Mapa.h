//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_MAPA_H
#define RAYLIB_TEMPLATE_MAPA_H

#include "raylib.h"
#include "ball.h"
#include "Wall.h"
#include "Enemy.h"

class Mapa {
public:
    Mapa(int screenWidth, int screenHeight);
    void Update();
    void Draw();

    unsigned int tilesX;
    unsigned int tilesY;
    unsigned char *tileIds;
    unsigned char *tileFog;
    void ClearFogAroundPlayer();
private:
    int screenWidth;
    int screenHeight;
    Color darkGreen;
    Ball personaje;
    Wall pared;
    Enemy enemigo;
    Camera2D camera;
    void DrawMap();
    void DrawUI();

};

#endif //RAYLIB_TEMPLATE_MAPA_H
