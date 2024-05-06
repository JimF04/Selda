//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel5.h"



Nivel5::Nivel5(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    ball.setPosition({ 592, 704 });

    LoadMap("../BossLevel.json", 0, floor);
    LoadMap("../BossLevel.json", 1, saferoom);
    LoadMap("../BossLevel.json", 2, wall);
    miniMapTexture = LoadTexture("../assets/BossLevel.png");
}

void Nivel5::Update() {
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

    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");
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