//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL_H
#define SELDA_NIVEL_H


#include "Mapa.h"
#include "raylib.h"
#include "DataStructures/Stack.h"

class Nivel {
public:
    Nivel(int screenWidth, int screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
        camera = { 0 };
        camera.target = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
        camera.offset = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
        camera.rotation = 0.0f;
        camera.zoom = 3.0f;
    };

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool CheckWinCondition() = 0;

protected:
    // Variables comunes a todos los niveles
    int screenWidth;
    int screenHeight;
    Camera2D camera;
    Mapa mapa;
    bool winCondition = false;
};

#endif //SELDA_NIVEL_H
