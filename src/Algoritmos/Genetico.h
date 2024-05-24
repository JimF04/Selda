#ifndef GENETICO_H
#define GENETICO_H

#include "../DataStructures/Vector.h"
#include "raylib.h"
#include "../Enemy/Espectro.h"
#include <fstream>
#include <iostream>

class Genetico {
public:
    Genetico();

    void Producir(Vector<Espectro> &resultados);



private:
    Vector<size_t> ObtenerMejoresIndices(const Vector<float>& promedios, int numMejores);
    void MutarVector(Vector3& vec);
    float RandFloat(float min, float max);

    int RandInt(int min, int max);
};

#endif // GENETICO_H
