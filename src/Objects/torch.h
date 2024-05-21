//
// Created by jimmy on 20/05/24.
//

#ifndef SELDA_TORCH_H
#define SELDA_TORCH_H

#include "Objetos.h"

class Torch : public Objetos {

public:
    Torch(){
        spritesheet = LoadTexture("../assets/enemyPack/tiles_dungeon_v1.1.png");
        tilepos = {18,0};
        size = 16;
    };

private:
};

#endif //SELDA_TORCH_H