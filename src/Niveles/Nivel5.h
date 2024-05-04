//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL5_H
#define SELDA_NIVEL5_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../Ball.h"
#include "../Enemy/Enemy.h"
#include "../Nivel.h"

class Nivel5 : public Nivel {
public:
    Nivel5(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;

    virtual bool CheckWinCondition() override {
        return winCondition;
    }

private:
    Ball ball;

};


#endif //SELDA_NIVEL5_H
