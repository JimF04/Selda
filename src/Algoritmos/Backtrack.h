//
// Created by winjimmy on 5/4/2024.
//

#ifndef SELDA_BACKTRACK_H
#define SELDA_BACKTRACK_H

#include <iostream>
#include <vector>
#include <stack>
#include "raylib.h"
#include "../Mapa.h"
#include "../DataStructures/Stack.h"
#include <glog/logging.h>

struct Node {
    int x, y;
    Node* parent;
    Node(int x, int y, Node* parent = nullptr) : x(x), y(y), parent(parent) {}
};

class Backtrack {
public:
    Backtrack(int wall[][50]);
    Stack<Vector2> findPath(int startX, int startY, int endX, int endY);
    void printPath(Stack<Vector2> path) const;

private:
    int (*wall)[50];
    bool isValid(int x, int y);
};

#endif //SELDA_BACKTRACK_H
