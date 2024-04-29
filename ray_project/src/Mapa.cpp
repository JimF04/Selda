#include "Mapa.h"

Mapa::Mapa(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    darkGreen = Color{20, 160, 133, 255};

    ball = Ball();
    const int wallPosX = 500;
    const int wallPosY = 100;
    const int wallWidth = 50;
    const int wallHeight = 50;
    Vector2 wallPosition = { wallPosX, wallPosY };
    pared = Wall(wallPosition, wallWidth, wallHeight);
    enemigo = Enemy();

    camera = { 0 };
    camera.target = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Mapa::Update() {
    int deltaX = 0;
    int deltaY = 0;

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

    camera.target = ball.GetPosition();
}

void Mapa::Draw() {
    BeginMode2D(camera);

    ClearBackground(darkGreen);
    ball.Draw();
    pared.Draw();
    enemigo.Draw();

    EndMode2D();
}
