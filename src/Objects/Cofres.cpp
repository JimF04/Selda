#include "raymath.h"
#include "Cofres.h"
#include "raylib.h"
int sheetwidth = 97;
int sheetheight = 129;
int framesperow = 3;
int framespercolumn = 4;

const float framewidth = sheetwidth / framesperow;
const float frameheight = sheetheight / framespercolumn;

Cofres::Cofres() {

    position = {400,300};
    collisionBox = {0,0,16};
    spritesheet = LoadTexture("/home/gabriel/Documents/SeldaProject/Selda/assets/Fantasy RPG (Toony) 32x32(1).png");
    sourcerec = {0,0,framewidth,frameheight};

    framecounter = 0;
    currentframe = 0;
    framespeed = 8;
    time_for_crums = 0;
}

void Cofres::Draw() const{
    DrawTextureRec(spritesheet,sourcerec,{position.x - framewidth / 2, position.y - frameheight / 2},WHITE);
}

void Cofres::Still(){
    sourcerec.y = frameheight*1 + frameheight*2 + frameheight*3;
}

void Cofres::UpdateAnimation(){
    framecounter++;
    if(framecounter>=framespeed){
        framecounter = 0;
        currentframe++;
        if(currentframe>2){
            currentframe = 0;
        }
        sourcerec.x = currentframe * framewidth;
    }
}
