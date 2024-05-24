#include "Genetico.h"
#include "../Enemy/Espectro.h"

Genetico::Genetico() {

}

void Genetico::Producir(Vector<Espectro> &resultados) {
    std::ofstream archivo("../assets/alelos.txt", std::ios::app);
    if (!archivo.is_open()) {
        LOG(ERROR) << "Error: No se pudo abrir el archivo 'alelos.txt' para escritura.";
        return;
    }

    Vector<float> puntuaciones;
    for (const auto& espectro : resultados) {
        float puntuacion = espectro.duracion * espectro.ataques * espectro.lives;
        puntuaciones.push_back(puntuacion);
    }


    Vector<size_t> mejoresIndices = ObtenerMejoresIndices(puntuaciones, 2);


    int padre1 = RandInt(0, 1);
    int padre2 = 1 - padre1;


    Vector3 nuevoVector;
    nuevoVector.x = (resultados[mejoresIndices[padre1]].speed + resultados[mejoresIndices[padre2]].speed) / 2.0f;
    nuevoVector.y = (resultados[mejoresIndices[padre1]].damage + resultados[mejoresIndices[padre2]].damage) / 2.0f;
    nuevoVector.z = (resultados[mejoresIndices[padre1]].lives + resultados[mejoresIndices[padre2]].lives) / 2.0f;


    nuevoVector.x = std::min(std::round(nuevoVector.x * 1000) / 1000, 6.0f);
    nuevoVector.y = std::min(std::round(nuevoVector.y * 1000) / 1000, 6.0f);
    nuevoVector.z = std::min(std::round(nuevoVector.z * 1000) / 1000, 6.0f);


    archivo << nuevoVector.x << " " << nuevoVector.y << " " << nuevoVector.z << "\n";

    archivo.close();
}

int Genetico::RandInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

Vector<size_t> Genetico::ObtenerMejoresIndices(const Vector<float>& promedios, int numMejores) {
    Vector<size_t> indices;
    for (size_t i = 0; i < promedios.getSize(); ++i) {
        indices.push_back(i);
    }

    for (size_t i = 0; i < promedios.getSize() - 1; ++i) {
        for (size_t j = i + 1; j < promedios.getSize(); ++j) {
            if (promedios[i] < promedios[j]) {
                std::swap(indices[i], indices[j]);
            }
        }
    }

    indices.resize(numMejores);
    return indices;
}

void Genetico::MutarVector(Vector3& vec) {
    vec.x += RandFloat(-0.1f, 0.1f);
    vec.y += RandFloat(-0.1f, 0.1f);
    vec.z += RandFloat(-0.1f, 0.1f);
}

float Genetico::RandFloat(float min, float max) {
    // Implementación del método RandFloat
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
