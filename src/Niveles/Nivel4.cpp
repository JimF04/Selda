//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel4.h"
#include "raylib.h"
#include "raymath.h"

Nivel4::Nivel4(int screenWidth, int screenHeight,int puntuacionInicial) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    contadorPuntuacion = puntuacionInicial;
    ball.setPosition({ 112, 672 });

    LoadMap("../Level4.json", 0, floor);
    LoadMap("../Level4.json", 1, saferoom);
    LoadMap("../Level4.json", 2, wall);
    LoadMap("../Level4.json", 3, traps);
    LoadMap("../Level4.json", 4, falsefloor);

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    miniMapTexture = LoadTexture("../assets/Level4.png");
    levelMusic = LoadMusicStream("../assets/lvl4_music.mp3");
    PlayMusicStream(levelMusic);


    for(int i = 0;i<5;i++){
        cofres.push_back(Cofres());
    }
    cofres[0].setPosition({24,5});
    cofres[1].setPosition({52,39});
    cofres[2].setPosition({45,26});
    cofres[3].setPosition({45,15});
    cofres[4].setPosition({23,31});



    for(int i = 0; i < 5;i++){
        jarrones.push_back(Jarrones());
    }

    jarrones[0].setPosition({23,23});
    jarrones[1].setPosition({72,29});
    jarrones[2].setPosition({13,6});
    jarrones[3].setPosition({35,10});
    jarrones[4].setPosition({28,38});


    for ( int i = 0; i < 2; i++){
        rojo.push_back(Espectro("rojo"));
    }

    rojo[0].setPosition({49,26});
    route1.push({49,34});
    route1.push({49,26});
    rojo[0].setRoute(route1);

    rojo[1].setPosition({21,8});
    route2.push({28,8});
    route2.push({21,8});
    rojo[1].setRoute(route2);

    for ( int i = 0; i < 2; i++){
        rojo.push_back(Espectro("gris"));
    }

    rojo[2].setPosition({37,25});
    route3.push({37,11});
    route3.push({43,11});
    route3.push({37,11});
    route3.push({37,25});
    rojo[2].setRoute(route3);

    rojo[3].setPosition({21,39});
    route4.push({36,39});
    route4.push({36,44});
    route4.push({21,44});
    route4.push({21,39});
    rojo[3].setRoute(route4);

    for ( int i = 0; i < 1; i++){
        azul.push_back(Espectro("azul"));
    }

    azul[0].setPosition({71,20});
    route5.push({71,41});
    route5.push({71,20});
    azul[0].setRoute(route5);

    for ( int i = 0; i < 3; i++){
        chocobos.push_back(Chocobos());
    }
    chocobos[0].setPosition({25, 22});
    chocobos[1].setPosition({25, 30});
    chocobos[2].setPosition({69, 17});

    for ( int i = 0; i < 2; i++){
        ojos_espectrales.push_back(Ojo_Espectral());
    }
    ojos_espectrales[0].setPosition({57, 45});
    ojos_espectrales[1].setPosition({37, 25});


}



void Nivel4::Update() {
    camera.zoom=1.0f;

    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;

    if (ball.lives <=0){
        Nivel::ResetLevel(112,672);

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
    for(auto& espectro:rojo){
        float distance = Vector2Distance(ball.GetPosition(),espectro.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
                ball.Atacar();
                contadorPuntuacion+=20;
                espectro.setPosition({-1000,1000});
            }
        }
    }

    for(auto& espectro:azul){
        float distance = Vector2Distance(ball.GetPosition(),espectro.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
                ball.Atacar();
                contadorPuntuacion+=20;
                espectro.setPosition({-1000,-1000});
            }
        }
    }

//    for(auto& espectro:gris){
//        float distance = Vector2Distance(ball.GetPosition(),espectro.GetPosition());
//        if(distance < ball.GetRadius() + 10){
//            if(IsKeyDown(KEY_L)){
//                ball.Atacar();
//                contadorPuntuacion+=20;
//                espectro.setPosition({-1000,1000});
//            }
//        }
//    }

    for(auto& ojo_espectral:ojos_espectrales){
        float distance = Vector2Distance(ball.GetPosition(),ojo_espectral.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
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
                ball.Atacar();
                choco.setPosition({-1000,1000});
                contadorPuntuacion += 30;
            }
        }
    }

    chocobos[0].bresenham(ball.GetPosition(), wall);
    chocobos[1].bresenham(ball.GetPosition(), wall);
    chocobos[2].bresenham(ball.GetPosition(), wall);

    UpdateRojos(rojo, activeFireballs);

    UpdateEspectros(rojo);
    UpdateEspectros(azul);
    UpdatesAzules(azul, ball.GetPosition());

    UpdateChoco(chocobos);
    UpdateOjos(ojos_espectrales,ball.GetPosition());

    if (!personaje_visto) {
        rojo[0].LoopPath(route1);
        rojo[1].LoopPath(route2);
        rojo[2].LoopPath(route3);
        rojo[3].LoopPath(route4);
        azul[0].LoopPath(route5);
    }


    //==============Update de los objetos===============
    UpdateChests(cofres);
    UpdateJars(jarrones);
}


void Nivel4::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(traps, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(falsefloor, 25, TEXTURE_TILEMAP);
    DrawMiniMap();
    ball.Draw();
    ball.DrawHearts(camera);

    //===========Enemigos================
    for (auto& espectro : rojo) {
        espectro.Draw();
        espectro.DrawFireballs(activeFireballs);

    }

    for (auto& espectro : azul) {
        espectro.Draw();
    }


    for (auto& choco : chocobos) {
        choco.Draw();
    }

    for (auto& ojos : ojos_espectrales) {
        ojos.Draw();
    }

    //===========Objetos================
    for(auto& cofre:cofres){
        cofre.drawTile();
    }
    DrawChestCounter();

    for(auto& jarron:jarrones){
        jarron.drawTile();
    }

    DrawPuntuationCounter();


    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    EndMode2D();
}