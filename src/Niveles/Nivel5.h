//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL5_H
#define SELDA_NIVEL5_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../ball.h"
#include "../Enemy/Enemy.h"
#include "../Nivel.h"
#include "../Enemy/Boss.h"



class Nivel5 : public Nivel {
public:
    Nivel5(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
    Boss boss;
    void ResetLevel();

    virtual bool CheckWinCondition() override {
        return winCondition;
    }

private:
    Enemy enemigo;
    void DrawAStar(Stack<Vector2> path);
    bool collisionDetected;
    double lastCollisionDetectionTime;

    Vector<Cofres> cofres;

};


#endif //SELDA_NIVEL5_H
