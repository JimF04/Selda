#include "Vidas.h"


const int DESIRED_WIDTH = 20;  // Ancho deseado de la textura
const int DESIRED_HEIGHT = 10; // Altura deseada de la textura

Vidas::Vidas(int initialLives,int totalHearts) : lives(5), initialLives(5),totalHearts(totalHearts),heartsLeft(totalHearts) {
    position = {-120,-60};
    Image image = LoadImage("C:\\SeldaProject\\Selda\\assets\\heartimage.png");
    if (image.data == nullptr) {
        TraceLog(LOG_WARNING, "Error al cargar la imagen de las vidas");
    } else {
        TraceLog(LOG_INFO, "Imagen de las vidas cargada correctamente");
        ImageResize(&image, DESIRED_WIDTH, DESIRED_HEIGHT); // Escalar la imagen al tamaño deseado
        spriteshit = LoadTextureFromImage(image);
        UnloadImage(image); // Descargar la imagen original después de escalarla
    }
    surceRec = {0,0,DESIRED_WIDTH,DESIRED_HEIGHT}; // Tamaño deseado del rectángulo fuente
}


void Vidas::DecreaseLife() {
    if (lives > 0) {
        lives--;
        heartsLeft--;
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
    heartsLeft = totalHearts;
}
void Vidas::Draw(Camera2D camera) const {
    for (int i = 0; i < heartsLeft; i++) {
        Vector2 drawPosition = {position.x + camera.target.x + i * (DESIRED_WIDTH + 5), position.y + camera.target.y};
        DrawTextureRec(spriteshit, surceRec, drawPosition, WHITE);
    }
}

