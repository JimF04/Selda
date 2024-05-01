#include <fstream>
#include <iostream>
#include "Mapa.h"
#include <unordered_set>

std::unordered_set<int> wallTiles = {1,2,3,4,5,6,11,16,21,26,31,36,41,42,43,44,45,46,51,52,53,54,55,56};


#define TILE_SIZE 16
#define MAP_WIDTH 50
#define MAP_HEIGHT 38

#define MAX_TEXTURES 1
typedef enum {
    TEXTURE_TILEMAP = 0
} texture_asset;

Texture2D textures[MAX_TEXTURES];

int map[MAP_WIDTH][MAP_HEIGHT];

void DrawTile( int pos_x, int pos_y, int tile_x, int tile_y){

    Rectangle sourceRec = {(float)TILE_SIZE * tile_x, (float)TILE_SIZE * tile_y, (float)TILE_SIZE, (float)TILE_SIZE };
    Rectangle destRec = {(float)pos_x, (float)pos_y, (float)TILE_SIZE, (float)TILE_SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(textures[TEXTURE_TILEMAP], sourceRec, destRec, origin, 0.0f, WHITE);

}

Mapa::Mapa(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    darkGreen = Color{20, 160, 133, 255};

    ball = Ball();
    const int wallPosX = 500;
    const int wallPosY = 100;
    const int wallWidth = 50;
    const int wallHeight = 50;
    Vector2 wallPosition = { wallPosX, wallPosY };
    pared = Wall(wallPosition, wallWidth, wallHeight);
    enemigo = Enemy();

    camera = { 0 };
    camera.target = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
    camera.offset = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    Image image = LoadImage("../src/resources/Dungeon_Tileset.png");
    textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
    UnloadImage(image);

    std::ifstream file("../map.json");
    // Leer el archivo JSON y parsearlo
    Json::Value root;
    file >> root;

    // Obtener la capa de datos
    Json::Value layer = root["layers"][0];

    // Obtener los datos (la matriz de números)
    Json::Value data = layer["data"];

    // Llenar la matriz con los datos del JSON
    int index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[x][y] = data[index].asInt();
            ++index;
        }
    }
}

void Mapa::Update() {
    int deltaX = 0;
    int deltaY = 0;

    if (IsKeyDown(KEY_W))
        deltaY -= 2;
    if (IsKeyDown(KEY_S))
        deltaY += 2;
    if (IsKeyDown(KEY_A))
        deltaX -= 2;
    if (IsKeyDown(KEY_D))
        deltaX += 2;

    // Calcula la posición proyectada de la bola
    Vector2 projectedPosition = { ball.GetPosition().x + deltaX, ball.GetPosition().y + deltaY };

    // Verifica si la posición proyectada está dentro de los límites del mapa
    if (projectedPosition.x >= 0 && projectedPosition.x <= MAP_WIDTH * TILE_SIZE - ball.GetRadius() * 2 &&
        projectedPosition.y >= 0 && projectedPosition.y <= MAP_HEIGHT * TILE_SIZE - ball.GetRadius() * 2) {
        // Calcula el rectángulo de colisión de la bola en su posición proyectada
        // Calcula el rectángulo de colisión de la bola en su posición proyectada
        Rectangle ballRect = { projectedPosition.x - ball.GetRadius(), projectedPosition.y - ball.GetRadius(), static_cast<float>(ball.GetRadius() * 2), static_cast<float>(ball.GetRadius() * 2) };


        // Verifica si la bola está colisionando con un tile que representa una pared
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                int tileType = map[x][y];
                if (wallTiles.find(tileType) != wallTiles.end()) {
                    // Si el tile representa una pared, calcula su rectángulo de colisión
                    Rectangle tileRect = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE), TILE_SIZE, TILE_SIZE };
                    // Verifica si hay colisión entre la bola y el tile
                    if (CheckCollisionRecs(ballRect, tileRect)) {
                        // Si hay colisión, evita que la bola se mueva en esa dirección
                        if (deltaX > 0) {
                            deltaX = 0;
                        } else if (deltaX < 0) {
                            deltaX = 0;
                        }
                        if (deltaY > 0) {
                            deltaY = 0;
                        } else if (deltaY < 0) {
                            deltaY = 0;
                        }
                    }
                }
            }
        }

        // Mueve la bola
        ball.Move(deltaX, deltaY);
    }

    enemigo.FollowBreadcrumb(ball.GetPosition());

    camera.target = ball.GetPosition();
}



void Mapa::DrawMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileType = map[x][y];
            int tile_x;
            int tile_y;

            if (tileType % 10 == 0){
                tile_x = 9;
                tile_y = (tileType / 10) - 1;
            } else if (tileType < 10 && (tileType%10 != 0)){
                tile_x = tileType - 1;
                tile_y = 0;
            } else if (tileType > 10){
                tile_x = (tileType % 10) - 1;
                tile_y = (tileType / 10);
            }

            DrawTile(x * TILE_SIZE, y * TILE_SIZE, tile_x, tile_y);
        }
    }
}

void Mapa::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    DrawMap();
    ball.Draw();
    enemigo.Draw();

    EndMode2D();
}