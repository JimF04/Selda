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

class Nivel1 : public Nivel {
public:
    Nivel1(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;
    void ResetLevel();

    virtual bool CheckWinCondition() override {
        return winCondition;
    }

private:
    Ball ball;
    Enemy enemigo;
    bool collisionDetected;
    double lastCollisionDetectionTime;
};



#endif //SELDA_NIVEL1_H
