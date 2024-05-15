#include "Jarrones.h"
#include "raymath.h"
#include "raylib.h"

 int sheetw = 31;
 int sheeth = 20;
 int framespero = 2;
 int framesperco = 1;

 const float framewidth = sheetw/ framespero;
 const float frameheight = sheeth / framesperco;

 Jarrones::Jarrones() {
    position = {1040,620};
    collisionbox = {0,0,16};
    spritesheet = LoadTexture("/home/gabriel/Documents/SeldaProject/Selda/assets/jarrones.png");

    framecounter = 0;
    currentframe = 0;
    framespeed = 8;
    time_for_crums = 0;

 }

 void Jarrones::Draw() const {
     DrawTextureRec(spritesheet,sourcerec,{position.x - framewidth / 2, position.y - frameheight / 2},WHITE);
 }

 void Jarrones::Anim(){
     sourcerec.y = frameheight*1 + frameheight*2 ;
     UpdateAnimation();
 }

 void Jarrones::UpdateAnimation() {
     framecounter++;
     if (framecounter >= framespeed) {
         framecounter = 0;
         currentframe++;
         if (currentframe >= framespero * framesperco) {
             currentframe = 0;
         }
         // Calcular la fila y columna actual
         int currentrow = currentframe / framespero;
         int currentcolumn = currentframe % framespero;
         // Calcular la posición del sprite en el spritesheet
         sourcerec.x = currentcolumn * framewidth;
         sourcerec.y = currentrow * frameheight;
     }
 }


Vector2 Jarrones::GetPosition() const {
    return position;
}

void Jarrones::SetPosition(Vector2 newPosition) {
    position = newPosition;
}


