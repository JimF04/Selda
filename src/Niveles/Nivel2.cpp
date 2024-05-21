#include "Nivel2.h"
#include "raymath.h"
#include "raylib.h"

Nivel2::Nivel2(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight) {
    // Iniciar clases
    ball = Ball();
    enemigo = Enemy();
    ball.setPosition({90, 416});


    LoadMap("../Level2.json", 0, floor);
    LoadMap("../Level2.json", 1, saferoom);
    LoadMap("../Level2.json", 2, wall);
    miniMapTexture = LoadTexture("../assets/Level2.png");
    levelMusic = LoadMusicStream("../assets/lvl2_music.mp3");
    PlayMusicStream(levelMusic);
}

void Nivel2::ResetLevel() {
    ball.setPosition({90, 160});

    enemigo.setPosition({100, 300});



    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();
}

void Nivel2::Update() {
    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;

    if (isShiftPressed) {
        speed *= 2.0f;
    }

    if (IsKeyDown(KEY_W))
        deltaY -= speed;
    if (IsKeyDown(KEY_S))
        deltaY += speed;
    if (IsKeyDown(KEY_A))
        deltaX -= speed;
    if (IsKeyDown(KEY_D))
        deltaX += speed;
    if (IsKeyDown(KEY_L))
        ball.Atacar();


    if(IsKeyDown(KEY_K) && !keyKPressed) {
        ball.Defender();
        keyKPressed = true;
    }


    if (IsKeyUp(KEY_K)) {
        keyKPressed = false;
    }

    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, floor, "stairs");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");
    UpdateMusicStream(levelMusic);

    if (GetTime() - lastCollisionDetectionTime >= 2.0) {
        collisionDetected = false; // Restablece la bandera de colisión
    }
    float distance = Vector2Distance(ball.GetPosition(), enemigo.GetPosition());
    if (distance < ball.GetRadius()) {
        if (IsKeyDown(KEY_P)) {
            enemigo.setPosition({-1000, 1000});
        }
    }
    // Realiza la detección de colisiones solo si ha pasado suficiente tiempo y no se ha detectado una colisión recientemente
    if (!collisionDetected && GetTime() - lastCollisionDetectionTime >= 2.0) {
        if (ball.CheckCollisionWithEnemy(enemigo)) {


            collisionDetected = true;
            lastCollisionDetectionTime = GetTime();
        }
    }
}
void DrawRingGradient(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color innerColor, Color outerColor) {
    const float stepLength = (endAngle - startAngle) / segments;

    for (float angle = startAngle; angle < endAngle; angle += stepLength) {
        Vector2 innerStart = { center.x + innerRadius * cos(DEG2RAD * angle), center.y + innerRadius * sin(DEG2RAD * angle) };
        Vector2 outerStart = { center.x + outerRadius * cos(DEG2RAD * angle), center.y + outerRadius * sin(DEG2RAD * angle) };
        Vector2 innerEnd = { center.x + innerRadius * cos(DEG2RAD * (angle + stepLength)), center.y + innerRadius * sin(DEG2RAD * (angle + stepLength)) };
        Vector2 outerEnd = { center.x + outerRadius * cos(DEG2RAD * (angle + stepLength)), center.y + outerRadius * sin(DEG2RAD * (angle + stepLength)) };

        DrawTriangle(innerStart, outerStart, outerEnd, outerColor);
        DrawTriangle(innerStart, outerEnd, innerEnd, outerColor);
        DrawTriangle(innerStart, innerEnd, outerStart, innerColor);
        DrawTriangle(innerEnd, outerEnd, outerStart, innerColor);
    }
}
void Nivel2::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);

    // Dibujar mapa y otros elementos
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);

    // Dibujar un anillo semi-transparente alrededor del personaje con un área central transparente
    Vector2 center = ball.GetPosition();
    float innerRadius = ball.GetRadius() + 40;
    float outerRadius = ball.GetRadius() + 200;
    DrawRing(center, innerRadius, outerRadius, 0, 360, 0, Fade(BLACK, 0.99f));
    DrawRing(center, 35, 100, 0, 360, 0, Fade(BLACK, 0.65f));
    DrawRing(center, 32.5, 95, 0, 360, 0, Fade(BLACK, 0.55f));
    DrawRing(center, 30, 90, 0, 360, 0, Fade(BLACK, 0.45f));
    DrawRing(center, 27.5, 85, 0, 360, 0, Fade(BLACK, 0.35f));
    DrawRing(center, 25, 80, 0, 360, 0, Fade(BLACK, 0.25f));
    DrawRing(center, 22.5, 75, 0, 360, 0, Fade(BLACK, 0.15f));
    DrawRing(center, 20, 70, 0, 360, 0, Fade(BLACK, 0.05f));
 //   DrawRing(center, 17.5, 65, 0, 360, 0, Fade(BLACK, 0.45f));
   // DrawRing(center, 15, 60, 0, 360, 0, Fade(BLACK, 0.25f));
    //DrawRing(center, 12.5, 55, 0, 360, 0, Fade(BLACK, 0.15f));



    // Dibujar personajes
    ball.Draw();
    enemigo.Draw();

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    DrawMiniMap(); // Dibujar el minimapa al final

    EndMode2D();
}



