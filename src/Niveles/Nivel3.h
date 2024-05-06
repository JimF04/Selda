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
    Nivel3(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;

    virtual bool CheckWinCondition() override {
        return winCondition;
    }

private:


};


#endif //SELDA_NIVEL3_H
