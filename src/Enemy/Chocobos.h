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

};


#endif //SELDA_CHOCOBOS_H
