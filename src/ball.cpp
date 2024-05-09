#include "ball.h"
#include "raylib.h"
#include "raymath.h"
#include "Hitbox.h" // Incluir el archivo de encabezado Hitbox.h

Ball::Ball() : hitbox({400, 300}, 20) // Inicializar hitbox con la posición y el radio predeterminados
{
    position = {400, 300};
    radius = 6;
    color = PINK;
    lives = 5;
}

int Ball::GetLives() const {
    return lives;
}

void Ball::DecreaseLives() {
    lives--;
}

void Ball::Draw() const
{
    // Dibujar la bola
    DrawCircleV(position, radius, color);
    // Dibujar el hitbox
    hitbox.Draw(GREEN);
}

void Ball::Move(int deltaX, int deltaY)
{
    position.x += deltaX;
    position.y += deltaY;
    // Actualizar la posición del hitbox cuando la bola se mueve
    hitbox.SetPosition(position);
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

    // Actualizar la posición del hitbox cuando se establece la posición de la bola
    hitbox.SetPosition(position);
}

bool Ball::CheckCollisionWithEnemy(const Enemy& enemy) const {
    float distance = Vector2Distance(position, enemy.GetPosition());
    return distance < radius + enemy.GetRadius();
}
