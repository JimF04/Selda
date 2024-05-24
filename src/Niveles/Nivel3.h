//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL3_H
#define SELDA_NIVEL3_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../ball.h"
#include "../Enemy/Enemy.h"
#include "../Nivel.h"


class Nivel3 : public Nivel {
public:
    Nivel3(int screenWidth, int screenHeight,int puntuacionInicial, int cofreInicial);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
    float keyKReleaseTime;
    Vector<Espectro> espectros;
    Vector<Ojo_Espectral> ojos_espectrales;
    Vector<Chocobos> chocobos;
    void ResetLevel();

    virtual bool CheckWinCondition() override {
        if (onstairs){
            winCondition = true;
        }
        else {
            winCondition= false;
        }
        return winCondition;
    }

private:
    bool collisionDetected;
    double lastCollisionDetectionTime;

    Vector<Cofres> cofres;

};


#endif //SELDA_NIVEL3_H
