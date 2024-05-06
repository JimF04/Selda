//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel2.h"


Nivel2::Nivel2(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    enemigo = Enemy();
    ball.setPosition({100,410});


    LoadMap("../Level2.json", 0,floor);

}

void Nivel2::Update() {
    int deltaX = 0;
    int deltaY = 0;

    if (IsKeyDown(KEY_W))
        deltaY -= 1;
    if (IsKeyDown(KEY_S))
        deltaY += 1;
    if (IsKeyDown(KEY_A))
        deltaX -= 1;
    if (IsKeyDown(KEY_D))
        deltaX += 1;

    LayerCollision(deltaX, deltaY, wall, "wall");
}

void Nivel2::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    ball.Draw();
    enemigo.Draw();

    EndMode2D();
}