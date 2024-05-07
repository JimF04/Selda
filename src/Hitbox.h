#ifndef HITBOX_H
#define HITBOX_H

#include "raylib.h"

class Hitbox {
public:
    Hitbox(Vector2 position, int radius);
    void SetPosition(Vector2 newPosition);
    void SetRadius(int newRadius);
    void Draw(Color color) const;

private:
    Vector2 position;
    int radius;
};

#endif // HITBOX_H
