//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_MAPA_H
#define RAYLIB_TEMPLATE_MAPA_H

#include "raylib.h"
#include <json/json.h>
#include <glog/logging.h>

#define TILE_SIZE 16

#define MAP_WIDTH 75
#define MAP_HEIGHT 50

#define MAX_TEXTURES 2
typedef enum {
    TEXTURE_TILEMAP = 0,
    TEXTURE_FOREST
} texture_asset;

class Mapa {
public:
    Mapa();
    void DrawMap(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture);
    void DrawTile(int pos_x, int pos_y, int tile_x, int tile_y, texture_asset texture);
    void DrawMapAtPosition(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture, Vector2 center, float innerRadius, float outerRadius);
    Texture2D textures[MAX_TEXTURES];

private:
    int screenWidth;
    int screenHeight;
};

#endif //RAYLIB_TEMPLATE_MAPA_H
