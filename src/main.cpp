#include "raylib.h"
#include "Mapa.h"
#include "Niveles/Nivel1.h"
#include "Niveles/Nivel2.h"
#include "Niveles/Nivel3.h"
#include "Niveles/Nivel4.h"
#include "Niveles/Nivel5.h"
#include "Algoritmos/Genetico.h"
#include <glog/logging.h>
#include <fstream> // Incluir la biblioteca para la manipulación de archivos
#include <vector>  // Incluir la biblioteca para el uso de vectores

int main(int argc, char* argv[]) {
    // Inicialización de Glog
    google::SetLogDestination(google::GLOG_INFO, "../logging/registro.log");
    google::SetLogDestination(google::GLOG_WARNING, "../logging/registro.log");
    google::SetLogDestination(google::GLOG_ERROR, "../logging/registro.log");
    google::SetLogDestination(google::GLOG_FATAL, "../logging/registro.log");

    google::InitGoogleLogging(argv[0]);

    Genetico genetico;

    LOG(INFO) << "Inicio del juego";

    // Vector de alelos
    std::vector<Vector3> alelos;
    alelos.push_back(Vector3{1.0f, 5.0f, 1.0f});
    alelos.push_back(Vector3{2.0f, 1.0f, 2.0f});
    alelos.push_back(Vector3{1.0f, 4.0f, 3.0f});

    // Código para guardar alelos en un archivo de texto antes de iniciar el juego
    std::ofstream file("../assets/alelos.txt");
    if (file.is_open()) {
        for (const auto& alelo : alelos) {
            file << alelo.x << " " << alelo.y << " " << alelo.z << "\n";
        }
        file.close();
        LOG(INFO) << "Alelos guardados en assets/alelos.txt";
    } else {
        LOG(ERROR) << "No se pudo abrir el archivo para escribir los alelos.";
    }

    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Selda");
    SetTargetFPS(60);

    Nivel* nivelActual = new Nivel1(screenWidth, screenHeight);
    int nivelActualIndex = 0;

    int puntuacionAcumulada = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        nivelActual->Update();
        nivelActual->Draw();


        if (nivelActual->CheckWinCondition() || IsKeyPressed(KEY_RIGHT)){
            puntuacionAcumulada =100 + nivelActual->GetPuntuacion();


            if(nivelActualIndex == 0 || nivelActualIndex ==1){
                Vector<Espectro> resultados = nivelActual->Regresar_resultado();
                genetico.Producir(resultados);
            }


            delete nivelActual;

            nivelActualIndex++; // Avanzar al siguiente nivel
            if (nivelActualIndex >= 5){
                nivelActualIndex = 0;
                puntuacionAcumulada = 0;
            }

            switch (nivelActualIndex){
                case 0:
                    nivelActual = new Nivel1(screenWidth, screenHeight);
                    break;
                case 1:
                    nivelActual = new Nivel2(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
                case 2:
                    nivelActual = new Nivel3(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
                case 3:
                    nivelActual = new Nivel4(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
                case 4:
                    nivelActual = new Nivel5(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
            }

        } else if (IsKeyPressed(KEY_LEFT)){ // Solo para pruebas
            delete nivelActual;

            nivelActualIndex--; // Retroceder al nivel anterior
            if (nivelActualIndex < 0){
                nivelActualIndex = 5;
                puntuacionAcumulada = 0;
            }

            switch (nivelActualIndex){
                case 0:
                    nivelActual = new Nivel1(screenWidth, screenHeight);
                    break;
                case 1:
                    nivelActual = new Nivel2(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
                case 2:
                    nivelActual = new Nivel3(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
                case 3:
                    nivelActual = new Nivel4(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
                case 4:
                    nivelActual = new Nivel5(screenWidth, screenHeight,puntuacionAcumulada);
                    break;
            }
        }

        EndDrawing();
    }

    LOG(INFO) << "Fin de la aplicación";
    CloseWindow();

    return 0;
}
