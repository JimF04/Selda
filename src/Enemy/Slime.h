//
// Created by ahenao on 22/05/24.
//

#ifndef SELDA_SLIME_H
#define SELDA_SLIME_H
#include "Enemy.h"


class Slime : public Enemy {
public:
    Slime() {
        spritesheet = LoadTexture("../assets/enemyPack/chara_slime.png");
    }

};
#endif //SELDA_SLIME_H

