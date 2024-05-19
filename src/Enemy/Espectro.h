//
// Created by jimmy on 18/05/24.
//

#ifndef SELDA_ESPECTRO_H
#define SELDA_ESPECTRO_H

#include "Enemy.h"


using namespace std;

class Espectro : public Enemy
{
public:
    Espectro() : Enemy(), type("default") {}
    Espectro(const string& type);
    //void Draw() const override;

private:

    string type;

};


#endif //SELDA_ESPECTRO_H
