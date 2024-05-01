#include "Mapa.h"
#include <stdlib.h>
#include "raylib.h"
#define MAP_TILE_SIZE    70         // Tiles size 32x32 pixels
#define PLAYER_SIZE      30         // Player size
#define PLAYER_TILE_VISIBILITY  2
RenderTexture2D fogOfWar;

Mapa::Mapa(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    darkGreen = Color{20, 160, 133, 255};

    const int wallPosX = 500;
    const int wallPosY = 100;
    const int wallWidth = 50;
    const int wallHeight = 50;

    tilesX = 25;
    tilesY = 20;
    tileIds = (unsigned char *)calloc(tilesX*tilesY, sizeof(unsigned char));
    tileFog = (unsigned char *)calloc(tilesX*tilesY, sizeof(unsigned char));

    // Load map tiles (generating 2 random tile ids for testing)
    // NOTE: Map tile ids should be probably loaded from an external map file
    for (unsigned int i = 0; i < tilesY*tilesX; i++) tileIds[i] = GetRandomValue(0, 5);

    // Initialize player, enemy, and wall
    personaje = Ball();
    personaje.radius = PLAYER_SIZE;
    enemigo = Enemy();


    Vector2 wallPosition = { wallPosX, wallPosY };
    pared = Wall(wallPosition, wallWidth, wallHeight);


    // Render texture to render fog of war
    // NOTE: To get an automatic smooth-fog effect we use a render texture to render fog
    // at a smaller size (one pixel per tile) and scale it on drawing with bilinear filtering
    fogOfWar = LoadRenderTexture(tilesX, tilesY);
    SetTextureFilter(fogOfWar.texture, FILTER_TRILINEAR);

    camera = { 0 };
    camera.target = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
    camera.offset = (Vector2){ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

}
void Mapa::Update() {
    float deltaX = 0;
    float deltaY = 0;
    const float playerSpeed = 5.0f; // Velocidad del jugador

    if (IsKeyDown(KEY_D)) deltaX += playerSpeed;
    if (IsKeyDown(KEY_A)) deltaX -= playerSpeed;
    if (IsKeyDown(KEY_W)) deltaY -= playerSpeed;
    if (IsKeyDown(KEY_S)) deltaY += playerSpeed;

    Vector2 projectedPosition = {personaje.GetPosition().x + deltaX, personaje.GetPosition().y + deltaY };
    Rectangle ballRect = {projectedPosition.x - personaje.radius, projectedPosition.y - personaje.radius, static_cast<float>(personaje.radius * 2), static_cast<float>(personaje.radius * 2)};

    if (!CheckCollisionRecs(ballRect, pared.GetCollisionRect())) {
        personaje.Move(deltaX, deltaY);
    }


    Vector2 projectedEnemyPosition = { enemigo.position.x + deltaX, enemigo.position.y + deltaY };
    Rectangle enemyRect = { projectedEnemyPosition.x - enemigo.radius, projectedEnemyPosition.y - enemigo.radius, static_cast<float>(enemigo.radius * 2), static_cast<float>(enemigo.radius * 2) };

    // Check collision between enemy and wall
    if (!CheckCollisionRecs(enemyRect, pared.GetCollisionRect())) {
        enemigo.FollowBreadcrumb(personaje.GetPosition());
    } else {
        enemigo.Move(5, 5);
    }

    // Actualizar la posición de la cámara para seguir al personaje
    camera.target = personaje.GetPosition();



    for (unsigned int i = 0; i < tilesX*tilesY; i++) if (tileFog[i] == 1) tileFog[i] = 2;

    // Get current tile position from player pixel position
    personaje.playerTileX = (int)((personaje.GetPosition().x + MAP_TILE_SIZE / 2) / MAP_TILE_SIZE);
    personaje.playerTileY = (int)((personaje.GetPosition().y + MAP_TILE_SIZE / 2) / MAP_TILE_SIZE);

    // Check visibility and update fog
    for (int y = (personaje.playerTileY - PLAYER_TILE_VISIBILITY); y < (personaje.playerTileY + PLAYER_TILE_VISIBILITY); y++)
        for (int x = (personaje.playerTileX - PLAYER_TILE_VISIBILITY); x < (personaje.playerTileX + PLAYER_TILE_VISIBILITY); x++)
            if ((x >= 0) && (x < (int)tilesX) && (y >= 0) && (y < (int)tilesY)) tileFog[y*tilesX + x] = 1;




}

void Mapa::Draw() {
    BeginMode2D(camera);

    BeginTextureMode(fogOfWar);
    ClearBackground(BLANK);
    for (unsigned int y = 0; y < tilesY; y++)
        for (unsigned int x = 0; x < tilesX; x++)
            if (tileFog[y*tilesX + x] == 0) DrawRectangle(x, y, 1, 1, BLACK);
            else if (tileFog[y*tilesX + x] == 2) DrawRectangle(x, y, 1, 1, Fade(BLACK, 0.8f));
    EndTextureMode();

    DrawMap();
    DrawUI();

    EndMode2D();
}

void Mapa::DrawMap() {
    for (unsigned int y = 0; y < tilesY; y++) {
        for (unsigned int x = 0; x < tilesX; x++) {
            // Draw tiles from id (and tile borders)
            DrawRectangle(x*MAP_TILE_SIZE, y*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE,
                          (tileIds[y*tilesX + x] == 0)? BLUE : Fade(BLUE, 0.9f));
            DrawRectangleLines(x*MAP_TILE_SIZE, y*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, Fade(DARKBLUE, 0.5f));
        }
    }
    // Draw player and enemy
    personaje.Draw();
    enemigo.Draw();
    pared.Draw();

    // Draw fog of war (scaled to full map, bilinear filtering)
    DrawTexturePro(fogOfWar.texture, (Rectangle){ 0, 0, (float)fogOfWar.texture.width, (float)-fogOfWar.texture.height },
                   (Rectangle){ 0, 0, (float)tilesX*MAP_TILE_SIZE, (float)tilesY*MAP_TILE_SIZE },
                   (Vector2){ 0, 0 }, 0.0f, WHITE);
}

void Mapa::DrawUI() {
    DrawText(TextFormat("Current tile: [%i,%i]", personaje.playerTileX, personaje.playerTileX), 10, 10, 20, RAYWHITE);

}
