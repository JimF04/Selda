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
#include "../Lives/Vidas.h"


class Nivel4 : public Nivel {
public:
    Nivel4(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
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
    Enemy enemigo;
    void DrawAStar(Stack<Vector2> path);
    bool collisionDetected;
    double lastCollisionDetectionTime;
    Vidas vidas;
};





#endif //SELDA_NIVEL4_H
