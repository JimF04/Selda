//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL_H
#define SELDA_NIVEL_H


#include "Mapa.h"
#include "raylib.h"
#include "DataStructures/Stack.h"
#include "ball.h"

class Nivel {
public:
    Nivel(int screenWidth, int screenHeight);

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool CheckWinCondition() = 0;
    virtual void LoadMap(std::string mapJson, int layerIndex, int layer[MAP_WIDTH][MAP_HEIGHT]);
    virtual void LayerCollision(int deltaX, int deltaY, int layer[MAP_WIDTH][MAP_HEIGHT], std::string type);
    void DrawCenteredText(const char* text, int fontSize, Color color);
    void DrawMiniMap();
    Texture2D miniMapTexture;


protected:
    // Variables comunes a todos los niveles
    int screenWidth;
    int screenHeight;
    Camera2D camera;
    Mapa mapa;
    bool winCondition = false;
    int floor[MAP_WIDTH][MAP_HEIGHT];
    int wall[MAP_WIDTH][MAP_HEIGHT];
    int saferoom[MAP_WIDTH][MAP_HEIGHT];
    Ball ball;
    int stairs [4] = {158,159,183,184};

};

#endif //SELDA_NIVEL_H
