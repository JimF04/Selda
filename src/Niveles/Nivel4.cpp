//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel4.h"
#include "raylib.h"
#include "raymath.h"

Nivel4::Nivel4(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    ball.setPosition({ 112, 672 });

    LoadMap("../Level4.json", 0, floor);
    LoadMap("../Level4.json", 1, saferoom);
    LoadMap("../Level4.json", 2, wall);
    LoadMap("../Level4.json", 3, traps);
    LoadMap("../Level4.json", 4, falsefloor);

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    miniMapTexture = LoadTexture("../assets/Level4.png");
    levelMusic = LoadMusicStream("../assets/lvl4_music.mp3");
    PlayMusicStream(levelMusic);

}

void Nivel4::Update() {
    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;

    if (ball.lives <=0){
        Nivel::ResetLevel(112,672);

    }


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


    LayerCollision(deltaX, deltaY, traps, "traps");
    LayerCollision(deltaX, deltaY, falsefloor, "falsefloor");
    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, floor, "stairs");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");

    UpdateMusicStream(levelMusic);

    float distance = Vector2Distance(ball.GetPosition(),enemigo.GetPosition());
    if(distance<ball.GetRadius()){
        if(IsKeyDown(KEY_P)){
            enemigo.setPosition({-1000,1000});
        }
    }
    // Realiza la detección de colisiones solo si ha pasado suficiente tiempo y no se ha detectado una colisión recientemente
    if (!collisionDetected && GetTime() - lastCollisionDetectionTime >= 2.0) {
        if (ball.CheckCollisionWithEnemy(enemigo)) {



            // Establece la bandera de colisión en true
            collisionDetected = true;

            // Actualiza el tiempo de la última detección de colisiones
            lastCollisionDetectionTime = GetTime();
        }
    }
}


void Nivel4::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(traps, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(falsefloor, 25, TEXTURE_TILEMAP);
    DrawMiniMap();
    ball.Draw();
    ball.DrawHearts(camera);

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    EndMode2D();
}