#include <iostream>
#include "Jarrones.h"
#include "raymath.h"
#include "raylib.h"


int framesperow = 2;
int framespercolumn = 1;
 const float framewidth = 31.0f / 2.0f;
 const float frameheight =20.0f;

Jarrones::Jarrones() {
    position = {695, 200};
    collisionbox = {0, 0, 16};
    spriteshet = LoadTexture("/home/gabriel/Documents/SeldaProject/Selda/assets/jarrones.png");
    sourcerec = {0,0,framewidth,frameheight};

    // Verificar si la textura se cargó correctamente
    if (spriteshet.id == 0) {
        // Si el ID de la textura es cero, indica que la carga falló
        std::cerr << "Error al cargar la textura de jarrones." << std::endl;
    }else{
        std::cerr<<"correcto"<<std::endl;
    }

    framecounter = 0;
    currentframe = 0;
    framespeed = 8;
    time_for_crums = 0;
}


 void Jarrones::Draw() const {
     DrawTextureRec(spriteshet,sourcerec,{position.x - framewidth / 2, position.y - frameheight / 2},WHITE);
 }

 void Jarrones::Anim(){
     sourcerec.x = 0;
     sourcerec.y = 0;
     Updateanimation();
 }


void Jarrones::Updateanimation() {

        sourcerec.x = 200;
        sourcerec.y = 0; // Mantener la coordenada y en 0 ya que solo tienes una fila de frames
    }


Vector2 Jarrones::GetPosition() const {
    return position;
}

void Jarrones::SetPosition(Vector2 newPosition) {
    position = newPosition;
}


