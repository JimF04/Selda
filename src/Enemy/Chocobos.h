//
// Created by jimmy on 18/05/24.
//

#ifndef SELDA_CHOCOBOS_H
#define SELDA_CHOCOBOS_H


#include "Enemy.h"

class Chocobos : public Enemy{
public:
    Chocobos(){
        spritesheet = LoadTexture("../assets/enemyPack/chocobo.png");
    };

    void bresenham(Vector2 playerPos, int layer[MAP_WIDTH][MAP_HEIGHT]);

private:


};


#endif //SELDA_CHOCOBOS_H
