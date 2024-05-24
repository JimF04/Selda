//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel4.h"
#include "raylib.h"
#include "raymath.h"

Nivel4::Nivel4(int screenWidth, int screenHeight,int puntuacionInicial) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    contadorPuntuacion = puntuacionInicial;
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




    for(int i = 0;i<3;i++){
        cofres.push_back(Cofres());
    }
    cofres[0].setPosition({24,5});
    cofres[1].setPosition({72,12});
    cofres[2].setPosition({45,26});



    for(int i = 0; i < 3;i++){
        jarrones.push_back(Jarrones());
    }

    jarrones[0].setPosition({23,23});
    jarrones[1].setPosition({72,29});
    jarrones[2].setPosition({13,6});



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

    if (IsKeyDown(KEY_K) ) {
        ball.IsDefending = true;
        ball.Defender();
        keyKPressed = true;
        keyKReleaseTime = -1;
    }

    if (IsKeyUp(KEY_K)) {
        if (keyKReleaseTime < 0) {
            keyKReleaseTime = GetTime();
        } else if (GetTime() - keyKReleaseTime >= 0.8f) {
            ball.IsDefending = false;
        }
    } else {
        keyKReleaseTime = -1;
    }


    LayerCollision(deltaX, deltaY, traps, "traps");
    LayerCollision(deltaX, deltaY, falsefloor, "falsefloor");
    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, floor, "stairs");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");

    UpdateMusicStream(levelMusic);


    //==============Update de los enemigos===============


    //==============Update de los objetos===============
    UpdateChests(cofres);
    UpdateJars(jarrones);

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

    //===========Objetos================
    for(auto& cofre:cofres){
        cofre.drawTile();
    }
    DrawChestCounter();

    for(auto& jarron:jarrones){
        jarron.drawTile();
    }

    DrawPuntuationCounter();


    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    EndMode2D();
}