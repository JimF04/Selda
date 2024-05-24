//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel3.h"
#include "../ball.h"
#include "raymath.h"


Nivel3::Nivel3(int screenWidth, int screenHeight,int puntuacionInicial) : Nivel(screenWidth, screenHeight){
    contadorPuntuacion = puntuacionInicial;
    ball.setPosition({ 368, 80 });
    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();


    LoadMap("../Level3.json", 0, floor);
    LoadMap("../Level3.json", 1, saferoom);
    LoadMap("../Level3.json", 2, wall);
    LoadMap("../Level3.json", 3, traps);
    LoadMap("../Level3.json", 4, falsefloor);

    miniMapTexture = LoadTexture("../assets/Level3.png");
    levelMusic = LoadMusicStream("../assets/lvl3_music.mp3");
    PlayMusicStream(levelMusic);

//===========Objetos==============//
    for(int i = 0;i<5;i++){
        cofres.push_back(Cofres());
    }
    cofres[0].setPosition({14,39});
    cofres[1].setPosition({4,15});
    cofres[2].setPosition({51,9});
    cofres[3].setPosition({66,33});
    cofres[4].setPosition({31,39});



    for(int i = 0; i < 5;i++){
        jarrones.push_back(Jarrones());
    }

    jarrones[0].setPosition({53,26});
    jarrones[1].setPosition({72,46});
    jarrones[2].setPosition({41,15});
    jarrones[3].setPosition({51,47});
    jarrones[4].setPosition({38,3});

    //===========Enemigos==============//

    for (int i = 0; i < 4; i++){
        espectros.push_back(Espectro("azul"));
    }

    espectros[0].setPosition({8, 28});
    route1.push({8,19});
    route1.push({8,28});
    espectros[0].setRoute(route1);

    espectros[1].setPosition({36, 17});
    route2.push({36,28});
    route2.push({36,17});
    espectros[1].setRoute(route2);

    espectros[2].setPosition({15, 40});
    route3.push({15,46});
    route3.push({20,46});
    route3.push({20,40});
    route3.push({25,40});
    route3.push({25,46});
    route1.push({30,46});
    route1.push({30,41});
    route1.push({30,46});
    route3.push({25,46});
    route3.push({25,40});
    route3.push({20,40});
    route3.push({20,46});
    route3.push({15,46});
    route3.push({15,40});
    espectros[2].setRoute(route3);

    espectros[3].setPosition({60, 29});
    route4.push({70,29});
    route4.push({70,39});
    route4.push({70,29});
    route4.push({60,29});
    espectros[3].setRoute(route4);


    for ( int i = 0; i < 4; i++){
        ojos_espectrales.push_back(Ojo_Espectral());
    }
    ojos_espectrales[0].setPosition({22, 22});
    ojos_espectrales[1].setPosition({66, 8});
    ojos_espectrales[2].setPosition({51, 39});
    ojos_espectrales[3].setPosition({51, 39});


    for ( int i = 0; i < 3; i++){
        chocobos.push_back(Chocobos());
    }
    chocobos[0].setPosition({53, 8});
    chocobos[1].setPosition({21, 31});
    chocobos[2].setPosition({69, 38});

}



void Nivel3::Update() {

    camera.zoom=1.0f;

    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;


    if (ball.lives <=0){
        Nivel::ResetLevel(368,80);

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

    if (IsKeyDown(KEY_K) ) {
        ball.IsDefending = true;
        ball.Defender();
        keyKPressed = true;
        keyKReleaseTime = -1;
    }

    if (IsKeyUp(KEY_K)) {
        if (keyKReleaseTime < 0) {
            keyKReleaseTime = GetTime();
        } else if (GetTime() - keyKReleaseTime >= 0.6f) {
            ball.IsDefending = false;
        }
    } else {
        keyKReleaseTime = -1;
    }


    LayerCollision(deltaX, deltaY, traps, "traps");
    LayerCollision(deltaX, deltaY, falsefloor, "falsefloor");
    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, floor, "stairs");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");

    UpdateMusicStream(levelMusic);


    //==============Update de los enemigos===============

    chocobos[0].bresenham(ball.GetPosition(), wall);
    chocobos[1].bresenham(ball.GetPosition(), wall);
    chocobos[2].bresenham(ball.GetPosition(), wall);

    UpdateEspectros(espectros);
    UpdateOjos(ojos_espectrales,ball.GetPosition());
    UpdateChoco(chocobos);
    UpdatesAzules(espectros, ball.GetPosition());

    if (!personaje_visto) {
        espectros[0].LoopPath(route1);
        espectros[1].LoopPath(route2);
        espectros[2].LoopPath(route3);
        espectros[3].LoopPath(route4);

    }

    //==============Update de los objetos===============
    UpdateChests(cofres);
    UpdateJars(jarrones);



    // ======================Eliminar Enemigos========================//
    for(auto& espectro:espectros){
        float distance = Vector2Distance(ball.GetPosition(),espectro.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
                ball.Atacar();
                contadorPuntuacion+=20;
                espectro.setPosition({-1000,-1000});
            }
        }
    }

    //Ojos espectrales
    for(auto& ojo_espectral:ojos_espectrales){
        float distance = Vector2Distance(ball.GetPosition(),ojo_espectral.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
                cout<<"Collisioned with Ojo espectral";
                ball.Atacar();
                ojo_espectral.setPosition({-1000,1000});
                contadorPuntuacion += 15;
            }
        }
    }

    for(auto& choco:chocobos){
        float distance = Vector2Distance(ball.GetPosition(),choco.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
                cout<<"Collisioned with Ojo espectral";
                ball.Atacar();
                choco.setPosition({-1000,1000});
                contadorPuntuacion += 30;
            }
        }
    }

}

void Nivel3::ResetLevel() {
    ball.setPosition({90, 160});
    //enemigo.setPosition({100, 300});
    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();
}
void Nivel3::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(traps, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(falsefloor, 25, TEXTURE_TILEMAP);

    //=============Objetos================
    for(auto& cofre:cofres){
        cofre.drawTile();
    }
    DrawChestCounter();

    for(auto& jarron:jarrones){
        jarron.drawTile();
    }
    DrawPuntuationCounter();
    DrawMiniMap();
    ball.Draw();
    ball.DrawHearts(camera);

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    //=============Enemigos================

    for (auto& espectro : espectros) {
        espectro.Draw();
    }

    for (auto& ojo_espectral : ojos_espectrales) {
        ojo_espectral.Draw();
    }
    DrawPuntuationCounter();

    for (auto& chocobo : chocobos) {
        chocobo.Draw();
    }

    EndMode2D();
}