#ifndef SELDA_FIREBALL_H
#define SELDA_FIREBALL_H

#include "raylib.h"
#include "../Mapa.h"
#include "../DataStructures/Vector.h"
#include "../ball.h"

using namespace std;

class FireBall{
public:
    FireBall(Vector2 position, string type) : position(position) {
        frameWidth = 16;
        frameHeight = 16;
        currentFrame = 0;
        totalFrames = 5;
        frameCounter = 0;
        frameSpeed = 8;
        sourceRec = {0, 17, static_cast<float>(frameWidth), static_cast<float>(frameHeight)};

        if (type == "player"){
            spritesheet = LoadTexture("../assets/effects/All_Fire_Bullet_Pixel_16x16_01.png");
        } else if (type == "enemigo"){
            spritesheet = LoadTexture("../assets/effects/All_Fire_Bullet_Pixel_16x16_00.png");
        }

    }

    void UpdateAnimation() {
        frameCounter++;

        if (frameCounter >= (60 / frameSpeed)) {
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > totalFrames - 1)
                currentFrame = 0;

            sourceRec.x = currentFrame * frameWidth;
        }
    }

    void Draw() const {
        DrawTextureRec(spritesheet, sourceRec, position, WHITE);
    }

    void SetVelocity(Vector2 newVelocity) {
        velocity = newVelocity;
    }

    Vector2 GetPosition() const {
        return position;
    }

    void SetPosition(Vector2 newPosition) {
        position = newPosition;
    }

    void UpdatePosition() {
        position.x += velocity.x;
        position.y += velocity.y;
    }

private:
    Vector2 position;
    Texture2D spritesheet;
    Rectangle sourceRec;
    int frameWidth;
    int frameHeight;
    int frameCounter;
    int currentFrame;
    int totalFrames;
    int frameSpeed;
    Vector2 velocity;
};

#endif // SELDA_FIREBALL_H
