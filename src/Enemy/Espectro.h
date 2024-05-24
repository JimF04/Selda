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
        FireBall fireball({position.x , position.y}, "enemigo");
        if (lastFireballTime >= fireballCooldown) {
            Vector2 fireballVelocity = {0, 0};

            // Determinamos la dirección de la bola de fuego según la dirección del jugador
            switch (currentDirection) {
                case RIGHT:
                    fireballVelocity.x = 0.5;
                    break;
                case LEFT:
                    fireballVelocity.x = -0.5f;
                    break;
                case DOWN:
                    fireballVelocity.y = 0.5f;
                    break;
                case UP:
                    fireballVelocity.y = -0.5f;
                    break;
                case IDLE:
                    fireballVelocity.x = 0.5f;
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


    void UpdateFireballs(Ball ball) {
        // Actualizamos todas las bolas de fuego activas

        for (size_t i = 0; i < activeFireballs.size(); ++i) {
            activeFireballs[i].UpdatePosition();
            activeFireballs[i].UpdateAnimation(); // Actualizamos la animación de la bola de fuego

            // Calculamos la distancia entre la bola de fuego y la bola principal
            float distanceToBall = Vector2Distance(activeFireballs[i].GetPosition(), ball.GetPosition());
//            cout << "Distancia entre bola de fuego y pelota: " << distanceToBall << endl;
//
//            cout << "Fuego x: " << activeFireballs[i].GetPosition().x << endl;
//            cout << "Fuego y: " << activeFireballs[i].GetPosition().y << endl;
//            cout << "Pelota x: " << ball.GetPosition().x << endl;
//            cout << "Pelota y: " << ball.GetPosition().y << endl;
             //Comprobamos si hay colisión
            if (distanceToBall < ball.GetRadius() + 15) {
                ball.DecreaseLives(51);
                cout << "Colisión detectada entre la bola de fuego y la pelota" << endl; // Imprimir un mensaje
            } else

                // Verificamos la distancia recorrida por la bola de fuego
            if (Vector2Distance(activeFireballs[i].GetPosition(), position) > maxFireballDistance * 16) {
                activeFireballs.erase(activeFireballs.begin() + i);
                --i;
            }
        }
        lastFireballTime += GetFrameTime();
    }


    void DrawFireballs() const {
        for (size_t i = 0; i < activeFireballs.size(); ++i) {
            activeFireballs[i].Draw();
        }
    }


private:

    queue<Vector2> route;
    bool defaultRoute = true;

    std::vector<FireBall> activeFireballs;

    int maxFireballDistance = 5;
    float lastFireballTime;
    float fireballCooldown = 1.5f;

};


#endif //SELDA_ESPECTRO_H
