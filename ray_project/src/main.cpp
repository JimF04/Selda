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

    // Caracteristicas de la camara
    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenWidth / 2, screenHeight / 2 }; // Centro de la pantalla como su centro 
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f; // Sin rotacion
    camera.zoom = 1.0f; // Sin zoom

    while (!WindowShouldClose())
    {
        // Update
        int deltaX = 0;
        int deltaY = 0;

        // Handle input
        if (IsKeyDown(KEY_W))
            deltaY -= 5;
        if (IsKeyDown(KEY_S))
            deltaY += 5;
        if (IsKeyDown(KEY_A))
            deltaX -= 5;
        if (IsKeyDown(KEY_D))
            deltaX += 5;

        Vector2 projectedPosition = { ball.GetPosition().x + deltaX, ball.GetPosition().y + deltaY };

        Rectangle ballRect = { projectedPosition.x - ball.GetRadius(), projectedPosition.y - ball.GetRadius(), ball.GetRadius() * 2, ball.GetRadius() * 2 };
        if (!CheckCollisionRecs(ballRect, pared.GetCollisionRect()))
        {
            ball.Move(deltaX, deltaY);
        }

        enemigo.FollowBreadcrumb(ball.GetPosition());

        
        camera.target = ball.GetPosition();// Siguiendo a la bola y su posicion

        BeginMode2D(camera);  // Inicio del dibujo de la camara

        
        ClearBackground(darkGreen);
        ball.Draw();
        pared.Draw();
        enemigo.Draw();

        EndMode2D(); // Fin del dibujo de la camara

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
