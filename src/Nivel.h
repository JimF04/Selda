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
#include "Enemy/Chocobos.h"
#include "Objects/Cofres.h"
#include "Objects/Jarrones.h"
#include "Enemy/Boss.h"
#include "Enemy/Slime.h"
#include "Objects/Fireball.h"

class Nivel {
public:

    // Variables de la clase

    Texture2D miniMapTexture;
    Texture2D imageTexture;
    int contadorCofres = 0;
    Sound Ojomusica;
    Sound CofreSonido;
    int contadorPuntuacion = 0;

    \
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

    void UpdateBoss(Boss boss);
    void UpdateEspectros(Vector<Espectro>& espectros);

    void DrawChestCounter();
    void DrawPuntuationCounter();

    void UpdateRatones(Vector<Ratones>& ratones, Vector<Espectro>& espectros);
    void UpdatesAzules(Vector<Espectro> &azules, Vector2 vector2);

    void UpdateChests(Vector<Cofres>& cofres);
    void UpdateJars(Vector<Jarrones>& jarrones);
    void UpdateOjos(Vector<Ojo_Espectral> &ojos, Vector2 vector2);
    void UpdateChoco(Vector<Chocobos> &chocobos);

    void Vision(Enemy enemy);
    bool personaje_visto;
    void UpdateSlimes(Vector<Slime> &slimes);
    int GetPuntuacion()const {
        return contadorPuntuacion;
    }



    void UpdateRojos(Vector<Espectro> &rojos, std::vector<FireBall>& activeFireballs){
        for (auto& rojo : rojos) {
            if (rojo.type == "rojo") {

                if (personaje_visto) {
                    rojo.LaunchFireball(activeFireballs);
                }
                UpdateFireballs(rojos, activeFireballs);
            }
        }
    }

    void UpdateFireballs(Vector<Espectro> &rojos, std::vector<FireBall>& activeFireballs);

    int maxFireballDistance = 5;
    Vector<Vector3> Genes;
    Vector<Espectro> Regresar_resultado();
    Vector<Vector3> result;



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
    bool find_AStar = false;
    bool RataVe;

    queue<Vector2> routa;
    bool visto_por_ojo;
    bool visto_por_enemigos;
    bool collisionDetected = false;
    double lastCollisionDetectionTime;
    Vector<Jarrones> jarrones;
    Vector<Cofres> cofres;

    std::vector<FireBall> activeFireballs;

    queue<Vector2> route1;
    queue<Vector2> route2;
    queue<Vector2> route3;
    queue<Vector2> route4;
    queue<Vector2> route5;
    queue<Vector2> route6;
    queue<Vector2> route7;
    queue<Vector2> route8;



    vector<Vector3> CargarAleloDesdeArchivo(const std::string& filename);



    Vector<Espectro> espectros;

    void Dar_genes(vector<Vector3> &alelos, Vector<Espectro> *espectros);
};

#endif //SELDA_NIVEL_H