//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel2.h"

// Incicializar matrices para cada layer
int floor2[MAP_WIDTH][MAP_HEIGHT];
int wall2[MAP_WIDTH][MAP_HEIGHT];
int saferoom2[MAP_WIDTH][MAP_HEIGHT];

Stack<Vector2> path2;

Nivel2::Nivel2(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    enemigo = Enemy();
    ball.setPosition({100,410});


    // Leer json con los datos de la mapa
    std::ifstream file("../Level2.json");
    Json::Value root;
    file >> root;

    // Obtener la capa de Floor
    Json::Value layer = root["layers"][0];
    Json::Value data = layer["data"];

    // Llenar la matriz con los datos del JSON
    int index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            floor2[x][y] = data[index].asInt();
            ++index;
        }
    }

// Obtener la capa Safe
    Json::Value safeLayer = root["layers"][1];
    Json::Value safeData = safeLayer["data"];
    index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            saferoom2[x][y] = safeData[index].asInt();
            ++index;
        }
    }

    // Obtener la capa Wall
    Json::Value wallLayer = root["layers"][2];
    Json::Value wallData = wallLayer["data"];
    index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            wall2[x][y] = wallData[index].asInt();
            ++index;
        }
    }


// Obtener la capa Safe
    Json::Value safeLayer2 = root["layers"][1];
    Json::Value safeData2 = safeLayer["data"];
    index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            saferoom2[x][y] = safeData[index].asInt();
            ++index;
        }
    }

    // Obtener la capa Wall
    Json::Value wallLayer2 = root["layers"][2];
    Json::Value wallData2 = wallLayer["data"];
    index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            wall2[x][y] = wallData[index].asInt();
            ++index;
        }
    }

}

void Nivel2::Update() {
    int deltaX = 0;
    int deltaY = 0;

    if (IsKeyDown(KEY_W))
        deltaY -= 1;
    if (IsKeyDown(KEY_S))
        deltaY += 1;
    if (IsKeyDown(KEY_A))
        deltaX -= 1;
    if (IsKeyDown(KEY_D))
        deltaX += 1;

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
                int tileType = wall2[x][y];
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

    }


    // Convertir las coordenadas de la bola a las coordenadas de la matriz
    int ball_x_grid = static_cast<int>( ball.GetPosition().x / TILE_SIZE);
    int ball_y_grid = static_cast<int>( ball.GetPosition().y / TILE_SIZE);

    int enemy_x_grid = static_cast<int>( enemigo.GetPosition().x / TILE_SIZE);
    int enemy_y_grid = static_cast<int>( enemigo.GetPosition().y / TILE_SIZE);



    path2.pop(); // Elimina la posición actual del enemigo
    //astar.printPath(path);
    Stack<Vector2> pathCopy = path2;

    enemigo.FollowBreadcrumb(ball.GetPosition());

    camera.target = ball.GetPosition();
}

void Nivel2::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor2, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom2, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall2, 25, TEXTURE_TILEMAP);

    ball.Draw();
    enemigo.Draw();

    EndMode2D();
}