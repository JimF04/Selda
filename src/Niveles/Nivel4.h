//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL4_H
#define SELDA_NIVEL4_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../Ball.h"
#include "../Enemy/Enemy.h"
#include "../Nivel.h"

class Nivel4 : public Nivel {
public:
    Nivel4(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;

    virtual bool CheckWinCondition() override {
        return winCondition;
    }

private:
    Ball ball;

};


#endif //SELDA_NIVEL4_H
