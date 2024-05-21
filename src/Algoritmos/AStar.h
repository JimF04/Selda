//
// Created by winjimmy on 5/4/2024.
//

#ifndef SELDA_ASTAR_H
#define SELDA_ASTAR_H


#include <iostream>
#include <vector>
#include <stack>
#include "raylib.h"
#include "../Mapa.h"
#include "../DataStructures/Stack.h"
#include <glog/logging.h>

// Estructura para representar un nodo en el algoritmo A*
struct AStarNode {
    int x;
    int y;
    float g;
    float h;
    float f;
    AStarNode* parent;
};

class AStar {
public:
    AStar(int wall[][50]);
    Stack<Vector2> findPath(int startX, int startY, int endX, int endY);
    void printPath(Stack<Vector2> path) const ;

private:
    int (*wall)[50];

    float heuristic(int x1, int y1, int x2, int y2);
    bool isValid(int x, int y);
};


#endif //SELDA_ASTAR_H
