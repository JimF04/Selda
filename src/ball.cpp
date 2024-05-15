#include <iostream>
#include "ball.h"
const int FRAME_WIDTH = 48;
const int FRAME_HEIGHT = 48;


Ball::Ball():vidas(5,5)
{
    position = {400, 300};

    collisionBox = {0, 0, 16, 16};

    radius = 8;

    crums;
    spritesheet = LoadTexture("../assets/chara_hero.png");

    sourceRec = {0, 0, FRAME_WIDTH, FRAME_HEIGHT};

    frameCounter = 0;

    currentFrame = 0;

    frameSpeed = 11;

    time_for_crums = 0;




}

void Ball::Draw() const
{
//    DrawCircleV(position, radius, color);


    // Dibujar el sprite
    DrawTextureRec(spritesheet, sourceRec, {position.x - FRAME_WIDTH / 2, position.y - FRAME_HEIGHT / 2}, WHITE);

}

void Ball::Move(int deltaX, int deltaY)
{
    position.x += deltaX;
    position.y += deltaY;

    // Determine which animation to play based on movement
    if (deltaX > 0) {
        // Moving right
        sourceRec.y = FRAME_HEIGHT * 3; // Row 4: Walk sideways
        // Reset any previous flips
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (deltaX < 0) {
        // Moving left
        sourceRec.y = FRAME_HEIGHT * 3; // Row 4: Walk sideways
        // Flip the sprite horizontally
        sourceRec.width = -FRAME_WIDTH; // Invert the width
    } else if (deltaY > 0) {
        // Moving down
        sourceRec.y = FRAME_HEIGHT * 2; // Row 3: Walk forward
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (deltaY < 0) {
        // Moving up
        sourceRec.y = FRAME_HEIGHT * 4; // Row 3: Walk forward
        sourceRec.width = FRAME_WIDTH; // Reset the width
    } else if (!IsKeyDown(KEY_L) && !IsKeyDown(KEY_K)) {
        // No movement, idle animation
        sourceRec.y = 0; // Row 1: Idle
        sourceRec.width = FRAME_WIDTH; // Reset the width
    }

    // Update the animation
    UpdateAnimation();

    GetCrumbs();
}





int Ball::GetRadius() const
{
    return radius;
}

    Vector2 Ball::GetPosition() const
    {
        return position;
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

void Ball::Defender(){
    std::cout<<"defendiendo"<<std::endl;
    sourceRec.y = FRAME_HEIGHT *1;
}

void Ball::Dano(){
    sourceRec.y = FRAME_HEIGHT *9;
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
    void Ball::setPosition(Vector2 pos)
    {
        position = pos;


    }

    bool Ball::CheckCollisionWithEnemy(const Enemy &enemy) const {
        float distance = Vector2Distance(position, enemy.GetPosition());
        return distance < radius + enemy.GetRadius();


    }

    bool Ball::GetSafeRoom()
    {
        return safeRoom;
    }



    void Ball::DecreaseLives() {
    lives--;
}
int Ball::GetRemainingLives() const {
    return vidas.GetLives();
}
