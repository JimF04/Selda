//
// Created by winjimmy on 5/5/2024.
//

#include <fstream>
#include "Nivel.h"
#include "Algoritmos/AStar.h"
#include "Algoritmos/Backtrack.h"
#include "Enemy/Ojo_Espectral.h"
#include <random>
#include "math.h"
#include <chrono>
#include <ctime>

std::chrono::time_point<std::chrono::system_clock> lastTrapCollisionTime;


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
    auto currentTime = std::chrono::system_clock::now();


    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTrapCollisionTime).count();

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

                        else if (type == "falsefloor"){
                            ball.lives=0;
                        }
                        else if (type == "traps" && elapsedTime >= 2600){
                            ball.DecreaseLives(1);
                            lastTrapCollisionTime = currentTime;
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
    Backtrack backtrack(wall);

    for(auto& espectros: espectros){
        if (!collisionDetected && GetTime() - lastCollisionDetectionTime >= 2.0) {

            if (ball.CheckCollisionWithEnemy(espectros)) {
                ball.DecreaseLives(espectros.getDamage());

                collisionDetected = true;
                lastCollisionDetectionTime = GetTime();
            }
        }
        collisionDetected = false;

    }

    if (!ball.GetSafeRoom()) {
        for (auto& espectro : espectros) {
            if (espectro.FollowBreadcrumb(ball.crums) || visto_por_ojo) {
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
                if(espectro.type != "azul"){
                    int ball_x_grid = static_cast<int>(ball.GetPosition().x / TILE_SIZE);
                    int ball_y_grid = static_cast<int>(ball.GetPosition().y / TILE_SIZE);

                    int enemy_x_grid = static_cast<int>(espectro.GetPosition().x / TILE_SIZE);
                    int enemy_y_grid = static_cast<int>(espectro.GetPosition().y / TILE_SIZE);

                    Stack<Vector2> path = astar.findPath(enemy_x_grid, enemy_y_grid, ball_x_grid, ball_y_grid);
                    path.pop();  // Eliminar el primer nodo del camino si es necesario
                    espectro.FollowPath(path);
                    espectro.set_llego(false);
                }

            }
        } else {
            for (auto& espectro : espectros) {
                if(espectro.type != "azul"){
                    int enemy_x_grid = static_cast<int>(espectro.GetPosition().x / TILE_SIZE);
                    int enemy_y_grid = static_cast<int>(espectro.GetPosition().y / TILE_SIZE);

                    int initial_x_grid = static_cast<int>(espectro.Get_inial_position().x / TILE_SIZE);
                    int initial_y_grid = static_cast<int>(espectro.Get_inial_position().y / TILE_SIZE);

                    if(enemy_x_grid == initial_x_grid && enemy_y_grid == initial_y_grid || espectro.halegado()){
                        espectro.set_llego(true);

                    }
                    else{
                        Stack<Vector2> pathback = backtrack.findPath(enemy_x_grid, enemy_y_grid, initial_x_grid, initial_y_grid);
                        pathback.pop();  // Eliminar el primer nodo del camino si es necesario
                        espectro.FollowPath(pathback);
                    }

                }


                // Verificar si el espectro ya llegó a su posición inicial alguna vez

            }
        }
    } else {
        personaje_visto = false;
    }

    // Modo patrulla si no se ve al personaje

}

void Nivel::UpdatesAzules(Vector<Espectro> &azules, Vector2 player_pos) {
    for(auto& espectro: azules){
        if(espectro.type == "azul"){

            if(visto_por_ojo && !espectro.halegado()){
                espectro.setPosition({(player_pos.x/TILE_SIZE)+2,(player_pos.y/TILE_SIZE)-2});
                espectro.set_llego(true);
            }
            else{
                espectro.MoveRandomly(wall);
                espectro.set_llego(false);
            }
        }
    }
}

void Nivel::UpdateRatones(Vector<Ratones>& ratones) {

     AStar aestar(wall);

    for(auto& raton:ratones){

        raton.MoveRandomly(wall);
    }

}


void Nivel::UpdateOjos(Vector<Ojo_Espectral> &ojos, Vector2 posision_player) {
    for(auto& ojo:ojos){

        float dis = std::sqrt(std::pow(ojo.GetPosition().x - posision_player.x, 2) + std::pow(ojo.GetPosition().y - posision_player.y, 2));
        if(dis<30){
            visto_por_ojo = true;
            ojo.Animacion_random();
            break;
        }
        else{
            visto_por_ojo = false;
        }

    }
}

