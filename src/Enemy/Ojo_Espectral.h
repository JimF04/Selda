//
// Created by jimmy on 18/05/24.
//

#ifndef SELDA_OJO_ESPECTRAL_H
#define SELDA_OJO_ESPECTRAL_H


#include "Enemy.h"

class Ojo_Espectral : public Enemy{
public:
    Ojo_Espectral(){
        spritesheet = LoadTexture("../assets/enemyPack/Ojo_Espectral.png");
    };

};


#endif //SELDA_OJO_ESPECTRAL_H
