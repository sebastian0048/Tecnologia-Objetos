#include "funciones.h"

using namespace std;

bool esNotaValida(float nota)
{
    return nota >= NOTA_MINIMA && nota <= NOTA_MAXIMA;
}

float calcularNotaFinal(float notaTeoria, float notaPractica)
{
    return (notaTeoria * 0.5f) + (notaPractica * 0.5f);
}

bool estaAprobado(const Estudiante &estudiante)
{
    return estudiante.notaFinal >= NOTA_APROBATORIA;
}

int buscarIndicePorId(const vector<Estudiante> &estudiantes, int id)
{
    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        if (estudiantes[i].id == id)
        {
            return i;
        }
    }
    return -1;
}
