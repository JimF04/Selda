//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL4_H
#define SELDA_NIVEL4_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../ball.h"
#include "../Enemy/Enemy.h"
#include "../Nivel.h"



class Nivel4 : public Nivel {
public:
    Nivel4(int screenWidth, int screenHeight,int puntuacionInicial);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
    float keyKReleaseTime;
    Vector<Espectro> azul;
    Vector<Espectro> rojo;
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

    Vector<Cofres> cofres;

};





#endif //SELDA_NIVEL4_H
