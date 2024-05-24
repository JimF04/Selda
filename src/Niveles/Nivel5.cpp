#include "Nivel5.h"
#include "../Algoritmos/AStar.h"

Nivel5::Nivel5(int screenWidth, int screenHeight,int puntuacionInicial) : Nivel(screenWidth, screenHeight) {
    // Iniciar clases
    contadorPuntuacion = puntuacionInicial;
    ball = Ball();
    ball.setPosition({ 592, 704 });
    boss = Boss();
    boss.setPosition({36,24});

    LoadMap("../BossLevel.json", 0, floor);
    LoadMap("../BossLevel.json", 1, saferoom);
    LoadMap("../BossLevel.json", 2, wall);
    LoadMap("../BossLevel.json", 3, traps);

    miniMapTexture = LoadTexture("../assets/BossLevel.png");
    levelMusic = LoadMusicStream("../assets/boss_music.mp3");
    victoryMusic = LoadMusicStream("../assets/Victory.mp3");
    PlayMusicStream(levelMusic);
    lastSlimeSpawnTime = GetTime();
    victoryMusicStarted = false;


    //==============Dibujo de los jarrones===============//
    for(int i = 0; i<11;i++){
        jarrones.push_back(Jarrones());
    }
    jarrones[0].setPosition({35,17});
    jarrones[1].setPosition({38,17});
    jarrones[2].setPosition({30,6});
    jarrones[3].setPosition({43,6});
    jarrones[4].setPosition({27,42});
    jarrones[5].setPosition({46,42});
    jarrones[6].setPosition({55,31});
    jarrones[7].setPosition({55,18});
    jarrones[8].setPosition({18,31});
    jarrones[9].setPosition({19,15});
    jarrones[10].setPosition({36,30});



}


void Nivel5::Update() {
    double currentTime = GetTime();
    static bool cofreDetectado = false;
    int deltaX = 0;
    int deltaY = 0;
    float speed = 1.0f;
    bool isShiftPressed = IsKeyDown(KEY_LEFT_SHIFT);
    static bool keyKPressed = false;
    static double lastAttackTime = 0.0;
    static double lastBossAttackTime = 0.0;
    float distanceToPlayer = Vector2Distance(boss.GetPosition(), ball.GetPosition());
    float BossattackRange = 15.0f;
    float slimeattackRange = 15.0f;

    if (ball.lives <= 0) {
        Nivel::ResetLevel(592, 704);
        boss.IncreaseBossLives(2);
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
    if (IsKeyDown(KEY_L)) {
        ball.Atacar();

        if (currentTime - lastAttackTime >= 1.0) {
            ball.Atacar();
            float distanceToBoss = Vector2Distance(ball.GetPosition(), boss.GetPosition());
            float attackRangeToBoss = 20.0f;

            if (distanceToBoss < attackRangeToBoss) {
                boss.DecreaseBossLives();
            }

            lastAttackTime = currentTime;
        }
        for (size_t i = 0; i < slimes.getSize(); ++i) {
            float distance = Vector2Distance(ball.GetPosition(), slimes[i].GetPosition());
            float attackRange = 30.0f;

            if (distance < attackRange) {
                contadorPuntuacion += 50;
                slimes[i].setPosition({1200, -1100});

            }
        }

    }

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
    LayerCollision(deltaX, deltaY, wall, "wall");
    LayerCollision(deltaX, deltaY, saferoom, "saferoom");
    UpdateMusicStream(levelMusic);
    UpdateJars(jarrones);

    //==============Update de los enemigos===============


    AStar astar(wall);
    int ball_x_grid = static_cast<int>(ball.GetPosition().x / TILE_SIZE);
    int ball_y_grid = static_cast<int>(ball.GetPosition().y / TILE_SIZE);

    int enemy_x_grid = static_cast<int>(boss.GetPosition().x / TILE_SIZE);
    int enemy_y_grid = static_cast<int>(boss.GetPosition().y / TILE_SIZE);

    Stack<Vector2> path = astar.findPath(enemy_x_grid, enemy_y_grid, ball_x_grid, ball_y_grid);
    path.pop();
    boss.FollowPath(path);
    UpdateSlimes(slimes);
    UpdateChests(cofres);


    if (distanceToPlayer < BossattackRange) {
        double currentTime = GetTime();
        boss.Ataque();
        if (currentTime - lastBossAttackTime >= 2.0 && !ball.IsDefending) {
            ball.DecreaseLives(2);
            lastBossAttackTime = currentTime;
            boss.Ataque();
        }
    }


    if (currentTime - lastSlimeSpawnTime >= GetRandomValue(5, 8) && boss.GetBossLives() > 0) {
        boss.SpawnSlime(slimes);

        for (int i = 0; i < slimes.getSize(); ++i) {
            if (i == slimes.getSize() - 1) { // Solo para el último slime
                slimes[i].setPosition({boss.GetPosition().x / 16 + 1, boss.GetPosition().y / 16 - 1});
            }
        }
        lastSlimeSpawnTime = currentTime;
    }


    if (boss.GetBossLives() == 0 && !victoryMusicStarted) {
        StopMusicStream(levelMusic);
        victoryMusicStarted = true;
        boss.setPosition({1000, -1100});
        contadorPuntuacion += 1500;
    }

    if (victoryMusicStarted) {
        PlayMusicStream(victoryMusic);
        UpdateMusicStream(victoryMusic);

    }

    for (auto &slime: slimes) {
        float distance = Vector2Distance(ball.GetPosition(), slime.GetPosition());
        if (distance < slimeattackRange) {
            slime.Ataque();
        }
    }


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





    // Dibujar slimes
    for (auto& slime : slimes) {
        slime.Draw();
    }

    if (boss.GetBossLives() > 0) {
        float healthBarWidth = 150.0f;
        float healthBarHeight = 5.0f;
        Vector2 healthBarPosition = { ball.GetPosition().x - healthBarWidth / 2, ball.GetPosition().y + 70 };
        float healthPercentage = static_cast<float>(boss.GetBossLives()) / 20;

        DrawRectangle(healthBarPosition.x, healthBarPosition.y, healthBarWidth, healthBarHeight, BLACK);
        DrawRectangle(healthBarPosition.x, healthBarPosition.y, healthBarWidth * healthPercentage, healthBarHeight, RED);
    }

    if (boss.GetBossLives() > 0) {
        const char* bossName = "SunderBloop the Shatterer:";
        int fontSize = 10; // Font size
        Vector2 textPosition = { ball.GetPosition().x - 73, ball.GetPosition().y + 60 };
        DrawText(bossName, textPosition.x, textPosition.y, fontSize, LIGHTGRAY);
    }


    if (boss.GetBossLives() <= 0) {
        const char* message = "You Conquered the Dungeon";
        Vector2  scorepos = {-68 + camera.target.x, camera.target.y + 40};
        DrawText(FormatText("Your final score was: %d",contadorPuntuacion),scorepos.x,scorepos.y,10,GREEN);
        Vector2  treasurepos = {-60 + camera.target.x, camera.target.y + 20};
        DrawText(FormatText("Treasures collected: %d",contadorCofres),treasurepos.x,treasurepos.y,10,GREEN);
        int messageWidth = MeasureText(message, 12);
        Vector2 messagePosition = { ball.GetPosition().x - messageWidth / 2, ball.GetPosition().y -30 };
        DrawText(message, messagePosition.x, messagePosition.y, 12, GREEN);
    }
    else{
        DrawPuntuationCounter();
        DrawChestCounter();
    }

    for (auto& jarron:jarrones){
        jarron.drawTile();
    }

    EndMode2D();

}
