//
// Created by jimmy on 18/05/24.
//

#include "Chocobos.h"

void Chocobos::bresenham(Vector2 playerPos, int layer[MAP_WIDTH][MAP_HEIGHT]) {
    int x1 = static_cast<int>(position.x) / 16;
    int y1 = static_cast<int>(position.y) / 16;
    int x0 = static_cast<int>(playerPos.x) / 16;
    int y0 = static_cast<int>(playerPos.y) / 16;


    distanceToPlayer = sqrt(pow(playerPos.x - position.x, 2) + pow(playerPos.y - position.y, 2));


    // Comprobación de la dirección del enemigo
    bool canSeePlayer = false;
    switch (currentDirection) {
        case RIGHT:
            if (x1 < x0 && abs(y1 - y0) <= (x0 - x1)) {
                canSeePlayer = true;
            }
            break;
        case LEFT:
            if (x1 > x0 && abs(y1 - y0) <= (x1 - x0)) {
                canSeePlayer = true;
            }
            break;
        case DOWN:
        case IDLE:
            if (y1 < y0 && abs(x1 - x0) <= (y0 - y1)) {
                canSeePlayer = true;
            }
            break;
        case UP:
            if (y1 > y0 && abs(x1 - x0) <= (y1 - y0)) {
                canSeePlayer = true;
            }
            break;
    }


    if (!canSeePlayer) {
        updateDir(0.02f);
        return;
    }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {

        if (layer[x0][y0] != 0) {
            return;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    float directionX = playerPos.x - position.x;
    float directionY = playerPos.y - position.y;


    float length = sqrt(directionX * directionX + directionY * directionY);
    directionX /= length;
    directionY /= length;

    Move(directionX * 1.2f, directionY * 1.2f);


    if(distanceToPlayer<20){
        Ataque();

    }
}