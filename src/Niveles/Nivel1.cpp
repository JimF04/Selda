//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel1.h"
#include "raylib.h"
#include "../ball.h"
#include "raymath.h"
#include "../Enemy/Enemy.h"
#include "../Objects/Cofres.h"
#include "../Objects/Jarrones.h"


Stack<Vector2> path;
Stack<Vector2> pathCopy;


Nivel1::Nivel1(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight),vidas(5,5),contadorCofres(0),cofre(this){
    InitAudioDevice();
    ball = Ball();
    cofres.emplace_back(this);
    jarrones.emplace_back();
    hitbox = Hitbox();
    ball.setPosition({90,160});
    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();

    Jarrones jarron2;
    jarron2.SetPosition({770,375});
    jarrones.push_back(jarron2);

    Cofres cofre1(this);
    cofre1.SetPosition({510,40});
    cofres.push_back(cofre1);

    Cofres cofre2(this);
    cofre2.SetPosition({610, 600}); // Establecer posición del segundo cofre
    cofres.push_back(cofre2);


    camera.zoom = 1.0f;

    personaje_visto = false;

//====================Enemigos==================
    for ( int i = 0; i < 3; i++){
        espectros.push_back(Espectro("gris"));
    }


    espectros[0].setPosition({17,36});
    route1.push({23,36});
    route1.push({23,44});
    route1.push({17,44});
    route1.push({17,36});
    espectros[0].setRoute(route1);

    espectros[1].setPosition({45,28});
    route2.push({31,28});
    route2.push({31,20});
    route2.push({45,20});
    route2.push({45,28});
    espectros[1].setRoute(route2);


    espectros[2].setPosition({32,11});
    route3.push({42,11});
    route3.push({42,6});
    route3.push({32,6});
    route3.push({31,11});
    espectros[2].setRoute(route3);

    for ( int i = 0; i < 2; i++){
        ratones.push_back(Ratones());
    }
    ratones[0].setPosition({42, 28});

    ratones[1].setPosition({32, 11});

    for (int i = 0; i < 2; i++){
        ojos_espectrales.push_back(Ojo_Espectral());
    }
    ojos_espectrales[0].setPosition({56,3});
    ojos_espectrales[1].setPosition({68,39});

//==========Matrices de colisiones================
    LoadMap("../Level1.json", 0, floor);
    LoadMap("../Level1.json", 1, saferoom);
    LoadMap("../Level1.json", 2, wall);


    miniMapTexture = LoadTexture("../assets/Level1.png");
    levelMusic = LoadMusicStream("../assets/lvl1_music.mp3");

    PlayMusicStream(levelMusic);

}


void Nivel1::Update() {
    static bool cofreDetectado = false;
    static bool jarronDetectado = false;
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


    UpdateEspectros(espectros);
    UpdateRatones(ratones);
    UpdateOjos(ojos_espectrales, ball.GetPosition());


    if (!personaje_visto){

        espectros[0].LoopPath(route1);
        espectros[1].LoopPath(route2);
        espectros[2].LoopPath(route3);

    }



    for(auto& cofre : cofres){
        float distancian = Vector2Distance(ball.GetPosition(),cofre.GetPosition());
        if(distancian < ball.GetRadius() + 11 && !cofre.abierto){
            if(IsKeyDown(KEY_O) && !cofreDetectado){ // Verificar si la tecla O está presionada y el cofre no ha sido detectado
                cofre.Still();
                cout<<"Cofre Abierto"<<endl;
                contadorCofres++;
                cout<<contadorCofres;
                cofreDetectado = true;
                cofre.abierto = true;// Marcar el cofre como detectado para este fotograma
            }
            else if (!IsKeyDown(KEY_O)) {
                cofreDetectado = false; // Reiniciar la detección del cofre si la tecla O ya no está presionada
            }
        }
    }

    for(auto& jarron: jarrones){
        float distancie = Vector2Distance(ball.GetPosition(), jarron.GetPosition());
        if(distancie < ball.GetRadius() + 20 && !jarron.abierto){
            if(IsKeyDown(KEY_L) && !jarronDetectado){
                jarron.Anim();
                vidas.IncreaseLife();
                cout << "Jarron abierto" << endl;
                jarronDetectado = true;
                jarron.abierto = true;
            }
                // Solo restablece jarronDetectado si el jarrón está abierto y la tecla Q está suelta
            else if (!IsKeyDown(KEY_L) && jarron.abierto) {
                jarronDetectado = false;
            }
        }
    }




   //Realiza la detección de colisiones solo si ha pasado suficiente tiempo y no se ha detectado una colisión recientemente
    for(auto& espectros: espectros){
        if (!collisionDetected && GetTime() - lastCollisionDetectionTime >= 2.0) {
            if (ball.CheckCollisionWithEnemy(espectros)) {
               vidas.DecreaseLife();
                if(!vidas.IsAlive()){
                    ResetLevel();
                }
                collisionDetected = true;
                lastCollisionDetectionTime = GetTime();
            }
        }
        collisionDetected = false;

    }

}

void Nivel1::ResetLevel() {
    ball.setPosition({90, 160});

//    for (auto& enemy : enemigos) {
//        enemy.setPosition({100, 300}); // Restablecer la posición de cada enemigo
//    }

    collisionDetected = false;
    vidas.ResetLives();
    lastCollisionDetectionTime = GetTime();
}

void Nivel1::Draw() {
    BeginMode2D(camera);
    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);

    for(const auto& cofre:cofres){
        cofre.Draw();
        cofre.DrawCounter(camera);
    }

    for(const auto& jarron : jarrones) { // Dibuja cada jarrón en el vector de jarrones
        jarron.Draw();
    }


    ball.Draw();
    vidas.Draw(camera);

    for (auto& espectro : espectros) {
        espectro.Draw();
    }

    for (auto& raton : ratones) {
        raton.Draw();
    }

    for (auto& ojo_espectral : ojos_espectrales) {
        ojo_espectral.Draw();
    }

//    int textPosX = GetScreenWidth() / 2 - MeasureText(FormatText("x: %d", contadorCofres), 20) / 2 + camera.target.x;
//    int textPosY = 10 + camera.target.y; // Altura fija desde la parte superior de la pantalla
//
//    DrawText(FormatText("x: %d", contadorCofres), textPosX, textPosY, 20, WHITE);

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    if (personaje_visto) {
        DrawCenteredText("En vista",10, RED);
        // También puedes usar un emoji
        // DrawText("\xF0\x9F\x91\x81", screenWidth / 2 - MeasureText("\xF0\x9F\x91\x81", 30) / 2, screenHeight / 2, 30, RED);
    }

    DrawMiniMap();
    EndMode2D();
}





void Nivel1::DrawAStar(Stack<Vector2> path) {
    // Calcula el desplazamiento necesario para centrar los círculos en cada celd
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
