//
// Created by gabri on 5/10/2024.
//


#include "Hitbox.h"

Hitbox::Hitbox() {
    rect = {0, 0, 0, 0}; // Inicializa el rectángulo con valores por defecto
}
Hitbox::Hitbox(Vector2 position, int width, int height) {
    // Ajustamos el tamaño del rectángulo del hitbox
    rect.x = position.x - width / 2;
    rect.y = position.y - height / 2;
    rect.width = width;
    rect.height = height;
}

void Hitbox::Draw(Color color) const {
    DrawRectangleLinesEx(rect, 1, color);
}

bool Hitbox::CheckCollision(Vector2 point) const {
    return CheckCollisionPointRec(point, rect);
}

bool Hitbox::CheckCollision(const Hitbox& other) const {
    return CheckCollisionRecs(rect, other.rect);
}


void Hitbox::SetRect(Rectangle newRect){
    rect = newRect;
}

Rectangle Hitbox::GetRect() const {
    return rect;
}

