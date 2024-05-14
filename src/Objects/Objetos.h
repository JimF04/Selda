
#ifndef SELDA_OBJETOS_H
#define SELDA_OBJETOS_H

#include "raylib.h"

class Objetos{
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
};


#endif //SELDA_OBJETOS_H
