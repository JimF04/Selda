#include "raylib.h"
#include "Mapa.h"
#include "Niveles/Nivel1.h"
#include "Niveles/Nivel2.h"
#include "Niveles/Nivel3.h"
#include "Niveles/Nivel4.h"
#include "Niveles/Nivel5.h"
#include <glog/logging.h>

int main(int argc, char* argv[]) {
    // Inicialización de Glog
    google::SetLogDestination(google::GLOG_INFO, "../logging/registro.log");
    google::SetLogDestination(google::GLOG_WARNING, "../logging/registro.log");
    google::SetLogDestination(google::GLOG_ERROR, "../logging/registro.log");
    google::SetLogDestination(google::GLOG_FATAL, "../logging/registro.log");


    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Inicio del juego";

    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Selda");
    SetTargetFPS(60);

    Nivel* nivelActual = new Nivel1(screenWidth, screenHeight);

    int nivelActualIndex = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();


        nivelActual->Update();
        nivelActual->Draw();



        if (nivelActual->CheckWinCondition()){
            delete nivelActual;

            nivelActualIndex++; // Avanzar al siguiente nivel
            if (nivelActualIndex >= 5){
                nivelActualIndex = 0;
            }

            switch (nivelActualIndex){
                case 0:
                    nivelActual = new Nivel1(screenWidth, screenHeight);
                    break;
                case 1:
                    nivelActual = new Nivel2(screenWidth, screenHeight);
                    break;
                case 2:
                    nivelActual = new Nivel3(screenWidth, screenHeight);
                    break;
                case 3:
                    nivelActual = new Nivel4(screenWidth, screenHeight);
                    break;
                case 4:
                    nivelActual = new Nivel5(screenWidth, screenHeight);
                    break;
            }

        }

        EndDrawing();
    }

    LOG(INFO) << "Fin de la aplicación";

    CloseWindow();

    return 0;
}