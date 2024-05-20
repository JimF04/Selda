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
#include "../Lives/Vidas.h"
#include "../Objects/Cofres.h"
#include "../Objects/Jarrones.h"

#include "../Enemy/Espectro.h"
#include "../Enemy/Ratones.h"
#include "../Enemy/Ojo_Espectral.h"

class Nivel1 : public Nivel {
public:
    Nivel1(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
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

    int contadorCofres = 0;

    void DrawCounter();


private:

    Vector<Espectro> espectros;
    queue<Vector2> route1;
    queue<Vector2> route2;
    queue<Vector2> route3;

    Vector<Ratones> ratones;
    Vector<Ojo_Espectral> ojos_espectrales;

    Cofres cofre;
    std::vector<Cofres> cofres;
    std::vector<Jarrones> jarrones;
    Jarrones jarron;
    void DrawAStar(Stack<Vector2> path);
    bool collisionDetected;
    double lastCollisionDetectionTime;
    Hitbox hitbox;



};



#endif //SELDA_NIVEL1_H
