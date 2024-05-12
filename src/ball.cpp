#include <iostream>
#include "ball.h"
const int FRAME_WIDTH = 48;
const int FRAME_HEIGHT = 48;


Ball::Ball()
{
    position = {400, 300};
    radius = 6;
    color = PINK;
    crums;
    spritesheet = LoadTexture("/home/jose/Selda/assets/chara_hero.png");

    sourceRec = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    frameCounter = 0;

    currentFrame = 0;

    frameSpeed = 8;

    time_for_crums = 0;




}

void Ball::Draw() const

{
    DrawCircleV(position, radius, color);
    //DrawTextureRec(spritesheet, sourceRec, position, WHITE);
}

void Ball::Move(int deltaX, int deltaY)
{
    time_for_crums +=1;
    position.x += deltaX;
    position.y += deltaY;

    // Determina qué animación reproducir según el movimiento
    if (deltaX > 0) {
        // Movimiento hacia la derecha
        sourceRec.y = FRAME_HEIGHT * 3; // Fila 4: Caminar de lado
    } else if (deltaX < 0) {
        // Movimiento hacia la izquierda
        sourceRec.y = FRAME_HEIGHT * 4; // Fila 5: Caminar hacia atrás
    } else if (deltaY > 0) {
        // Movimiento hacia abajo
        sourceRec.y = FRAME_HEIGHT * 2; // Fila 3: Caminar hacia adelante
    } else if (deltaY < 0) {
        // Movimiento hacia arriba
        sourceRec.y = FRAME_HEIGHT *4; // Fila 2: Caminar hacia adelante (reutilizamos la fila 3)
    } else {
        // No hay movimiento, animación de estar quieto
        sourceRec.y = 0; // Fila 1: Estar quieto
    }

    // Actualiza la animación
    UpdateAnimation();

    if(time_for_crums>10){
        GetCrumbs();
        time_for_crums =0;

    }





}

Vector2 Ball::GetPosition() const
{
    return position;
}



int Ball::GetRadius() const
{
    return radius;
}

void Ball::setPosition(Vector2 pos)
{
    position = pos;
}

bool Ball::GetSafeRoom()
{
    return safeRoom;
}

void Ball::SetSafeRoom(bool safe)
{
    safeRoom = safe;
}

void Ball::GetCrumbs(){

    crums=(GetPosition());

}


void Ball::Atacar(){
    std::cout<<"atacando"<<std::endl;
    sourceRec.y = FRAME_HEIGHT *6;
    UpdateAnimation();



}

void Ball::UpdateAnimation()
{
    // Actualiza el frame actual basado en el tiempo
    frameCounter++;
    if (frameCounter >= frameSpeed)
    {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame > 2) // Si excede el número de frames de la animación
        {
            currentFrame = 0; // Reiniciar la animación
        }
        // Actualizar el rectángulo fuente de la textura para el siguiente frame
        sourceRec.x = currentFrame * FRAME_WIDTH;
    }}