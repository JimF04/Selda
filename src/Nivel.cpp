//
// Created by winjimmy on 5/5/2024.
//

#include <fstream>
#include "Nivel.h"
#include "Algoritmos/AStar.h"

Nivel::Nivel(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    camera.target = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
    camera.offset = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
    camera.rotation = 0.0f;
    camera.zoom = 5.0f;

}

void Nivel::LoadMap(std::string mapJson, int layerIndex, int layer[MAP_WIDTH][MAP_HEIGHT]) {
    // Leer json con los datos de la mapa
    std::ifstream file(mapJson);
    Json::Value root;
    file >> root;

    // Obtener la capa de Floor
    Json::Value layerJson = root["layers"][layerIndex];
    Json::Value data = layerJson["data"];

    // Llenar la matriz con los datos del JSON
    int index = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            layer[x][y] = data[index].asInt();
            ++index;
        }
    }
}

void Nivel::LayerCollision(int deltaX, int deltaY, int layer[MAP_WIDTH][MAP_HEIGHT], std::string type) {

    bool safeRoom = false;

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
                int tileType = layer[x][y];
                if (tileType != 0) {
                    // Si hay un tile diferente de cero, calcula su rectángulo de colisión
                    Rectangle tileRect = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE), TILE_SIZE, TILE_SIZE };
                    // Verifica si hay colisión entre la bola y el tile
                    if (CheckCollisionRecs(ballRect, tileRect)) {

                        if (type == "wall") {
                            deltaX = 0;
                            deltaY = 0;
                        }
                        else if (type == "saferoom") {
                            safeRoom = true;
                        }
                        else if (type == "stairs"){
                            for (int i=0; i<4; i++){
                                if (tileType == stairs[i]){
                                    onstairs=true;
                                }


                            }
                        }
                    }
                }
            }
        }

        if (type == "wall") {
            // Mueve la bola
            ball.Move(deltaX, deltaY);
        }

        ball.SetSafeRoom(safeRoom);


    }

    camera.target = ball.GetPosition();
}

void Nivel::DrawMiniMap() {
    // Definir las dimensiones y posición del minimapa

    const float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    const float miniMapWidth = 60;  // Ancho del minimapa en pantalla
    const float miniMapHeight = miniMapWidth / aspectRatio; // Alto del minimapa en pantalla

    // Calcular la posición del minimapa relativa a la cámara
    Vector2 minimapPosition;
    minimapPosition.x = camera.target.x - miniMapWidth / 2.0f + 87;
    minimapPosition.y = camera.target.y - miniMapHeight / 2.0f - 57;


    // Dibujar el fondo del minimapa (tu imagen del minimapa)
    DrawTexturePro(miniMapTexture, { 0.0f, 0.0f, static_cast<float>(miniMapTexture.width), static_cast<float>(miniMapTexture.height) },
                   { minimapPosition.x, minimapPosition.y, miniMapWidth, miniMapHeight }, { 0, 0 }, 0.0f, WHITE);
    // Dibujar la posición actual del jugador en el minimapa
    Vector2 ballPositionOnMiniMap = { minimapPosition.x + ball.GetPosition().x / (screenWidth / miniMapWidth),
                                      minimapPosition.y + ball.GetPosition().y / (screenHeight / miniMapHeight) };
    DrawRectangle(ballPositionOnMiniMap.x, ballPositionOnMiniMap.y, 1, 1, YELLOW);

}




void Nivel::DrawCenteredText(const char* text, int fontSize, Color color) {
    // Medir el ancho del texto para centrarlo
    int textWidth = MeasureText(text, fontSize);

    // Calcular la posición del texto relativa a la cámara
    Vector2 textPosition;
    textPosition.x = camera.target.x - (textWidth / 2);
    textPosition.y = camera.target.y - (fontSize / 2) - 70; // Agregar el desplazamiento vertical

    // Dibujar el texto
    DrawText(text, static_cast<int>(textPosition.x), static_cast<int>(textPosition.y), fontSize, color);
}


void Nivel::UpdateEspectros(Vector<Espectro>& espectros) {

    AStar astar(wall);

    if (!ball.GetSafeRoom()){

        for (auto& espectro : espectros) {
            if (espectro.FollowBreadcrumb(ball.crums)) {
                personaje_visto = true;
                find_AStar = true;
                break;
            } else {
                personaje_visto = false;
                find_AStar = false;
            }
        }

        if (find_AStar) {
            for (auto& espectro : espectros) {
                int ball_x_grid = static_cast<int>(ball.GetPosition().x / TILE_SIZE);
                int ball_y_grid = static_cast<int>(ball.GetPosition().y / TILE_SIZE);

                int enemy_x_grid = static_cast<int>(espectro.GetPosition().x / TILE_SIZE);
                int enemy_y_grid = static_cast<int>(espectro.GetPosition().y / TILE_SIZE);

                path = astar.findPath(enemy_x_grid, enemy_y_grid, ball_x_grid, ball_y_grid);
                path.pop();

                espectro.FollowPath(path);
            }
        }
    } else {
        personaje_visto = false;
    }
}


