#include "Backtrack.h"
#include <queue>

Backtrack::Backtrack(int wall[][50]) : wall(wall) {}

bool Backtrack::isValid(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT && wall[x][y] == 0);
}

void Backtrack::printPath(Stack<Vector2> path) const {
    LOG(INFO) << "Camino encontrado:";
    while (!path.empty()) {
        Vector2 point = path.top();
        std::cout << "(" << static_cast<int>(point.x) << ", " << static_cast<int>(point.y) << ")" << std::endl;
        path.pop();
    }
}

Stack<Vector2> Backtrack::findPath(int startX, int startY, int endX, int endY) {
    Stack<Vector2> path;
    std::queue<Node*> queue;
    bool visited[MAP_WIDTH][MAP_HEIGHT] = {false};

    queue.push(new Node(startX, startY));
    visited[startX][startY] = true;

    Node* endNode = nullptr;

    while (!queue.empty()) {
        Node* currentNode = queue.front();
        queue.pop();

        if (currentNode->x == endX && currentNode->y == endY) {
            endNode = currentNode;
            break;
        }

        // Direcciones: derecha, izquierda, abajo, arriba
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; ++i) {
            int newX = currentNode->x + dx[i];
            int newY = currentNode->y + dy[i];

            if (isValid(newX, newY) && !visited[newX][newY]) {
                queue.push(new Node(newX, newY, currentNode));
                visited[newX][newY] = true;
            }
        }
    }

    if (endNode != nullptr) {
        Node* currentNode = endNode;
        while (currentNode != nullptr) {
            path.push({static_cast<float>(currentNode->x), static_cast<float>(currentNode->y)});
            currentNode = currentNode->parent;
        }
    }

    // Liberar memoria de los nodos
    while (!queue.empty()) {
        delete queue.front();
        queue.pop();
    }

    return path;
}