//
// Created by ahenao on 21/05/24.
//

#include "Boss.h"


void Boss::Draw() const
{
    DrawTextureRec(spritesheet, sourceRec, {position.x-20,position.y-20}, WHITE);
}


void Boss::SpawnSlime(Vector<Slime> &slimes){
    Slime nuevoSlime;
    slimes.push_back(nuevoSlime);
    LOG(INFO) << "Slime spawned";

}

int Boss::GetBossLives() {
    return BossLives;
}

void Boss::DecreaseBossLives(){
    BossLives --;
}

void Boss::IncreaseBossLives(int vidas){
    if (BossLives + vidas > 15) {
        BossLives = 15;
    } else {
        BossLives += vidas;
    }
}


void Boss::Ataque(){
    sourceRec.y = 48*6;
    UpdateAnimation();
}


