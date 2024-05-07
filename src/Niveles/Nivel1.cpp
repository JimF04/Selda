#include "Nivel1.h"
#include "raylib.h"
#include "../ball.h"
#include "raymath.h"
#include "../Enemy/Enemy.h"







    // Incicializar matrices para cada layer
    int floormap[MAP_WIDTH][MAP_HEIGHT];
    int wall[MAP_WIDTH][MAP_HEIGHT];

    Stack<Vector2> path;

    Nivel1::Nivel1(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
        // Iniciar clases
        ball = Ball();
        enemigo = Enemy();
        collisionDetected = false;
        lastCollisionDetectionTime = GetTime();

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
                floormap[x][y] = data[index].asInt();
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

        camera.zoom = 1.0f;
    }

    void Nivel1::ResetLevel() {
        // Reiniciar la bola
        ball = Ball();

        // Reiniciar el enemigo
        enemigo = Enemy();

        // Reiniciar otros estados necesarios
        collisionDetected = false;
        lastCollisionDetectionTime = GetTime();
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

        }



        // Convertir las coordenadas de la bola a las coordenadas de la matriz
        int ball_x_grid = static_cast<int>( ball.GetPosition().x / TILE_SIZE);
        int ball_y_grid = static_cast<int>( ball.GetPosition().y / TILE_SIZE);

        int enemy_x_grid = static_cast<int>( enemigo.GetPosition().x / TILE_SIZE);
        int enemy_y_grid = static_cast<int>( enemigo.GetPosition().y / TILE_SIZE);


         //Crear una instancia de AStar y encontrar el camino
        AStar astar(wall);
        path = astar.findPath(enemy_x_grid,enemy_y_grid,ball_x_grid,ball_y_grid);

        path.pop(); // Elimina la posición actual del enemigo
        //astar.printPath(path);
        Stack<Vector2> pathCopy = path;

        enemigo.FollowBreadcrumb(ball.GetPosition());

        camera.target = ball.GetPosition();

        if (GetTime() - lastCollisionDetectionTime >= 2.0) {
            collisionDetected = false; // Restablece la bandera de colisión
        }
        float distance = Vector2Distance(ball.GetPosition(),enemigo.GetPosition());
        if(distance<ball.GetRadius()){
            if(IsKeyDown(KEY_P)){
                enemigo.setPosition({-1000,1000});
            }
        }
        // Realiza la detección de colisiones solo si ha pasado suficiente tiempo y no se ha detectado una colisión recientemente
        if (!collisionDetected && GetTime() - lastCollisionDetectionTime >= 2.0) {
            if (ball.CheckCollisionWithEnemy(enemigo)) {
                // Si hay colisión, puedes hacer lo que necesites aquí
                // Por ejemplo, decrementar vidas, mover la bola, etc.
                ball.DecreaseLives(); // Disminuir contador de vidas

                // Verifica si la bola se quedó sin vidas
                if (ball.GetLives() <= 0) {
                    // La bola ha perdido todas sus vidas
                    ResetLevel();
                }

                // Establece la bandera de colisión en true
                collisionDetected = true;

                // Actualiza el tiempo de la última detección de colisiones
                lastCollisionDetectionTime = GetTime();
            }
        }
    }

    void Nivel1::Draw() {
        BeginMode2D(camera);

        ClearBackground(BLACK);
        mapa.DrawMap(floormap, 10, TEXTURE_TILEMAP);
        mapa.DrawMap(wall, 10, TEXTURE_TILEMAP);
        ball.Draw();
        enemigo.Draw();

    // Calcula el desplazamiento necesario para centrar los círculos en cada celda
        float offsetX = (TILE_SIZE - 5) / 2.0f; // 5 es el radio del círculo
        float offsetY = (TILE_SIZE - 5) / 2.0f;

    // Dibujar círculos verdes en cada posición del camino encontrado
        while (!path.empty()) {
            Vector2 point = path.top();
            path.pop();

            // Convertir las coordenadas de la matriz a las coordenadas del mundo
            float worldX = static_cast<float>(point.x * TILE_SIZE + offsetX);
            float worldY = static_cast<float>(point.y * TILE_SIZE + offsetY);

            // Dibujar un círculo verde en la posición del mundo
            DrawCircle(worldX, worldY, 5, GREEN);
        }


        EndMode2D();
    }