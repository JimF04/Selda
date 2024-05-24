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


    void LaunchFireball(std::vector<FireBall>& activeFireballs) {

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


    void DrawFireballs(std::vector<FireBall>& activeFireballs) const {
        for (size_t i = 0; i < activeFireballs.size(); ++i) {
            activeFireballs[i].Draw();
        }
    }


    float lastFireballTime;
    float fireballCooldown = 10.5f;


private:

    queue<Vector2> route;
    bool defaultRoute = true;




};


#endif //SELDA_ESPECTRO_H
