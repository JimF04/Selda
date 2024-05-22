//
// Created by ahenao on 21/05/24.
//

#ifndef SELDA_BOSS_H
#define SELDA_BOSS_H
#include "Enemy.h"

class Boss : public Enemy{
public:
    Boss(){
        spritesheet = LoadTexture("../assets/enemyPack/chara_slime.png");
    }

    virtual void Draw() const override;

};


#endif //SELDA_BOSS_H


