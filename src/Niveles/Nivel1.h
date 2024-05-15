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
#include "../Lives/Vidas.h"
#include "../Objects/Cofres.h"

class Nivel1 : public Nivel {
public:
    Nivel1(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
    Texture2D image;
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
    bool personaje_visto;

    int contadorCofres = 0;


    void DrawCounter();

private:
    Enemy enemigo;
    Enemy enemigo2;
    std::vector<Enemy> enemigos;
    Cofres cofre;
    std::vector<Cofres>cofres;

    void DrawAStar(Stack<Vector2> path);
    bool collisionDetected;
    double lastCollisionDetectionTime;
    Hitbox hitbox;
    Vidas vidas;

};



#endif //SELDA_NIVEL1_H
