#include "raymath.h"
#include "Cofres.h"
#include "raylib.h"
#include "../Niveles/Nivel1.h"


int sheetwidth = 97;
int sheetheight = 129;
int framesrow = 3;
int framescolumn = 4;

const float framewidth = sheetwidth / framesrow;
const float frameheight = sheetheight / framescolumn;

Cofres::Cofres(){

    collisionBox = {0,0,16};
    spritesheet = LoadTexture("../assets/cofre.png");
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
    sourcerec.y = frameheight*1 + frameheight*2 + frameheight*3+frameheight*5;
    UpdateAnimation();
}

void Cofres::UpdateAnimation() {
    framecounter++;
    if (framecounter >= framespeed) {
        framecounter = 0;
        currentframe++;
        if (currentframe >= framesrow * framescolumn) {
            currentframe = 0;
        }
        // Calcular la fila y columna actual
        int currentrow = currentframe / framesrow;
        int currentcolumn = currentframe % framesrow;
        // Calcular la posición del sprite en el spritesheet
        sourcerec.x = currentcolumn * framewidth;
        sourcerec.y = currentrow * frameheight;
    }
}

Vector2 Cofres::GetPosition() const {
    return position;
}

void Cofres::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

void Cofres::DrawCounter(Camera2D camera2D) const {
    Vector2 drawPosition = {-115 + camera2D.target.x, -60 + camera2D.target.y};
    //DrawText(FormatText("x: %d", nivelPtr->contadorCofres), drawPosition.x, drawPosition.y, 10, WHITE);
}



