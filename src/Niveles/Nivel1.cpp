//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel1.h"


Stack<Vector2> path;
Stack<Vector2> pathCopy;



Nivel1::Nivel1(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    enemigo = Enemy();
    ball.setPosition({150,150});

    LoadMap("../Level1.json", 0, floor);
    LoadMap("../Level1.json", 1, saferoom);
    LoadMap("../Level1.json", 2, wall);

}

void Nivel1::Update() {
    int deltaX = 0;
    int deltaY = 0;

    if (IsKeyDown(KEY_W))
        deltaY -= 2;
    if (IsKeyDown(KEY_S))
        deltaY += 2;
    if (IsKeyDown(KEY_A))
        deltaX -= 2;
    if (IsKeyDown(KEY_D))
        deltaX += 2;

    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");

    // Convertir las coordenadas de la bola a las coordenadas de la matriz
    int ball_x_grid = static_cast<int>( ball.GetPosition().x / TILE_SIZE);
    int ball_y_grid = static_cast<int>( ball.GetPosition().y / TILE_SIZE);

    int enemy_x_grid = static_cast<int>( enemigo.GetPosition().x / TILE_SIZE);
    int enemy_y_grid = static_cast<int>( enemigo.GetPosition().y / TILE_SIZE);


     //Crear una instancia de AStar y encontrar el camino
    AStar astar(wall1);
    path = astar.findPath(enemy_x_grid,enemy_y_grid,ball_x_grid,ball_y_grid);

    path.pop(); // Elimina la posición actual del enemigo
    //astar.printPath(path);

    //pathCopy = path;

    if (!ball.GetSafeRoom()){
        enemigo.FollowBreadcrumb(ball.GetPosition());
    }

}

void Nivel1::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor1, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom1, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall1, 25, TEXTURE_TILEMAP);

    ball.Draw();
    enemigo.Draw();

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    DrawMiniMap("../assets/Level1.png");

    EndMode2D();
}


void Nivel1::DrawAStar(Stack<Vector2> path) {
    // Calcula el desplazamiento necesario para centrar los círculos en cada celda
    float offsetX = (TILE_SIZE - 6) / 2.0f; // 5 es el radio del círculo
    float offsetY = (TILE_SIZE - 6) / 2.0f;

    // Dibujar círculos verdes en cada posición del camino encontrado
    while (!path.empty()) {
        Vector2 point = path.top();
        path.pop();

        // Convertir las coordenadas de la matriz a las coordenadas del mundo
        float worldX = static_cast<float>(point.x * TILE_SIZE + offsetX);
        float worldY = static_cast<float>(point.y * TILE_SIZE + offsetY);

        // Dibujar un círculo verde en la posición del mundo
        DrawCircle(worldX, worldY, 5, GREEN);
    }
}