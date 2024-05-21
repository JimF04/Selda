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
    LoadMap("../Level2.json", 3, traps);
    LoadMap("../Level2.json", 4, falsefloor);
    miniMapTexture = LoadTexture("../assets/Level2.png");
    levelMusic = LoadMusicStream("../assets/lvl2_music.mp3");
    PlayMusicStream(levelMusic);


    for (int i = 0; i < 2; i++){
        espectroRojo.push_back(Espectro("rojo"));
    }
    espectroRojo[0].setPosition({6, 36});
    espectroRojo[1].setPosition({16, 25});

    //=============Objects================

    // Antorchas
    for( int i = 0; i < 16; i++){
        torch.push_back(Torch());
    }
    torch[0].setPosition({4, 27});
    torch[1].setPosition({7, 27});
    torch[2].setPosition({7, 24});
    torch[3].setPosition({4, 24});
    torch[4].setPosition({47, 8});
    torch[5].setPosition({50, 8});
    torch[6].setPosition({45, 5});
    torch[7].setPosition({52, 5});

    torch[8].setPosition({29, 43});
    torch[9].setPosition({32, 43});
    torch[10].setPosition({29, 46});
    torch[11].setPosition({32, 46});
    torch[12].setPosition({64, 34});
    torch[13].setPosition({67, 34});
    torch[14].setPosition({64, 37});
    torch[15].setPosition({67, 37});

}


void Nivel2::Update() {
    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;

    if (ball.lives <=0){
        Nivel::ResetLevel(90,416);

    }

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

    LayerCollision(deltaX, deltaY, traps, "traps");
    LayerCollision(deltaX, deltaY, falsefloor, "falsefloor");
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

void Nivel2::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);

    // Dibujar mapa y otros elementos
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(traps, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(falsefloor, 25, TEXTURE_TILEMAP);


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


    //==============Enemigos================
    for (auto&enemigo : espectroRojo){
        enemigo.Draw();
    }

    //============Objetos================
    for (auto&objeto : torch){
        objeto.drawTile();
    }

    // Dibujar personajes
    ball.Draw();
    ball.DrawHearts(camera);
    enemigo.Draw();

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    if (personaje_visto) {
        DrawCenteredText("En vista",10, RED);
        // También puedes usar un emoji
        // DrawText("\xF0\x9F\x91\x81", screenWidth / 2 - MeasureText("\xF0\x9F\x91\x81", 30) / 2, screenHeight / 2, 30, RED);
    }


    DrawMiniMap(); // Dibujar el minimapa al final

    EndMode2D();
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


void Nivel2::Draw_Fog(){
    // Dibujar un anillo semi-transparente alrededor del personaje con un área central transparente
    Vector2 ballCenter = ball.GetPosition();
    float ballInnerRadius = ball.GetRadius() + 30;
    float ballOuterRadius = ball.GetRadius() + 200;

    // Dibujar el anillo del personaje principal
    DrawRingGradient(ballCenter, ballInnerRadius, ballOuterRadius, 0, 360, 100, Fade(BLACK, 0.99f), Fade(BLACK, 0.0f));


    for (auto&enemigo : espectroRojo){

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

    for (auto& antorcha : torch) {
        Vector2 torchCenter = {antorcha.getPosition().x * 16 + 8, antorcha.getPosition().y * 16 + 8};
        float torchInnerRadius = antorcha.getSize() + 35;
        float torchOuterRadius = antorcha.getSize() + 35;

        float distance = Vector2Distance(ballCenter, torchCenter);

        bool circlesOverlap = (distance < (ballOuterRadius + torchOuterRadius));

        if (circlesOverlap) {
            float overlapRadius = ballOuterRadius + torchOuterRadius - distance;

            Vector2 overlapCenter = torchCenter;
            float overlapInnerRadius = torchInnerRadius - overlapRadius;
            float overlapOuterRadius = torchOuterRadius;

            mapa.DrawMapAtPosition(floor, 25, TEXTURE_TILEMAP, overlapCenter, overlapInnerRadius, overlapOuterRadius);
            mapa.DrawMapAtPosition(saferoom, 25, TEXTURE_TILEMAP, overlapCenter, overlapInnerRadius, overlapOuterRadius);
            mapa.DrawMapAtPosition(wall, 25, TEXTURE_TILEMAP, overlapCenter, overlapInnerRadius, overlapOuterRadius);
        }
    }
}




