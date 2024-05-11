//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel5.h"



Nivel5::Nivel5(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball("../assets/Level1.png");
    ball.setPosition({ 592, 704 });

    LoadMap("../BossLevel.json", 0, floor);
    LoadMap("../BossLevel.json", 1, saferoom);
    LoadMap("../BossLevel.json", 2, wall);
    miniMapTexture = LoadTexture("../assets/BossLevel.png");
    levelMusic = LoadMusicStream("../assets/boss_music.mp3");
    PlayMusicStream(levelMusic);
}

void Nivel5::Update() {
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
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");
    UpdateMusicStream(levelMusic);

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

void Nivel5::ResetLevel() {
    ball.setPosition({90, 160});

    enemigo.setPosition({100, 300});

    ball.ResetLives();

    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();
}


void Nivel5::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    DrawMiniMap();
    ball.Draw();


    EndMode2D();
}