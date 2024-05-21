#ifndef SELDA_JARRONES_H
#define SELDA_JARRONES_H
#include "Objetos.h"
#include "raylib.h"
#include "raymath.h"

class Jarrones : public Objetos{

public:
    Jarrones(){
        collisionBox = {0,0,16};
        spritesheet = LoadTexture("../assets/enemyPack/tiles_dungeon_v1.1.png");
        tilepos = {16,16};
    };

    Vector4 collisionBox;
    bool abierto = false;

    virtual Vector2 getPosition() override{
        Vector2 Newpos = {pos.x * 16,pos.y * 16};
        return Newpos;
    };

    void UpdateAnimation(){
        tilepos = {16, 17};
    };

private:
    Vector2 position;

};
#endif //SELDA_JARRONES_H
