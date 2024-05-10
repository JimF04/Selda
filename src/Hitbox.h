//
// Created by gabri on 5/10/2024.
//

#ifndef SELDA_HITBOX_H
#define SELDA_HITBOX_H



#ifndef HITBOX_H
#define HITBOX_H

#include "raylib.h"

class Hitbox {
public:
    Hitbox();
    Hitbox(Vector2 position, int width, int height);
    void Draw(Color color) const;
    bool CheckCollision(Vector2 point) const;
    bool CheckCollision(const Hitbox& other) const;
    void SetRect(Rectangle newRect);
    Rectangle GetRect() const;

private:
    Rectangle rect;
};

#endif // HITBOX_H



#endif //SELDA_HITBOX_H
