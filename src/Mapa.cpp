#include <fstream>
#include <iostream>
#include "Mapa.h"

Texture2D textures[MAX_TEXTURES];

// Método para dibujar un tile
void DrawTile( int pos_x, int pos_y, int tile_x, int tile_y, texture_asset texture){
    Rectangle sourceRec = {(float)TILE_SIZE * tile_x, (float)TILE_SIZE * tile_y, (float)TILE_SIZE, (float)TILE_SIZE };
    Rectangle destRec = {(float)pos_x, (float)pos_y, (float)TILE_SIZE, (float)TILE_SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(textures[texture], sourceRec, destRec, origin, 0.0f, WHITE);

}

Mapa::Mapa() {
    // Añadir texturas
    Image image = LoadImage("../assets/Dungeon_Tileset.png");
    textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
    UnloadImage(image);
}

// Método para dibujar un sólo mapa
void Mapa::DrawMap(int matriz[][MAP_HEIGHT], int tileSetSize, texture_asset texture) {
    for (int y = 0; y < MAP_HEIGHT; y++){
        for (int x = 0; x < MAP_WIDTH; x++){
            int tileID = matriz[x][y];
            int tile_x = (tileID - 1) % tileSetSize;
            int tile_y = (tileID - 1) / tileSetSize;

            DrawTile(x * TILE_SIZE, y * TILE_SIZE, tile_x, tile_y, texture);
        }
    }
}