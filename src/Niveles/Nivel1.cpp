//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel1.h"
#include "raylib.h"
#include "../ball.h"
#include "raymath.h"
#include "../Enemy/Enemy.h"



Stack<Vector2> path;
Stack<Vector2> pathCopy;



Nivel1::Nivel1(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    InitAudioDevice();
    ball = Ball("../assets/a.png");
    enemigo = Enemy();
    hitbox = Hitbox();
    ball.setPosition({90,160});
    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();

    LoadMap("../Level1.json", 0, floor);
    LoadMap("../Level1.json", 1, saferoom);
    LoadMap("../Level1.json", 2, wall);

    miniMapTexture = LoadTexture("../assets/Level1.png");
    levelMusic = LoadMusicStream("../assets/lvl1_music.mp3");

    PlayMusicStream(levelMusic);
}

void Nivel1::Update() {
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    if (isShiftPressed) {
        speed *= 2.0f;
    }

    if (IsKeyDown(KEY_W))
        deltaY -= speed;
    if (IsKeyDown(KEY_S))
        deltaY += speed;
    if (IsKeyDown(KEY_A))
        deltaX -= speed;
    if (IsKeyDown(KEY_D))
        deltaX += speed;

    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, floor, "stairs");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");
    UpdateMusicStream(levelMusic);


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

    //pathCopy = path;

    if (!ball.GetSafeRoom()&& !enemigo.IsEliminated()){
        enemigo.FollowBreadcrumb(ball.GetPosition());
    }

    if (GetTime() - lastCollisionDetectionTime >= 2.0) {
        collisionDetected = false; // Restablece la bandera de colisión
    }
    if(enemigo.GetCollisionWithHitbox(hitbox)){
        enemigo.setPosition({-1000,1000});
        enemigo.SetEliminated(true);

        collisionDetected = true;

        lastCollisionDetectionTime = GetTime();
    }
    float distance = Vector2Distance(ball.GetPosition(),enemigo.GetPosition());
    if(distance<ball.GetRadius() + 15){
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

void Nivel1::ResetLevel() {
    ball.setPosition({90,160});

    enemigo.setPosition({100,300});

    ball.ResetLives();

    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();
}
void Nivel1::Draw() {
    BeginMode2D(camera);
    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);

    ball.Draw();
    if(!enemigo.IsEliminated()){
        enemigo.Draw();
    }


    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    DrawMiniMap();
    EndMode2D();
}


void Nivel1::DrawAStar(Stack<Vector2> path) {
    // Calcula el desplazamiento necesario para centrar los círculos en cada celd
    float offsetX = (TILE_SIZE - 6) / 2.0f; // 5 es el radio del círculo
    float offsetY = (TILE_SIZE - 6) / 2.0f;

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
}

//Holam