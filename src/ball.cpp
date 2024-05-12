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
    if (spritesheet.id <= 0)
    {
        std::cerr << "Error cargando la textura del spritesheet" << std::endl;
    }

    sourceRec = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    frameCounter = 0;

    currentFrame = 0;

    frameSpeed = 8;




}

void Ball::Draw() const
{
    DrawTextureRec(spritesheet, sourceRec, position, WHITE);
}

void Ball::Move(int deltaX, int deltaY)
{

    position.x += deltaX;
    position.y += deltaY;

    // Actualizar la animación
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
    }

    GetCrumbs();




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

    crums.push_back(GetPosition());



}