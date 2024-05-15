//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel2.h"
#include "raymath.h"
#include "raylib.h"


Nivel2::Nivel2(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight), vidas(5,5){
    // Iniciar clases
    ball = Ball();
    enemigo = Enemy();
    ball.setPosition({90,416});

    LoadMap("../Level2.json", 0, floor);
    LoadMap("../Level2.json", 1, saferoom);
    LoadMap("../Level2.json", 2, wall);
    miniMapTexture = LoadTexture("../assets/Level2.png");
    levelMusic = LoadMusicStream("../assets/lvl2_music.mp3");
    PlayMusicStream(levelMusic);

}

void Nivel2::ResetLevel() {
    ball.setPosition({90, 160});

    enemigo.setPosition({100, 300});

    vidas.ResetLives();

    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();
}
void Nivel2::Update() {
    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;

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
    if (IsKeyDown(KEY_L))
        ball.Atacar();


    if(IsKeyDown(KEY_K) && !keyKPressed) {
        ball.Defender();
        keyKPressed = true;
    }


    if (IsKeyUp(KEY_K)) {
        keyKPressed = false;
    }


    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, floor, "stairs");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");
    UpdateMusicStream(levelMusic);

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
            vidas.DecreaseLife();
            if(!vidas.IsAlive()){
                ResetLevel();
            }
            collisionDetected = true;
            lastCollisionDetectionTime = GetTime();
        }
    }
}

void Nivel2::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    DrawMiniMap();

    ball.Draw();
    enemigo.Draw();

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }


    EndMode2D();
}