void Nivel::ResetLevel(float BallXPos, float BallYPos) {
    ball.setPosition({BallXPos, BallYPos});
    ball.ResetLives();
}

void Nivel::DrawChestCounter() {
    Vector2 drawPosition = {-115 + camera.target.x, -60 + camera.target.y};
    DrawText(FormatText("x: %d", contadorCofres), drawPosition.x, drawPosition.y, 10, WHITE);
}

void Nivel::UpdateChests(Vector<Cofres>& cofres) {
    for(auto& cofre : cofres){
        bool cofreDetectado = false;
        float distancia = Vector2Distance(ball.GetPosition(),cofre.getPosition());
        if(distancia < ball.GetRadius() + 11 && !cofre.abierto){
            if(IsKeyDown(KEY_O) && !cofreDetectado){ // Verificar si la tecla O está presionada y el cofre no ha sido detectado
                cofre.UpdateAnimation();
                cofre.drawTile();
                contadorCofres++;
                cout<<contadorCofres;
                cofreDetectado = true;
                cofre.abierto = true;// Marcar el cofre como detectado para este fotograma
            }
            else if (!IsKeyDown(KEY_O)) {
                cofreDetectado = false; // Reiniciar la detección del cofre si la tecla O ya no está presionada
            }
        }
    }
}

void Nivel::UpdateJars(Vector<Jarrones>& jarrones){
    for(auto& jarron: jarrones){
        bool jarronDetectado = false;
        float distancia = Vector2Distance(ball.GetPosition(), jarron.getPosition());
        if(distancia < ball.GetRadius() + 20 && !jarron.abierto){
            if(IsKeyDown(KEY_L) && !jarronDetectado){
                jarron.UpdateAnimation();
                jarron.drawTile();
                ball.IncreaseLives();
                jarronDetectado = true;
                jarron.abierto = true;
            }
                // Solo restablece jarronDetectado si el jarrón está abierto y la tecla Q está suelta
            else if (!IsKeyDown(KEY_L) && jarron.abierto) {
                jarronDetectado = false;
            }
        }
    }
}

void Nivel::Dar_genes(Vector<Vector3>& alelos, Vector<Espectro>* espectros) {
    // Verificar que el vector de alelos no esté vacío
    if (alelos.empty()) {
        std::cerr << "Error: El vector de alelos está vacío." << std::endl;
        throw std::runtime_error("El vector de alelos está vacío.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, alelos.getSize() - 1); // Distribución para seleccionar índices de alelos

    // Iterar sobre cada espectro y asignar un valor aleatorio de alelos a un atributo aleatorio
    for (auto& espectro : *espectros) {
        int random_index = dist(gen);
        std::cout << "Índice aleatorio generado: " << random_index << std::endl;

        if (random_index < 0 || random_index >= alelos.getSize()) {
            std::cerr << "Error: Índice de alelo aleatorio fuera de rango." << std::endl;
            throw std::out_of_range("Índice de alelo aleatorio fuera de rango.");
        }

        Vector3 alelo = alelos[random_index];

        // Debugging: imprimir el alelo seleccionado y los valores asignados
        std::cout << "Asignando alelo: (" << alelo.x << ", " << alelo.y << ", " << alelo.z << ") al espectro" << std::endl;

        espectro.speed = alelo.x;
        espectro.lives = alelo.y;
        espectro.damage = alelo.z;

        std::cout << "Asignación completada para el espectro." << std::endl;
    }

    std::cout << "Función Dar_genes completada." << std::endl;
}

Vector<Espectro> Nivel::Regresar_resultado(string type){
    if (type == "gris"){
        return espectros;
    } else if (type == "rojo"){
        return espectroRojo;
    } else if (type == "azul"){}
        return espectroAzul;
}

Vector<Vector3> Nivel::CargarAleloDesdeArchivo(const std::string& filename) {
    Vector<Vector3> alelos;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            float x, y, z;
            if (iss >> x >> y >> z) {
                alelos.push_back(Vector3{x, y, z});
            }
        }
        file.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo de alelos.");
    }

    return alelos;
}








