//
// Created by jimmy on 18/05/24.
//

#include "Espectro.h"

Espectro::Espectro(const string& type) : Enemy(), type(type){

    if (type == "gris"){
        spritesheet = LoadTexture("../assets/enemyPack/espectro_Gris.png");


    } else if(type == "rojo") {
        spritesheet = LoadTexture("../assets/enemyPack/espectro_Rojo.png");

    } else if (type == "azul"){
        spritesheet = LoadTexture("../assets/enemyPack/espectro_Azul.png");


    } else {
            LOG(FATAL) << "tipo de espectro no especificado";
    }

}

void Espectro::setRoute(queue<Vector2> newRoute) {
    route = newRoute;
}

queue<Vector2> Espectro::getRoute() {
    return route;
}

//void Espectro::Draw() const
//{
//    DrawTextureRec(spritesheet, sourceRec, {position.x-20,position.y-20}, WHITE);
//}

