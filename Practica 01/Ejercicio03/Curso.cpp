#include "Curso.h"
#include <iostream>

using namespace std;


Curso::Curso() : codigo(""), nombre(""), capacidadMaxima(0) {}

Curso::Curso(const string &codigo, const string &nombre, int capacidadMaxima)
    : codigo(codigo), nombre(nombre), capacidadMaxima(capacidadMaxima) {}

// Getters
string Curso::getCodigo() const
{
    return codigo;
}

string Curso::getNombre() const
{
    return nombre;
}

int Curso::getCapacidadMaxima() const
{
    return capacidadMaxima;
}

const vector<Estudiante> &Curso::getEstudiantes() const
{
    return estudiantes;
}

// Setters
void Curso::setCodigo(const string &codigo)
{
    this->codigo = codigo;
}

void Curso::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Curso::setCapacidadMaxima(int capacidadMaxima)
{
    this->capacidadMaxima = capacidadMaxima;
}

// Gestion de estudiantes
void Curso::agregarEstudiante(const Estudiante &estudiante)
{
    estudiantes.push_back(estudiante);
}

Estudiante *Curso::buscarEstudiante(int id)
{
    for (auto &est : estudiantes)
    {
        if (est.getId() == id)
        {
            return &est;
        }
    }
    return nullptr;
}

void Curso::mostrarEstudiantes() const
{
    cout << "\nEstudiantes del curso: " << nombre << "\n\n";

    if (estudiantes.empty())
    {
        cout << "No hay estudiantes registrados en este curso.\n";
        return;
    }

    for (const auto &est : estudiantes)
    {
        cout << "ID: " << est.getId() << endl;
        cout << "Nombre: " << est.getNombre() << endl;
        cout << "Teoria: " << est.getNotaTeoria() << endl;
        cout << "Practica: " << est.getNotaPractica() << endl;
        cout << "Final: " << est.getNotaFinal() << endl;
        cout << "Estado: " << (est.estaAprobado() ? "Aprobado" : "Desaprobado") << "\n";
    }

    cout << "\nTotal de estudiantes: " << estudiantes.size() << "\n";
}

float Curso::calcularPromedio() const
{
    if (estudiantes.empty())
    {
        return 0.0f;
    }

    float suma = 0.0f;
    for (const auto &est : estudiantes)
    {
        suma += est.getNotaFinal();
    }

    return suma / estudiantes.size();
}

Estudiante *Curso::obtenerEstudianteConMayorNota()
{
    if (estudiantes.empty())
    {
        return nullptr;
    }

    Estudiante *mejor = &estudiantes[0];
    for (auto &est : estudiantes)
    {
        if (est.getNotaFinal() > mejor->getNotaFinal())
        {
            mejor = &est;
        }
    }
    return mejor;
}

void Curso::mostrarInfoCurso() const
{
    cout << "\nInformacion del curso\n";
    cout << "Codigo:   " << codigo << "\n";
    cout << "Nombre:   " << nombre << "\n";
    cout << "Estudiantes inscritos: " << estudiantes.size() << "\n";
}

void Curso::mostrarAprobadosYDesaprobados() const
{
    cout << "\nAprobados y desaprobados - " << nombre << "\n\n";

    if (estudiantes.empty())
    {
        cout << "No hay estudiantes registrados en este curso.\n";
        return;
    }

    cout << "ESTUDIANTES APROBADOS:\n";

    bool hayAprobados = false;
    for (const auto &est : estudiantes)
    {
        if (est.estaAprobado())
        {
            cout << "  " << est.getNombre() << " (ID: " << est.getId()
                 << ") - Nota: " << est.getNotaFinal() << "\n";
            hayAprobados = true;
        }
    }
    if (!hayAprobados)
    {
        cout << "  Ninguno\n";
    }

    cout << "\nESTUDIANTES DESAPROBADOS:\n";

    bool hayDesaprobados = false;
    for (const auto &est : estudiantes)
    {
        if (!est.estaAprobado())
        {
            cout << "  " << est.getNombre() << " (ID: " << est.getId()
                 << ") - Nota: " << est.getNotaFinal() << "\n";
            hayDesaprobados = true;
        }
    }
    if (!hayDesaprobados)
    {
        cout << "  Ninguno\n";
    }
}
