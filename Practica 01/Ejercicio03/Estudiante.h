#include "Persona.h"
#include <string>
using namespace std;

class Estudiante : public Persona
{
private:
    float notaTeoria;
    float notaPractica;
    float notaFinal;
    bool aprobado;

    static const float NOTA_MINIMA;
    static const float NOTA_MAXIMA;
    static const float NOTA_APROBATORIA;

public:
    static int totalEstudiantesEvaluados;

    Estudiante();

    Estudiante(int id, const string &nombre,
               float notaTeoria, float notaPractica);

    // Getters

    string getCurso() const;

    float getNotaTeoria() const;

    float getNotaPractica() const;

    float getNotaFinal() const;

    // Setters

    void setCurso(const string &curso);

    void setNotaTeoria(float nota);

    void setNotaPractica(float nota);

    // Metodos

    void calcularNotaFinal();

    bool estaAprobado() const;

    void mostrarDatos() const override;

    static bool esNotaValida(float nota);
};
