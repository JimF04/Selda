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

#define TILE_SIZE 16

#define MAP_WIDTH 50
#define MAP_HEIGHT 38

#define MAX_TEXTURES 2
typedef enum {
    TEXTURE_TILEMAP = 0,
    TEXTURE_FOREST
} texture_asset;

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
    void DrawMaps();
    void DrawMap(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture);
};

#endif //RAYLIB_TEMPLATE_MAPA_H
