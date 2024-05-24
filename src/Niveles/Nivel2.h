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
#include "../Objects/torch.h"


class Nivel2 : public Nivel {
public:
    Nivel2(int screenWidth, int screenHeight,int puntuacionInicial);
    virtual void Update() override;
    virtual void Draw() override;
    Music levelMusic;
    void ResetLevel();
    void Draw_Fog();

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
    bool collisionDetected;
    double lastCollisionDetectionTime;

    Vector<Torch> torch;

    Vector<Espectro> espectroRojo;

    Vector<Cofres> cofres;

};


#endif //SELDA_NIVEL2_H
