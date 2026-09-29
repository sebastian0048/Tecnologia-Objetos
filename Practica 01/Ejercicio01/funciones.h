#include <vector>

using namespace std;
struct Estudiante;

float calcularNotaFinal(float notaTeoria, float notaPractica);

bool esNotaValida(float nota);

bool estaAprobado(const Estudiante &estudiante);

int buscarIndicePorId(const vector<Estudiante> &estudiantes, int id);
