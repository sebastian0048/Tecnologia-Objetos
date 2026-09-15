#include <vector>
#include "estudiante.h"

using namespace std;
float calcularNotaFinal(float notaTeoria, float notaPractica);

bool esNotaValida(float nota);

bool estaAprobado(const Estudiante &estudiante);

int buscarIndicePorId(const vector<Estudiante> &estudiantes, int id);
