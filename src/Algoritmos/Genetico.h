#ifndef GENETICO_H
#define GENETICO_H

#include <vector>
#include "../Enemy/Espectro.h"

class Genetico {
public:
    // Constructor que recibe un vector de referencias a Espectro
    Genetico(std::vector<Espectro>& espectros);

    // Método para seleccionar los dos mejores espectros y mutarlos
    std::vector<Vector3> seleccionarYMutar();

private:
    std::vector<Espectro>& espectros; // Referencia al vector de espectros

    // Método para realizar la mutación en un solo espectro
    Vector3 mutar(const Espectro& espectro);

    // Método para realizar la mutación combinando dos espectros
    Vector3 mutar(const Espectro& espectro1, const Espectro& espectro2);
};

#endif // GENETICO_H
