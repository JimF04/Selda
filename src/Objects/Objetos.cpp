#include "Objetos.h"
#include "../Mapa.h"

Objetos::Objetos() {
}

void Objetos::drawTile() {

    int pos_x = pos.x;
    int pos_y = pos.y;

    int tile_x = tilepos.x;
    int tile_y = tilepos.y;

    Rectangle sourceRec = {(float)TILE_SIZE * tile_y, (float)TILE_SIZE * tile_x, (float)TILE_SIZE, (float)TILE_SIZE };
    Rectangle destRec = {(float)pos_x*16, (float)pos_y*16, (float)TILE_SIZE, (float)TILE_SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(spritesheet, sourceRec, destRec, origin, 0.0f, WHITE);
}

void Objetos::setSize(int newSize) {
    size = newSize;
}

int Objetos::getSize() {
    return size;
}

void Objetos::setPosition(Vector2 newPos) {
    pos = newPos;
}

Vector2 Objetos::getPosition() {
    return pos;
}

