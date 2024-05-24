#include <iostream>
#include "ball.h"
const int FRAME_WIDTH = 48;
const int FRAME_HEIGHT = 48;


Ball::Ball() {

    heartTexture = LoadTexture("../assets/heart.png");

    lives= 5;
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

    DrawTextureRec(spritesheet, sourceRec, {position.x - FRAME_WIDTH / 2, position.y - FRAME_HEIGHT / 2}, WHITE);

}

void Ball::Move(int deltaX, int deltaY)
{
    position.x += deltaX;
    position.y += deltaY;


    if (deltaX > 0) {
        currentDir = Player_RIGHT;
        sourceRec.y = FRAME_HEIGHT * 3;
        sourceRec.width = FRAME_WIDTH;
    } else if (deltaX < 0) {
        currentDir = Player_LEFT;
        sourceRec.y = FRAME_HEIGHT * 3;
        sourceRec.width = -FRAME_WIDTH;
    } else if (deltaY > 0) {
        currentDir = Player_DOWN;
        sourceRec.y = FRAME_HEIGHT * 2;
        sourceRec.width = FRAME_WIDTH;
    } else if (deltaY < 0) {
        currentDir = Player_UP;
        sourceRec.y = FRAME_HEIGHT * 4;
        sourceRec.width = FRAME_WIDTH;
    } else if (!IsKeyDown(KEY_L) && !IsKeyDown(KEY_K)) {
        currentDir = Player_IDLE;

        sourceRec.y = 0;
        sourceRec.width = FRAME_WIDTH;
    }

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
    sourceRec.y = FRAME_HEIGHT *6;
    UpdateAnimation();
}

void Ball::Defender(){
    sourceRec.y = FRAME_HEIGHT *1;
}

void Ball::Dano(){
    sourceRec.y = FRAME_HEIGHT *9;
    UpdateAnimation();


}


void Ball::UpdateAnimation()
{

    frameCounter++;
    if (frameCounter >= frameSpeed)
    {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame > 2)
        {
            currentFrame = 0;
        }

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


void Ball::DecreaseLives(int damageDealt) {
    lives -= damageDealt;
}
int Ball::GetLives() const {
    return lives;
}

void Ball::IncreaseLives() {
    if (lives<5)
     lives++;
}

int Ball::ResetLives() {
     lives=5;

}

void Ball::DrawHearts(Camera2D camera) const {
    const int heartSize = 15;

    Vector2 heartPosition = {position.x-117 , position.y-78};

    for (int i = 0; i < lives; ++i) {

        DrawTextureEx(heartTexture, heartPosition, 0.0f, static_cast<float>(heartSize) / heartTexture.width, WHITE);

        heartPosition.x += heartSize -5;
    }
}