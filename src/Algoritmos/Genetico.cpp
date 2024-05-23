#include <vector>
#include <algorithm>
#include <random>

#include "../Enemy/Espectro.h"

class Genetico {
public:
    Genetico(std::vector<Espectro>& espectros) : espectros(espectros) {}

    std::vector<Vector3> seleccionarYMutar() {
        std::vector<float> promedios;

        // Calcular el promedio de muerto, ataque y duracion para cada espectro
        for (const auto& espectro : espectros) {
            float promedio = (espectro.muerto + espectro.ataques + espectro.duracion) / 3.0f;
            promedios.push_back(promedio);
        }

        // Ordenar los espectros según sus promedios
        std::vector<size_t> indices(promedios.size());
        std::iota(indices.begin(), indices.end(), 0); // Genera una secuencia de índices
        std::sort(indices.begin(), indices.end(), [&promedios](size_t i1, size_t i2) {
            return promedios[i1] > promedios[i2]; // Orden descendente
        });

        // Seleccionar los dos mejores espectros
        const Espectro& mejor1 = espectros[indices[0]];
        const Espectro& mejor2 = espectros[indices[1]];

        // Realizar la mutación
        Vector3 nuevo1 = mutar(mejor1);
        Vector3 nuevo2 = mutar(mejor2);
        Vector3 nuevo3 = mutar(mejor1, mejor2);

        return { nuevo1, nuevo2, nuevo3 };
    }

private:
    std::vector<Espectro>& espectros;

    Vector3 mutar(const Espectro& espectro) {
        // Realizar mutación en un solo espectro
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(-0.1, 0.1); // Mutación pequeña

        float new_x = espectro.speed + espectro.speed * dist(gen);
        float new_y = espectro.lives + espectro.lives * dist(gen);
        float new_z = espectro.damage + espectro.damage * dist(gen);

        return { new_x, new_y, new_z };
    }

    Vector3 mutar(const Espectro& espectro1, const Espectro& espectro2) {
        // Realizar mutación combinando dos espectros
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(-0.1, 0.1); // Mutación pequeña

        float new_x = (espectro1.speed + espectro2.speed) / 2.0f + ((espectro1.speed + espectro2.speed) / 2.0f) * dist(gen);
        float new_y = (espectro1.lives + espectro2.lives) / 2.0f + ((espectro1.lives + espectro2.lives) / 2.0f) * dist(gen);
        float new_z = (espectro1.damage + espectro2.damage) / 2.0f + ((espectro1.damage + espectro2.damage) / 2.0f) * dist(gen);

        return { new_x, new_y, new_z };
    }
};