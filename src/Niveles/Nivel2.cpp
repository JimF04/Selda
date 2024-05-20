#include "Nivel2.h"
#include "raymath.h"
#include "raylib.h"

Nivel2::Nivel2(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight), vidas(5, 5) {
    // Iniciar clases
    ball = Ball();
    ball.setPosition({90, 416});
    //enemigo.setPosition({240, 416});

    for (int i = 0; i < 2; i++){
        enemigos2.emplace_back();
    }

    enemigos2[0].setPosition({240, 416});
    enemigos2[1].setPosition({146, 400});

    camera.zoom = 1.0f;

    LoadMap("../Level2.json", 0, floor);
    LoadMap("../Level2.json", 1, saferoom);
    LoadMap("../Level2.json", 2, wall);
    miniMapTexture = LoadTexture("../assets/Level2.png");
    levelMusic = LoadMusicStream("../assets/lvl2_music.mp3");
    PlayMusicStream(levelMusic);
}

void Nivel2::ResetLevel() {
    ball.setPosition({90, 160});

    enemigo.setPosition({100, 160});

    vidas.ResetLives();

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
            vidas.DecreaseLife();
            if (!vidas.IsAlive()) {
                ResetLevel();
            }
            collisionDetected = true;
            lastCollisionDetectionTime = GetTime();
        }
    }

    AStar astar(wall);

    for (auto&enemigo : enemigos2){


        int ball_x_grid = static_cast<int>( ball.GetPosition().x / TILE_SIZE);
        int ball_y_grid = static_cast<int>( ball.GetPosition().y / TILE_SIZE);

        int enemy_x_grid = static_cast<int>( enemigo.GetPosition().x / TILE_SIZE);
        int enemy_y_grid = static_cast<int>( enemigo.GetPosition().y / TILE_SIZE);

        path2 = astar.findPath(enemy_x_grid, enemy_y_grid, ball_x_grid, ball_y_grid);

        path2.pop();

        enemigo.FollowPath(path2);

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
    Vector2 ballCenter = ball.GetPosition();
    float ballInnerRadius = ball.GetRadius() + 30;
    float ballOuterRadius = ball.GetRadius() + 200;

    // Dibujar el anillo del personaje principal
    DrawRingGradient(ballCenter, ballInnerRadius, ballOuterRadius, 0, 360, 100, Fade(BLACK, 0.99f), Fade(BLACK, 0.0f));




    for (auto&enemigo : enemigos2){


        // Dibujar el mapa alrededor del enemigo
        Vector2 enemyCenter = enemigo.GetPosition();
        float enemyInnerRadius = enemigo.GetRadius() + 50;  // Reducir el tamaño del área
        float enemyOuterRadius = enemigo.GetRadius() + 50; // Reducir el tamaño del área

        // Calcular la distancia entre el personaje y el enemigo
        float distance = Vector2Distance(ballCenter, enemyCenter);

        // Determinar si los círculos se superponen
        bool circlesOverlap = (distance < (ballOuterRadius + enemyOuterRadius));

        // Dibujar el mapa alrededor del enemigo si los círculos se superponen
        if (circlesOverlap) {
            // Calcular el área de superposición
            float overlapRadius = ballOuterRadius + enemyOuterRadius - distance;

            // Dibujar el mapa en el área alrededor del enemaaigo
            Vector2 overlapCenter = enemyCenter;
            float overlapInnerRadius = enemyInnerRadius - overlapRadius;
            float overlapOuterRadius = enemyOuterRadius;

            // Dibujar el mapa en el área alrededor del enemigo
            mapa.DrawMapAtPosition(floor, 25, TEXTURE_TILEMAP, overlapCenter, overlapInnerRadius, overlapOuterRadius);
            mapa.DrawMapAtPosition(saferoom, 25, TEXTURE_TILEMAP, overlapCenter, overlapInnerRadius, overlapOuterRadius);
            mapa.DrawMapAtPosition(wall, 25, TEXTURE_TILEMAP, overlapCenter, overlapInnerRadius, overlapOuterRadius);

        }

    }

    for (auto&enemigo : enemigos2){

        enemigo.Draw();

    }



    // Dibujar personajes
    ball.Draw();
    //enemigo.Draw();

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    DrawMiniMap(); // Dibujar el minimapa al final

    EndMode2D();
}



