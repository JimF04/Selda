//
// Created by winjimmy on 5/3/2024.
//

#include "Nivel5.h"
#include "../Algoritmos/AStar.h"


Nivel5::Nivel5(int screenWidth, int screenHeight) : Nivel(screenWidth, screenHeight){
    // Iniciar clases
    ball = Ball();
    ball.setPosition({ 592, 704 });
    boss = Boss();
    boss.setPosition({36,24});
    boss.SpawnSlime(slimes);
    boss.SpawnSlime(slimes);
    boss.SpawnSlime(slimes);


    camera.zoom = 1.0f;

    LoadMap("../BossLevel.json", 0, floor);
    LoadMap("../BossLevel.json", 1, saferoom);
    LoadMap("../BossLevel.json", 2, wall);
    LoadMap("../BossLevel.json", 3, traps);

    miniMapTexture = LoadTexture("../assets/BossLevel.png");
    levelMusic = LoadMusicStream("../assets/boss_music.mp3");
    PlayMusicStream(levelMusic);
}

void Nivel5::Update() {
    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;

    if (ball.lives <=0){
        Nivel::ResetLevel(592,704);

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
    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");
    UpdateMusicStream(levelMusic);


    //==============Update de los enemigos===============


    AStar astar(wall);
    int ball_x_grid = static_cast<int>(ball.GetPosition().x / TILE_SIZE);
    int ball_y_grid = static_cast<int>(ball.GetPosition().y / TILE_SIZE);

    int enemy_x_grid = static_cast<int>(boss.GetPosition().x / TILE_SIZE);
    int enemy_y_grid = static_cast<int>(boss.GetPosition().y / TILE_SIZE);

    Stack<Vector2> path = astar.findPath(enemy_x_grid, enemy_y_grid, ball_x_grid, ball_y_grid);
    path.pop();
    boss.FollowPath(path);


    UpdateChests(cofres);
    UpdateJars(jarrones);
}



void Nivel5::Draw() {
    BeginMode2D(camera);

    ClearBackground(BLACK);
    mapa.DrawMap(floor, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(saferoom, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(wall, 25, TEXTURE_TILEMAP);
    mapa.DrawMap(traps, 25, TEXTURE_TILEMAP);
    DrawMiniMap();
    ball.Draw();
    ball.DrawHearts(camera);
    boss.Draw();


    //===========Slimes================
    for (auto& slime : slimes) {
        slime.Draw();

    }


    //===========Objetos================
    for(auto& cofre:cofres){
        cofre.drawTile();
    }
    DrawChestCounter();

    for(auto& jarron:jarrones){
        jarron.drawTile();
    }


    EndMode2D();
}