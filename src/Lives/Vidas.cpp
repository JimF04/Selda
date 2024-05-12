#include "Vidas.h"

Vidas::Vidas(int initialLives) : lives(5),initialLives(5) {}

void Vidas::DecreaseLife() {
    if (lives > 0) {
        lives--;
    }
}

int Vidas::GetLives() const {
    return lives;
}

bool Vidas::IsAlive() const {
    return lives > 0;
}

void Vidas::ResetLives() {
    lives = initialLives; // Restablecemos las vidas al valor inicial
}
