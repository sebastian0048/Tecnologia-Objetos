#include <vector>
#include <string>
#include "Estudiante.h"

using namespace std;
class Curso
{
private:
    string codigo;
    string nombre;
    int capacidadMaxima;
    vector<Estudiante> estudiantes;

public:
    // Constructores
    Curso();

    Curso(const string &codigo, const string &nombre, int capacidadMaxima);

    // Getters

    string getCodigo() const;

    string getNombre() const;

    int getCapacidadMaxima() const;

    const vector<Estudiante> &getEstudiantes() const;

    // Setters

    void setCodigo(const string &codigo);

    void setNombre(const string &nombre);

    void setCapacidadMaxima(int capacidadMaxima);

    // Gestion de estudiantes

    void agregarEstudiante(const Estudiante &estudiante);

    Estudiante *buscarEstudiante(int id);

    void mostrarEstudiantes() const;

    float calcularPromedio() const;

    Estudiante *obtenerEstudianteConMayorNota();

    void mostrarInfoCurso() const;

    void mostrarAprobadosYDesaprobados() const;
};
