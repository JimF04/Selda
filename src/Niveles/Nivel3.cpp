//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel3.h"
#include "../ball.h"
#include "raymath.h"


Nivel3::Nivel3(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    ball.setPosition({ 368, 80 });
    enemigo = Enemy();
    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();

    LoadMap("../Level3.json", 0, floor);
    LoadMap("../Level3.json", 1, saferoom);
    LoadMap("../Level3.json", 2, wall);
    LoadMap("../Level3.json", 3, traps);
    LoadMap("../Level3.json", 4, falsefloor);

    miniMapTexture = LoadTexture("../assets/Level3.png");
    levelMusic = LoadMusicStream("../assets/lvl3_music.mp3");
    PlayMusicStream(levelMusic);
}

void Nivel3::Update() {
    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;


    if (ball.lives <=0){
        Nivel::ResetLevel(368,80);

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


    if (!collisionDetected && GetTime() - lastCollisionDetectionTime >= 2.0) {
        if (ball.CheckCollisionWithEnemy(enemigo)) {


            collisionDetected = true;
            lastCollisionDetectionTime = GetTime();
        }
    }
}

void Nivel3::ResetLevel() {
    ball.setPosition({90, 160});

    enemigo.setPosition({100, 300});



    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();
}
void Nivel3::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(traps, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(falsefloor, 25, TEXTURE_TILEMAP);

    //=============Objetos================
    for(const auto& cofre:cofres){
        cofre.Draw();
    }
    DrawChestCounter();

    DrawMiniMap();
    ball.Draw();
    ball.DrawHearts(camera);

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    EndMode2D();
}