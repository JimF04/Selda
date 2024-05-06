//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel3.h"



Nivel3::Nivel3(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    ball.setPosition({ 100, 100 });

    //LoadMap("../Level3.json", 0, floor);
}

void Nivel3::Update() {
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
}


void Nivel3::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    ball.Draw();

    EndMode2D();
}