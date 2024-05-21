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

class Nivel {
public:

    // Variables de la clase

    Texture2D miniMapTexture;
    Texture2D imageTexture;

    // Metodos de la clase

    Nivel(int screenWidth, int screenHeight);

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool CheckWinCondition() = 0;

/**
 * @brief Resetea el nivel
 * @param mapJson path del json con el mapa
 * @param layerIndex indice de la capa del json
 * @param layer matriz de la capa
 */
    virtual void LoadMap(std::string mapJson, int layerIndex, int layer[MAP_WIDTH][MAP_HEIGHT]);

/**
 * @brief Verifica si hay colision con la capa
 *
 * @param deltaX posicion de la bola x
 * @param deltaY posicion de la bola y
 * @param layer matriz de la capa
 * @param type el tipo de la capa (floor, wall, saferoom, etc)
 */
    virtual void LayerCollision(int deltaX, int deltaY, int layer[MAP_WIDTH][MAP_HEIGHT], std::string type);

/**
 * @brief Dibuja un texto centrado
 * @param text
 * @param fontSize
 * @param color
 */
    void DrawCenteredText(const char* text, int fontSize, Color color);

/**
 * @brief Dibuja el minimapa de cada nivel
 */
    void DrawMiniMap();
    void DrawHeart();

/**
 * @brief Verifica el estado de los espectros
 *
 * Se verifica si los espectros han visto al jugador y se actualiza su estado
 * Por ejemplo, habilitar A* para seguir al jugador
 *
 * @param espectros lista de espectros
 */
    void UpdateEspectros(Vector<Espectro>& espectros);



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

    void UpdateOjos(Vector<Ojo_Espectral> &ojos, Vector2 vector2);

    Ball ball;
    int stairs [4] = {158,159,183,184};
    bool onstairs = false;

    void UpdateRatones(Vector<Ratones>& ratones);

    Stack<Vector2> path;
    Stack<Vector2> pathback;
    bool personaje_visto;
    bool find_AStar = false;
    queue<Vector2> routa;

    bool visto_por_ojo;
};

#endif //SELDA_NIVEL_H
