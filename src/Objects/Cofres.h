#ifndef SELDA_COFRES_H
#define SELDA_COFRES_H


#include "Objetos.h"
#include "raylib.h"
#include "raymath.h"

class Cofres : public Objetos{
public:
    Cofres(){
        collisionBox = {0,0,16};
        spritesheet = LoadTexture("../assets/enemyPack/tiles_dungeon_v1.1.png");
        tilepos = {16,14};
    };

    Vector4 collisionBox;
    bool abierto = false;

    virtual Vector2 getPosition() override {
        Vector2 Newpos = {pos.x * 16,pos.y * 16};
        return Newpos;
    };

    void UpdateAnimation(){
        tilepos = {16, 15};
    };

private:

};
#endif //SELDA_COFRES_H
