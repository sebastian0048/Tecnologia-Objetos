#include <iostream>
#include "SistemaAcademico.h"

using namespace std;

int main()
{
    SistemaAcademico sistema;

    sistema.registrarCurso("Programacion", 5);
    sistema.registrarCurso("Bases de Datos", 5);
    sistema.registrarCurso("Redes", 5);

    sistema.registrarEstudiante(0, "Ana Torres", 18.0f, 17.0f);
    sistema.registrarEstudiante(0, "Bruno Perez", 15.0f, 16.0f);
    sistema.registrarEstudiante(0, "Carla Ruiz", 10.0f, 9.0f);
    sistema.registrarEstudiante(0, "Diego Soto", 14.0f, 13.0f);

    sistema.registrarEstudiante(1, "Elena Diaz", 19.0f, 18.0f);
    sistema.registrarEstudiante(1, "Fabian Leon", 11.0f, 12.0f);
    sistema.registrarEstudiante(1, "Gabriela Cruz", 8.0f, 10.0f);

    sistema.registrarEstudiante(2, "Hugo Ramos", 16.0f, 15.0f);
    sistema.registrarEstudiante(2, "Irene Vega", 13.0f, 14.0f);
    sistema.registrarEstudiante(2, "Jorge Flores", 9.0f, 8.0f);


    cout << "\nSistema Academico\n";
    cout << "\nCursos registrados\n";

    const vector<Curso> &cursos = sistema.obtenerCursos();

    cout << "Cantidad de cursos: " << cursos.size() << "\n";

    for (size_t i = 0; i < cursos.size(); i++)
    {
        cout << "\nCurso numero " << i + 1 << "\n";

        cursos[i].mostrarInfoCurso();
        cursos[i].mostrarEstudiantes();

        cout << "\nPromedio del curso: "
             << cursos[i].calcularPromedio() << "\n";

        cursos[i].mostrarAprobadosYDesaprobados();
    }

    cout << "\nResumen general\n";

    cout << "Promedio general: "
         << sistema.calcularPromedioGeneral() << "\n";

    const Estudiante *mejorEstudiante =
        sistema.obtenerEstudianteConMayorNota();

    cout << "\nEstudiante con mayor nota\n";

    if (mejorEstudiante != nullptr)
    {
        cout << "Identificador: "
             << mejorEstudiante->getId() << "\n";

        cout << "Nombre: "
             << mejorEstudiante->getNombre() << "\n";

        cout << "Nota de teoria: "
             << mejorEstudiante->getNotaTeoria() << "\n";

        cout << "Nota de practica: "
             << mejorEstudiante->getNotaPractica() << "\n";

        cout << "Nota final: "
             << mejorEstudiante->getNotaFinal() << "\n";

        const Curso *curso =
            sistema.obtenerCursoDelEstudiante(mejorEstudiante);

        if (curso != nullptr)
        {
            cout << "Curso: " << curso->getNombre() << "\n";
        }
    }
    else
    {
        cout << "No hay estudiantes registrados\n";
    }

    int idBuscado = 8;

    cout << "\nBusqueda de estudiante\n";

    Estudiante *estudianteEncontrado =
        sistema.buscarEstudiante(idBuscado);

    if (estudianteEncontrado != nullptr)
    {
        cout << "Estudiante encontrado\n";
        estudianteEncontrado->mostrarDatos();
    }
    else
    {
        cout << "El estudiante no fue encontrado\n";
    }

    int idModificar = 4;

    cout << "\nModificacion de notas\n";

    Estudiante *estudiante =
        sistema.buscarEstudiante(idModificar);

    if (estudiante != nullptr)
    {
        cout << "Datos anteriores\n";
        estudiante->mostrarDatos();

        bool resultado =
            sistema.modificarNotas(idModificar, 16.0f, 18.0f);

        if (resultado)
        {
            cout << "\nLas notas fueron modificadas\n";
            cout << "Datos actuales\n";

            estudiante->mostrarDatos();
        }
        else
        {
            cout << "No se pudieron modificar las notas\n";
        }
    }
    else
    {
        cout << "El estudiante no existe\n";
    }

    Curso *programacion = sistema.obtenerCurso(0);

    if (programacion != nullptr)
    {
        cout << "\nDatos actuales del curso Programacion\n";

        programacion->mostrarEstudiantes();

        cout << "\nPromedio actual del curso: "
             << programacion->calcularPromedio() << "\n";
    }

    return 0;
}