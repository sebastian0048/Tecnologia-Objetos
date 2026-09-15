#include <iostream>
#include "GestorEstudiantes.h"

using namespace std;

int main()
{
     GestorEstudiantes gestor;
     gestor.registrar("Ana", "Matematicas", 18.0f, 16.0f);
     gestor.registrar("Juan", "Historia", 10.0f, 8.0f);

     const Estudiante *mejor = gestor.obtenerConMayorNota();
     cout << "Estudiantes registrados: " << gestor.cantidad() << "\n";
     cout << "Promedio general: " << gestor.calcularPromedioGeneral() << "\n";
     cout << "Mejor estudiante: " << mejor->nombre << "\n";
     cout << "Busqueda de ID 1: "
          << (gestor.buscarPorId(1) != nullptr ? "correcta" : "incorrecta") << "\n";
     cout << "Nota final de Ana correcta: "
          << (abs(gestor.buscarPorId(1)->notaFinal - 17.0f) < 0.001f ? "si" : "no") << "\n";
     return 0;
}
