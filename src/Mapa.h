//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_MAPA_H
#define RAYLIB_TEMPLATE_MAPA_H

#include "raylib.h"
#include <json/json.h>
#include <glog/logging.h>
#include "raymath.h"

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

// Variables de la clase
    Texture2D textures[MAX_TEXTURES];

// Metodos de la clase
    Mapa();

/**
 * Dibuja un mapa en la pantalla
 * @param matriz Matriz que representa el mapa
 * @param tileSetSize Tamaño del spritesheet
 * @param texture Textura del spritesheet
 */
    void DrawMap(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture);

/**
* Dibuja un tile en la posición especificada
* @param pos_x Posición en x
* @param pos_y Posición en y
* @param tile_x Posición en x del tile en el spritesheet
* @param tile_y Posición en y del tile en el spritesheet
* @param texture Textura del spritesheet
*/
    void DrawTile( int pos_x, int pos_y, int tile_x, int tile_y, texture_asset texture);

/**
 * Dibuja un mapa en la pantalla en una posición específica
 * @param matriz Matriz que representa el mapa
 * @param tileSetSize Tamaño del spritesheet
 * @param texture Textura del spritesheet
 * @param center Centro del círculo
 * @param innerRadius Radio interior del círculo
 * @param outerRadius Radio exterior del círculo
 */
    void DrawMapAtPosition(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture, Vector2 center, float innerRadius, float outerRadius);

private:
    int screenWidth;
    int screenHeight;
};

#endif //RAYLIB_TEMPLATE_MAPA_H
