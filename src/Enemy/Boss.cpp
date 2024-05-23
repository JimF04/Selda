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
    std::cout<<"Se creo un slime";

}



