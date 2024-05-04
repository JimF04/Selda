#include "AStar.h"

// Función de comparación para el QuickSort
bool compareNodes(const AStarNode* a, const AStarNode* b) {
    return a->f < b->f;
}

// Función de partición del QuickSort sin usar std::swap
int partition(AStarNode** arr, int low, int high) {
    AStarNode* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (compareNodes(arr[j], pivot)) {
            i++;
            // Intercambio sin std::swap
            AStarNode* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Intercambio final sin std::swap
    AStarNode* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// Función de ordenamiento QuickSort específica para Node*
void quickSort(AStarNode** arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void AStar::printPath(Stack<Vector2> path) const {
    std::cout << "Path found:" << std::endl;
    while (!path.empty()) {
        Vector2 point = path.top();
        std::cout << "(" << static_cast<int>(point.x) << ", " << static_cast<int>(point.y) << ")" << std::endl;
        path.pop();
    }
}

AStar::AStar(int wall[][38]) :
       wall(wall){}

float AStar::heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool AStar::isValid(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT && wall[x][y] == 0);
}



Stack<Vector2> AStar::findPath(int startX, int startY, int endX, int endY) {
    Stack<Vector2> path;
    AStarNode** openList = new AStarNode*[MAP_WIDTH * MAP_HEIGHT];
    AStarNode** closedList = new AStarNode*[MAP_WIDTH * MAP_HEIGHT];
    int openListSize = 0;
    int closedListSize = 0;

    AStarNode* startNode = new AStarNode{startX, startY, 0.0f, heuristic(startX, startY, endX, endY), 0.0f, nullptr};
    openList[openListSize++] = startNode;

    while (openListSize > 0) {
        // Ordenar la lista abierta por F (menor F primero)
        quickSort(openList, 0, openListSize - 1);

        AStarNode* currentNode = openList[0];
        for (int i = 0; i < openListSize - 1; ++i) {
            openList[i] = openList[i + 1];
        }
        openListSize--;

        closedList[closedListSize++] = currentNode;

        if (currentNode->x == endX && currentNode->y == endY) {
            // Reconstruye el camino
            while (currentNode != nullptr) {
                path.push({static_cast<float>(currentNode->x), static_cast<float>(currentNode->y)});
                currentNode = currentNode->parent;
            }
            // Limpia la memoria de los nodos
            for (int i = 0; i < openListSize; ++i) delete openList[i];
            for (int i = 0; i < closedListSize; ++i) delete closedList[i];
            delete[] openList;
            delete[] closedList;
            return path;
        }

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int neighborX = currentNode->x + dx;
                int neighborY = currentNode->y + dy;
                if (isValid(neighborX, neighborY)) {
                    AStarNode* neighborNode = new AStarNode{neighborX, neighborY, 0.0f, 0.0f, 0.0f, currentNode};
                    // Calcula los valores g, h y f del vecino
                    neighborNode->g = currentNode->g + 1.0f; // Costo unitario para cada movimiento
                    neighborNode->h = heuristic(neighborNode->x, neighborNode->y, endX, endY);
                    neighborNode->f = neighborNode->g + neighborNode->h;

                    bool inOpenList = false;
                    bool inClosedList = false;
                    for (int i = 0; i < openListSize; ++i) {
                        if (neighborNode->x == openList[i]->x && neighborNode->y == openList[i]->y) {
                            inOpenList = true;
                            if (neighborNode->f < openList[i]->f) {
                                openList[i]->parent = neighborNode->parent;
                                openList[i]->g = neighborNode->g;
                                openList[i]->h = neighborNode->h;
                                openList[i]->f = neighborNode->f;
                            }
                            break;
                        }
                    }
                    for (int i = 0; i < closedListSize; ++i) {
                        if (neighborNode->x == closedList[i]->x && neighborNode->y == closedList[i]->y) {
                            inClosedList = true;
                            break;
                        }
                    }
                    if (!inOpenList && !inClosedList) {
                        openList[openListSize++] = neighborNode;
                    }
                }
            }
        }
    }

    // Si no se encontró un camino, libera la memoria de los nodos y devuelve una lista vacía
    for (int i = 0; i < openListSize; ++i) delete openList[i];
    for (int i = 0; i < closedListSize; ++i) delete closedList[i];
    delete[] openList;
    delete[] closedList;
    return path;
}
