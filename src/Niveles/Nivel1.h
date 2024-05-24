//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL1_H
#define SELDA_NIVEL1_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../ball.h"
#include "../Enemy/Enemy.h"
#include "../Nivel.h"
#include "../Algoritmos/AStar.h"
#include "../DataStructures/Stack.h"
#include "../DataStructures/Vector.h"
#include "../Objects/Cofres.h"
#include "../Objects/Jarrones.h"

#include "../Enemy/Espectro.h"
#include "../Enemy/Ratones.h"
#include "../Enemy/Ojo_Espectral.h"
#include "../Enemy/Chocobos.h"

class Nivel1 : public Nivel {
public:
    Nivel1(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
    float keyKReleaseTime;
    Texture2D image;
    void ResetLevel();
    bool KeyQPressed = false;



    virtual bool CheckWinCondition() override {
        if (onstairs){
            winCondition = true;
        }
        else {
            winCondition= false;
        }
        return winCondition;
    }
    int puntuacionAcumulada = 0;


private:

    Vector<Espectro> espectros;
    Vector<Ratones> ratones;
    Vector<Ojo_Espectral> ojos_espectrales;
    Vector<Chocobos> chocobos;

    void DrawAStar(Stack<Vector2> path);




    Hitbox hitbox;
};



#endif //SELDA_NIVEL1_H
