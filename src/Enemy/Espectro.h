//
// Created by jimmy on 18/05/24.
//

#ifndef SELDA_ESPECTRO_H
#define SELDA_ESPECTRO_H

#include "Enemy.h"

using namespace std;

class Espectro : public Enemy
{
public:
    Espectro() : Enemy(), type("default") {}
    Espectro(const string& type);
    void setRoute(queue<Vector2> route);
    queue<Vector2> getRoute();
    string type;


    void LaunchFireball() {
        FireBall fireball(position, "enemigo");
        if (lastFireballTime >= fireballCooldown) {
            Vector2 fireballVelocity = {0, 0};

            // Determinamos la dirección de la bola de fuego según la dirección del jugador
            switch (currentDirection) {
                case RIGHT:
                    fireballVelocity.x = 1.5f; // Aumentamos la posición en 1 en el eje x
                    break;
                case LEFT:
                    fireballVelocity.x = -1.5f; // Reducimos la posición en 1 en el eje x
                    break;
                case DOWN:
                    fireballVelocity.y = 1.5f; // Aumentamos la posición en 1 en el eje y
                    break;
                case UP:
                    fireballVelocity.y = -1.5f; // Reducimos la posición en 1 en el eje y
                    break;
                case IDLE:
                    fireballVelocity.x = 1.5f;
                    break;
                default:
                    // No cambiamos la posición si la dirección no es válida
                    break;
            }

            fireball.SetVelocity(fireballVelocity);

            activeFireballs.push_back(fireball);

            lastFireballTime = 0.0f;
        }
    }


    void UpdateFireballs() {

        // Actualizamos todas las bolas de fuego activas
        for (size_t i = 0; i < activeFireballs.size(); ++i) {
            activeFireballs[i].UpdatePosition(); // Actualizamos la posición de la bola de fuego
            activeFireballs[i].UpdateAnimation(); // Actualizamos la animación de la bola de fuego

            float distanciaf = Vector2Distance(activeFireballs[i].GetPosition(), ball.GetPosition());

//            if(distanciaf < ball.GetRadius() + 10) {
//                ball.setPosition({1000,-1000});
//                cout << "kjhilevuiwbevujibwujivbwikujbeviwbvicwbievbweiuvbkjdbshjkbejkcvbsiuebvjksbdhjke" << endl;
//            }


            // Verificamos la distancia recorrida por la bola de fuego
            if (Vector2Distance(activeFireballs[i].GetPosition(), position) > maxFireballDistance * 16) {
                // Si la distancia es mayor que la distancia máxima permitida, eliminamos la bola de fuego
                activeFireballs.erase(activeFireballs.begin() + i);
                // Decrementamos el índice para evitar omitir el siguiente elemento después de borrar uno
                --i;
            }

            // Colisiones con el jugador

//            Vector2 firePos = activeFireballs[i].GetPosition();
//            Vector2 playerPos = ball.GetPosition();


        }
        lastFireballTime += GetFrameTime();






    }

    void DrawFireballs() const {
        // Dibujamos todas las bolas de fuego activas
        for (size_t i = 0; i < activeFireballs.size(); ++i) {
            activeFireballs[i].Draw();
        }
    }


private:

    queue<Vector2> route;
    bool defaultRoute = true;

    std::vector<FireBall> activeFireballs;

    int maxFireballDistance = 3;
    float lastFireballTime;
    float fireballCooldown = 1.5f;

    Ball ball;

};


#endif //SELDA_ESPECTRO_H
