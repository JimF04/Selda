//
// Created by jimmy on 18/05/24.
//

#include "Espectro.h"

Espectro::Espectro(const string& type) : Enemy(), type(type){

    if (type == "gris"){
        spritesheet = LoadTexture("../assets/chara_goblin.png");

    } else if(type == "rojo") {
        spritesheet = LoadTexture("../assets/chara_slime.png");

    } else {
            LOG(FATAL) << "tipo de espectro no especificado";
    }


}

//void Espectro::Draw() const
//{
//    DrawTextureRec(spritesheet, sourceRec, {position.x-20,position.y-20}, WHITE);
//}

