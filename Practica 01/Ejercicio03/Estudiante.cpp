#include "Estudiante.h"
#include <iostream>

using namespace std;

int Estudiante::totalEstudiantesEvaluados = 0;
const float Estudiante::NOTA_MINIMA = 0.0f;
const float Estudiante::NOTA_MAXIMA = 20.0f;
const float Estudiante::NOTA_APROBATORIA = 11.0f;

Estudiante::Estudiante()
    : Persona(), notaTeoria(0.0f), notaPractica(0.0f),
      notaFinal(0.0f), aprobado(false) {}

Estudiante::Estudiante(int id, const string &nombre,
                       float notaTeoria, float notaPractica)
    : Persona(id, nombre), notaTeoria(notaTeoria),
      notaPractica(notaPractica), notaFinal(0.0f), aprobado(false)
{
    calcularNotaFinal();
}

// Getters

float Estudiante::getNotaTeoria() const
{
    return notaTeoria;
}

float Estudiante::getNotaPractica() const
{
    return notaPractica;
}

float Estudiante::getNotaFinal() const
{
    return notaFinal;
}

// Setters

void Estudiante::setNotaTeoria(float nota)
{
    if (esNotaValida(nota))
    {
        this->notaTeoria = nota;
        calcularNotaFinal(); // Recalcula la nota final
    }
}

void Estudiante::setNotaPractica(float nota)
{
    if (esNotaValida(nota))
    {
        this->notaPractica = nota;
        calcularNotaFinal(); // Recalcula la nota final
    }
}

void Estudiante::calcularNotaFinal()
{
    // Formula: 50% teoria + 50% practica
    notaFinal = (notaTeoria * 0.5f) + (notaPractica * 0.5f);
    aprobado = (notaFinal >= NOTA_APROBATORIA);

    // Incrementar contador de estudiantes evaluados
    totalEstudiantesEvaluados++;
}

bool Estudiante::estaAprobado() const
{
    return aprobado;
}

bool Estudiante::esNotaValida(float nota)
{
    return nota >= NOTA_MINIMA && nota <= NOTA_MAXIMA;
}

void Estudiante::mostrarDatos() const
{
    Persona::mostrarDatos();

    cout << "Nota Teoria:  " << notaTeoria << "\n";
    cout << "Nota Practica: " << notaPractica << "\n";
    cout << "Nota Final:   " << notaFinal << "\n";
    cout << "Estado:       " << (aprobado ? "Aprobado" : "Desaprobado") << "\n";
}
