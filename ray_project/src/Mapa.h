#ifndef MAPA_H
#define MAPA_H

#include <raylib.h>
#include "ball.h"
#include "Wall.h"
#include "Enemy.h"

class Mapa {
public:
    Mapa(int screenWidth, int screenHeight);
    void Update();
    void Draw();

private:
    int screenWidth;
    int screenHeight;
    Color darkGreen;
    Ball ball;
    Wall pared;
    Enemy enemigo;
    Camera2D camera;
};

#endif // MAPA_H
