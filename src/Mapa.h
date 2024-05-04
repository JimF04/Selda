//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_MAPA_H
#define RAYLIB_TEMPLATE_MAPA_H

#include "raylib.h"
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
    Mapa();
    void Update();
    void Draw();

    void DrawMap(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture);

private:
    int screenWidth;
    int screenHeight;
};

#endif //RAYLIB_TEMPLATE_MAPA_H
