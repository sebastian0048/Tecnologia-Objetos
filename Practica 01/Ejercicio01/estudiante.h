#include <string>
using namespace std;
const float NOTA_MINIMA = 0.0f;
const float NOTA_MAXIMA = 20.0f;
const float NOTA_APROBATORIA = 11.0f;

struct Estudiante
{
    int id;
    string nombre;
    string curso;
    float notaTeoria;
    float notaPractica;
    float notaFinal;
};
