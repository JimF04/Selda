#include <raylib.h>
#include "ball.h"
#include "Wall.h"
#include "Enemy.h"



int main()
{
    
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 800;
    const int screenHeight = 600;

    Ball ball = Ball();

    InitWindow(screenWidth, screenHeight, "Control de bola con teclas WASD");
    SetTargetFPS(60);

    Wall pared = Wall();
    Enemy enemigo = Enemy();



  while (!WindowShouldClose())
{
    // Variables para almacenar el movimiento proyectado
    int deltaX = 0;
    int deltaY = 0;

    

    // Movimiento de la bola basado en las teclas WASD
    if (IsKeyDown(KEY_W))
        deltaY -= 5;
    if (IsKeyDown(KEY_S))
        deltaY += 5;
    if (IsKeyDown(KEY_A))
        deltaX -= 5;
    if (IsKeyDown(KEY_D))
        deltaX += 5;

    // Calculamos la posición proyectada de la bola
    Vector2 projectedPosition = {ball.GetPosition().x + deltaX, ball.GetPosition().y + deltaY};

    // Comprobamos si la posición proyectada colisiona con la pared
    Rectangle ballRect = {projectedPosition.x - ball.GetRadius(), projectedPosition.y - ball.GetRadius(), ball.GetRadius() * 2, ball.GetRadius() * 2};
    if (!CheckCollisionRecs(ballRect, pared.GetCollisionRect()))
    {
        // Movemos la bola solo si no hay colisión
        ball.Move(deltaX, deltaY);
    }

    enemigo.FollowBreadcrumb(ball.GetPosition());

    BeginDrawing();
    ClearBackground(darkGreen);
    ball.Draw();
    pared.Draw();
    enemigo.Draw();
    EndDrawing();
}

    CloseWindow();
    return 0;
}
