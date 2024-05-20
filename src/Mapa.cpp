#include "Mapa.h"
#include "raymath.h"
#include "Mapa.h"
#include "raymath.h"
#include "raylib.h"
#include <json/json.h>
#include <glog/logging.h>

// Resto del código...

Mapa::Mapa() {
    // Añadir texturas
    Image image = LoadImage("../assets/Dungeon_Tileset.png");
    textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
    UnloadImage(image);
}

void Mapa::DrawTile(int pos_x, int pos_y, int tile_x, int tile_y, texture_asset texture) {
    Rectangle sourceRec = { (float)TILE_SIZE * tile_x, (float)TILE_SIZE * tile_y, (float)TILE_SIZE, (float)TILE_SIZE };
    Rectangle destRec = { (float)pos_x, (float)pos_y, (float)TILE_SIZE, (float)TILE_SIZE };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(textures[texture], sourceRec, destRec, origin, 0.0f, WHITE);
}

void Mapa::DrawMap(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileID = matriz[x][y];
            int tile_x = (tileID - 1) % tileSetSize;
            int tile_y = (tileID - 1) / tileSetSize;

            DrawTile(x * TILE_SIZE, y * TILE_SIZE, tile_x, tile_y, texture);
        }
    }
}

// Método para dibujar un mapa en una posición específica con un área circular
// Método para dibujar un mapa en una posición específica con un área circular
void Mapa::DrawMapAtPosition(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture, Vector2 center, float innerRadius, float outerRadius) {
    // Calcular el radio máximo permitido para dibujar
    float maxRadius = outerRadius - TILE_SIZE / 2;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            // Calcular la posición del tile en el mapa
            int tile_x = x * TILE_SIZE;
            int tile_y = y * TILE_SIZE;

            // Calcular la distancia desde el centro a la posición actual del tile
            float distance = Vector2Distance(center, { tile_x + TILE_SIZE / 2, tile_y + TILE_SIZE / 2 });

            // Verificar si la distancia está dentro del rango del radio interior y exterior
            if (distance >= innerRadius && distance <= maxRadius) {
                // Verificar si el punto está dentro del círculo
                if ((distance - innerRadius) * (distance - innerRadius) <= (maxRadius - innerRadius) * (maxRadius - innerRadius)) {
                    // Dibujar el tile si está dentro del círculo
                    int tileID = matriz[x][y];
                    int tilesetX = (tileID - 1) % tileSetSize;
                    int tilesetY = (tileID - 1) / tileSetSize;

                    DrawTile(tile_x, tile_y, tilesetX, tilesetY, texture);
                }
            }
        }
    }
}