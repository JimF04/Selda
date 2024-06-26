
//
// Created by winjimmy on 5/3/2024.
//

#include <algorithm>
#include "Nivel1.h"
#include "raylib.h"
#include "../ball.h"
#include "raymath.h"
#include "../Enemy/Enemy.h"
#include "../Objects/Cofres.h"
#include "../Objects/Jarrones.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Nivel1::Nivel1(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    InitAudioDevice();
    ball = Ball();
    personaje_visto = false;
    hitbox = Hitbox();
    ball.setPosition({90,160});
    lastCollisionDetectionTime = GetTime();

//==================Objetos==================
    for (int i = 0; i < 4; i++){
        cofres.push_back(Cofres());
    }
    cofres[0].setPosition({31,2});
    cofres[1].setPosition({68,42});
    cofres[2].setPosition({38, 20});
    cofres[3].setPosition({16, 4});

    for (int i = 0; i < 6; i++){
        jarrones.push_back(Jarrones());
    }
    jarrones[0].setPosition({43, 12});
    jarrones[1].setPosition({43, 2});
    jarrones[2].setPosition({16, 9});
    jarrones[3].setPosition({61, 24});
    jarrones[4].setPosition({68, 45});
    jarrones[5].setPosition({20, 45});


//====================Enemigos==================

   //Agrega x cantidad de espectros de un solo tipo
    for ( int i = 0; i < 4; i++){
        espectros.push_back(Espectro("gris"));

    }

    espectros[0].setPosition({17,36});
    route1.push({23,36});
    route1.push({23,44});
    route1.push({17,44});
    route1.push({17,36});
    espectros[0].setRoute(route1);

    espectros[1].setPosition({45,28});
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

    espectros[3].setPosition({56,38});
    route4.push({56,43});
    route4.push({40,43});
    route4.push({56,43});
    route4.push({56,38});
    espectros[3].setRoute(route4);

    Genes.push_back(Vector3{1.0f, 5.0f, 1.0f});
    Genes.push_back(Vector3{2.0f, 1.0f, 2.0f});
    Genes.push_back(Vector3{1.0f, 4.0f, 3.0f});

    std::vector<Vector3> alelos = CargarAleloDesdeArchivo("../assets/alelos.txt");

    Dar_genes(alelos,&espectros);

    for ( int i = 0; i < 2; i++){
        ratones.push_back(Ratones());
    }
    ratones[0].setPosition({42, 28});

    for (int i = 0; i < 2; i++){
        ojos_espectrales.push_back(Ojo_Espectral());
    }
    ojos_espectrales[0].setPosition({56,3});
    ojos_espectrales[1].setPosition({68,39});


    for ( int i = 0; i < 2; i++){
        chocobos.push_back(Chocobos());
    }
    chocobos[0].setPosition({10, 21});
    chocobos[1].setPosition({38, 38});



//==========Matrices de colisiones================
    LoadMap("../Level1.json", 0, floor);
    LoadMap("../Level1.json", 1, saferoom);
    LoadMap("../Level1.json", 2, wall);
    LoadMap("../Level1.json", 3, traps);
    LoadMap("../Level1.json", 4, falsefloor);

    miniMapTexture = LoadTexture("../assets/Level1.png");
    levelMusic = LoadMusicStream("../assets/lvl1_music.mp3");

    PlayMusicStream(levelMusic);



}


void Nivel1::Update() {
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_E);
    static bool keyKPressed = false;


    if (ball.lives <= 0) {
        Nivel::ResetLevel(90, 160);
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

    //==================Eliminar a los enemigos=======================//

    //RATA:
    for(auto& raton:ratones){
        float distance = Vector2Distance(ball.GetPosition(),raton.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
                cout<<"Collisioned with Rat";
                ball.Atacar();
                contadorPuntuacion += 10;
                cout<<contadorPuntuacion;
                raton.setPosition({-1000,1000});
            }
        }
    }

    //ESPECTROS:

    for(auto& espectro:espectros){
        float distance = Vector2Distance(ball.GetPosition(),espectro.GetPosition());
        if(distance < ball.GetRadius() + 10){
            if(IsKeyDown(KEY_L)){
                cout<<"Collisioned with Espectro";
                ball.Atacar();
                contadorPuntuacion += 15;
                cout<<contadorPuntuacion;
                espectro.setPosition({-1000,1000});

            }
        }
    }

    //OJOS ESPECTRALES:

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


    LayerCollision(deltaX, deltaY, traps, "traps");
    LayerCollision(deltaX, deltaY, falsefloor, "falsefloor");
    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, floor, "stairs");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");

    UpdateMusicStream(levelMusic);

    //==========Updates de los enemigos================

    UpdateEspectros(espectros);
    UpdateRatones(ratones,espectros);
    UpdateOjos(ojos_espectrales, ball.GetPosition());
    UpdatesAzules(espectros, ball.GetPosition());
    UpdateChoco(chocobos);

    chocobos[0].bresenham(ball.GetPosition(), wall);
    chocobos[1].bresenham(ball.GetPosition(), wall);



    //==========Updates de los objetos================

    UpdateChests(cofres);
    UpdateJars(jarrones);

    if (!personaje_visto) {
        espectros[0].LoopPath(route1);
        espectros[1].LoopPath(route2);
        espectros[2].LoopPath(route3);
        espectros[3].LoopPath(route4);

    }

    // Reproducción del sonido si el personaje es visto por un ojo
    if (IsKeyDown(KEY_T)){
        ball.LaunchFireball();
    }
    ball.UpdateFireballs();

}


void Nivel1::Draw() {
    BeginMode2D(camera);
    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(traps, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(falsefloor, 25, TEXTURE_TILEMAP);

    //=======================Objetos=========================

    for(auto& cofre:cofres){
        cofre.drawTile();
    }
    DrawChestCounter();


    for(auto& jarron : jarrones) { // Dibuja cada jarrón en el vector de jarrones
        jarron.drawTile();
    }

    //========================Enemigos========================

    for (auto& Espectro : espectros) {
        Espectro.Draw();
    }
    DrawPuntuationCounter();

    for (auto& raton : ratones) {
        raton.Draw();
    }
    DrawPuntuationCounter();

    for (auto& ojo_espectral : ojos_espectrales) {
        ojo_espectral.Draw();
    }
    DrawPuntuationCounter();

    for (auto& chocobo : chocobos) {
        chocobo.Draw();
    }

    //========================Otros========================
    ball.Draw();
    ball.DrawHearts(camera);

    if (ball.GetSafeRoom()){
        DrawCenteredText("SAFE ROOM", 10, GREEN);
    }

    if (personaje_visto) {
        DrawCenteredText("En vista",10, RED);
    }

    ball.DrawFireballs();

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
