#include <raylib.h>
#include "Mapa.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Control de bola con teclas WASD");
    SetTargetFPS(60);

    Mapa mapa(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        mapa.Update();
        mapa.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
