#include "raylib.h"
#include "Mapa.h"
#include "Niveles/Nivel1.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 608;

    InitWindow(screenWidth, screenHeight, "Control de bola con teclas WASD");
    SetTargetFPS(60);

    //Mapa mapa(screenWidth, screenHeight);
    Nivel1 nivel1(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {

        nivel1.Update();
        nivel1.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}