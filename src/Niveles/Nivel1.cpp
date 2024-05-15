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

    enemigos;
    cofres;
    enemigos.emplace_back();
    enemigos.emplace_back();
    hitbox = Hitbox();
    ball.setPosition({90,160});
    collisionDetected = false;
    lastCollisionDetectionTime = GetTime();

    Jarrones jarron1;
    jarron1.SetPosition({520,40});
    jarrones.push_back(jarron1);

    Cofres cofre1(this);
    cofre1.SetPosition({510,40});
    cofres.push_back(cofre1);

    Cofres cofre2(this);
    cofre2.SetPosition({610, 600}); // Establecer posición del segundo cofre
    cofres.push_back(cofre2);


    camera.zoom = 1.0f;




    personaje_visto = false;
    enemigos[0].setPosition({368,385});
    enemigos[0].initial_position={368,385};



    LoadMap("../Level1.json", 0, floor);
    LoadMap("../Level1.json", 1, saferoom);
    LoadMap("../Level1.json", 2, wall);


    miniMapTexture = LoadTexture("../assets/Level1.png");
    levelMusic = LoadMusicStream("../assets/lvl1_music.mp3");

    PlayMusicStream(levelMusic);


}

void Nivel1::Update() {
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


    // Convertir las coordenadas de la bola a las coordenadas de la matriz



    int ball_x_grid = static_cast<int>( ball.GetPosition().x / TILE_SIZE);
    int ball_y_grid = static_cast<int>( ball.GetPosition().y / TILE_SIZE);

    int enemy_x_grid = static_cast<int>( enemigos[0].GetPosition().x / TILE_SIZE);
    int enemy_y_grid = static_cast<int>( enemigos[0].GetPosition().y / TILE_SIZE);



    AStar astar(wall);
    path = astar.findPath(enemy_x_grid,enemy_y_grid,ball_x_grid,ball_y_grid);
    path.pop();


    if(personaje_visto){
        enemigos[0].FollowPath(path);
    }
    else if(personaje_visto== false && enemigos[0].initial_position.x != enemigos[0].position.x && enemigos[0].initial_position.y != enemigos[0].position.y ){
//        path=astar.findPath(enemy_x_grid,enemy_y_grid,enemigos[0].initial_position.x/TILE_SIZE,enemigos[0].initial_position.y/TILE_SIZE);
//        enemigos[0].Back_to_place(path,TILE_SIZE);

    }



    if (!ball.GetSafeRoom()){
        personaje_visto= false;

        for (auto& enemigo : enemigos) {
            if (enemigo.FollowBreadcrumb(ball.crums)) {
                personaje_visto = true;
                break;
            }



        }

    }



    for(auto& enemy : enemigos) {
        float distance = Vector2Distance(ball.GetPosition(), enemy.GetPosition());
        if (distance < ball.GetRadius() + 10) {
            if (IsKeyDown(KEY_L)) {
                ball.Atacar();
                enemy.setPosition({-1000, 1000});
            }
        }
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




    // Realiza la detección de colisiones solo si ha pasado suficiente tiempo y no se ha detectado una colisión recientemente
//    for(auto& enemy: enemigos){
//        if (!collisionDetected && GetTime() - lastCollisionDetectionTime >= 2.0) {
//            if (ball.CheckCollisionWithEnemy(enemy)) {
//               vidas.DecreaseLife();
//                if(!vidas.IsAlive()){
//                    ResetLevel();
//                }
//                collisionDetected = true;
//                lastCollisionDetectionTime = GetTime();
//            }
//        }
//        collisionDetected = false;
//
//    }

}

void Nivel1::ResetLevel() {
    ball.setPosition({90, 160});

    for (auto& enemy : enemigos) {
        enemy.setPosition({100, 300}); // Restablecer la posición de cada enemigo
    }
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
    for (const auto& enemigo : enemigos) {
        enemigo.Draw();
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

//Holam
