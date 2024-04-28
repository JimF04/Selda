#ifndef BALL_H
#define BALL_H

#include <raylib.h>

class Ball
{
public:
    Ball();
    void Draw() const;
    void Move(int deltaX, int deltaY); // Declaración del método Move
    Vector2 GetPosition() const;
    int GetRadius() const;
private:
    Vector2 position;
    int radius;
    Color color;
};

#endif // BALL_H