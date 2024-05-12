//
// Created by jimmy on 30/04/24.
//

#ifndef RAYLIB_TEMPLATE_BALL_H
#define RAYLIB_TEMPLATE_BALL_H

#include "raylib.h"
#include <vector>


class Ball
{
public:
    Ball();
    void Draw() const;
    void Move(int deltaX, int deltaY); // Declaración del método Move
    Vector2 GetPosition() const;
    int GetRadius() const;
    void setPosition(Vector2 pos);
    bool GetSafeRoom();
    void SetSafeRoom(bool safe);
    bool safeRoom;
    std::vector<Vector2> crums;
    void GetCrumbs();

    int frameCounter;
    int currentFrame;
    int frameSpeed;
    Texture2D spritesheet;
    Rectangle sourceRec;

private:
    Vector2 position;
    int radius;
    Color color;
};


#endif //RAYLIB_TEMPLATE_BALL_H
