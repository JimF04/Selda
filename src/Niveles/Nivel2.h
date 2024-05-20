#ifndef SELDA_NIVEL2_H
#define SELDA_NIVEL2_H

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../ball.h"
#include "../Enemy/Enemy.h"
#include "../Nivel.h"
#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../ball.h"
#include "../Nivel.h"
#include "../Algoritmos/AStar.h"
#include "../DataStructures/Stack.h"
#include "../Lives/Vidas.h"

class Nivel2 : public Nivel {
public:
    Nivel2(int screenWidth, int screenHeight);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
    void ResetLevel();

    // Declaración de la función para dibujar las sombras
    void DrawShadowMap();

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
    bool collisionDetected;
    double lastCollisionDetectionTime;
    Vidas vidas;

    Stack<Vector2> path2;

    std::vector<Enemy> enemigos2;
};


#endif //SELDA_NIVEL2_H
