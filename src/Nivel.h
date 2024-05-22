//
// Created by winjimmy on 5/3/2024.
//

#ifndef SELDA_NIVEL_H
#define SELDA_NIVEL_H


#include "Mapa.h"
#include "raylib.h"
#include "DataStructures/Stack.h"
#include "DataStructures/Vector.h"
#include "ball.h"
#include "Enemy/Espectro.h"
#include "Enemy/Ratones.h"
#include "Enemy/Ojo_Espectral.h"
#include "Objects/Cofres.h"
#include "Objects/Jarrones.h"

class Nivel {
public:

    // Variables de la clase

    Texture2D miniMapTexture;
    Texture2D imageTexture;
    int contadorCofres = 0;
    int contadorPuntuacion = 0;

    // Metodos de la clase

    Nivel(int screenWidth, int screenHeight);

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool CheckWinCondition() = 0;
    virtual void LoadMap(std::string mapJson, int layerIndex, int layer[MAP_WIDTH][MAP_HEIGHT]);
    virtual void LayerCollision(int deltaX, int deltaY, int layer[MAP_WIDTH][MAP_HEIGHT], std::string type);
    void DrawCenteredText(const char* text, int fontSize, Color color);
    void DrawMiniMap();
    void ResetLevel(float BallXPos, float BallYPos);

    void UpdateEspectros(Vector<Espectro>& espectros);

    void DrawChestCounter();
    void DrawPuntuationCounter();

    void UpdateRatones(Vector<Ratones>& ratones);
    void UpdatesAzules(Vector<Espectro> &azules, Vector2 vector2);

    void UpdateChests(Vector<Cofres>& cofres);
    void UpdateJars(Vector<Jarrones>& jarrones);
    void UpdateOjos(Vector<Ojo_Espectral> &ojos, Vector2 vector2);

protected:
    // Variables comunes a todos los niveles
    int screenWidth;
    int screenHeight;
    Camera2D camera;
    Mapa mapa;
    bool winCondition = false;
    int floor[MAP_WIDTH][MAP_HEIGHT];
    int wall[MAP_WIDTH][MAP_HEIGHT];
    int saferoom[MAP_WIDTH][MAP_HEIGHT];

    int traps[MAP_WIDTH][MAP_HEIGHT];
    int falsefloor[MAP_WIDTH][MAP_HEIGHT];

    Ball ball;
    int stairs [4] = {158,159,183,184};
    bool onstairs = false;

    Stack<Vector2> path;
    Stack<Vector2> pathback;
    bool personaje_visto;
    bool find_AStar = false;
    queue<Vector2> routa;

    bool visto_por_ojo;

    bool collisionDetected = false;
    double lastCollisionDetectionTime;

    Vector<Jarrones> jarrones;
    Vector<Cofres> cofres;

};

#endif //SELDA_NIVEL_H