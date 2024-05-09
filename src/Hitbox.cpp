#include "Hitbox.h"


Hitbox::Hitbox(Vector2 position, int radius) : position(position), radius(radius) {}

void Hitbox::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

void Hitbox::SetRadius(int newRadius) {
    radius = newRadius;
}

void Hitbox::Draw(Color color) const {
    // Calcular las coordenadas del rectángulo alrededor de la bola
    float x = position.x - radius;
    float y = position.y - radius;
    float width = radius * 2;
    float height = radius * 2;

    // Dibujar el rectángulo alrededor de la bola como hitbox
    DrawRectangleLines(x, y, width, height, color);
}

