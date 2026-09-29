#include "Persona.h"
#include <iostream>

using namespace std;

// Constructores

Persona::Persona() : id(0), nombre("") {}

Persona::Persona(int id, const string &nombre) : id(id), nombre(nombre) {}

// Destructor

Persona::~Persona() {}

// Getters

int Persona::getId() const
{
    return id;
}

string Persona::getNombre() const
{
    return nombre;
}

// Setters

void Persona::setId(int id)
{
    this->id = id;
}

void Persona::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Persona::mostrarDatos() const
{
    cout << "ID:     " << id << "\n";
    cout << "Nombre: " << nombre << "\n";
}
