#include "raylib.h"
#include "Mapa.h"
#include "Niveles/Nivel1.h"
#include "Niveles/Nivel2.h"
#include "Niveles/Nivel3.h"
#include "Niveles/Nivel4.h"
#include "Niveles/Nivel5.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 608;

    InitWindow(screenWidth, screenHeight, "Selda");
    SetTargetFPS(60);

    // Crear un arreglo de punteros a objetos de tipo Nivel
    const int numNiveles = 5;
    Nivel* niveles[numNiveles];

    // Crear instancias de los niveles y asignarlas al arreglo
    niveles[0] = new Nivel1(screenWidth, screenHeight);
    niveles[1] = new Nivel2(screenWidth, screenHeight);
    niveles[2] = new Nivel3(screenWidth, screenHeight);
    niveles[3] = new Nivel4(screenWidth, screenHeight);
    niveles[4] = new Nivel5(screenWidth, screenHeight);

    int nivelActualIndex = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Obtener el nivel actual del arreglo
        Nivel* nivelActual = niveles[nivelActualIndex];

        nivelActual->Update();
        nivelActual->Draw();

        // Verificar la condición de victoria
//        if (nivelActual->CheckWinCondition()){
//            nivelActualIndex++; // Avanzar al siguiente nivel
//        }

        if (IsKeyPressed(KEY_SPACE)){
            nivelActualIndex++; // Avanzar al siguiente nivel
            if (nivelActualIndex >= numNiveles){
                nivelActualIndex = 0;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}