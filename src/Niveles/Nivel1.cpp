//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel1.h"

// Incicializar matrices para cada layer
int map[MAP_WIDTH][MAP_HEIGHT];
int wall[MAP_WIDTH][MAP_HEIGHT];

Nivel1::Nivel1(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    enemigo = Enemy();

    // Leer json con los datos de la mapa
    std::ifstream file("../map.json");
    Json::Value root;
    file >> root;

    // Obtener la capa de Floor
    Json::Value layer = root["layers"][0];
    Json::Value data = layer["data"];

    // Llenar la matriz con los datos del JSON
    int index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[x][y] = data[index].asInt();
            ++index;
        }
    }
    // Obtener la capa Wall
    Json::Value wallLayer = root["layers"][1];
    Json::Value wallData = wallLayer["data"];
    index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            wall[x][y] = wallData[index].asInt();
            ++index;
        }
    }
}

void Nivel1::Update() {
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
        Rectangle ballRect = { projectedPosition.x - ball.GetRadius(), projectedPosition.y - ball.GetRadius(), static_cast<float>(ball.GetRadius() * 2), static_cast<float>(ball.GetRadius() * 2) };

        // Verifica si la bola está colisionando con algún tile diferente de cero en la matriz 'wall'
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                int tileType = wall[x][y];
                if (tileType != 0) {
                    // Si hay un tile diferente de cero, calcula su rectángulo de colisión
                    Rectangle tileRect = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE), TILE_SIZE, TILE_SIZE };
                    // Verifica si hay colisión entre la bola y el tile
                    if (CheckCollisionRecs(ballRect, tileRect)) {
                        // Si hay colisión, detiene el movimiento de la bola
                        deltaX = 0;
                        deltaY = 0;
                    }
                }
            }
        }

        // Mueve la bola
        ball.Move(deltaX, deltaY);

//        float ball_x = ball.GetPosition().x;
//        float ball_y = ball.GetPosition().y;
//
//        std::cout << "Ball position: " << ball_x << ", " << ball_y << std::endl;
    }

    enemigo.FollowBreadcrumb(ball.GetPosition());

    camera.target = ball.GetPosition();
}


void Nivel1::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(map, 10, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 10, TEXTURE_TILEMAP);
    ball.Draw();
    enemigo.Draw();

    EndMode2D();
}