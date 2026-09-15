#include "GestorEstudiantes.h"
#include "funciones.h"

GestorEstudiantes::GestorEstudiantes() : siguienteId(1)
{
}

Estudiante *GestorEstudiantes::registrar(const std::string &nombre,
                                         const std::string &curso,
                                         float notaTeoria,
                                         float notaPractica)
{
  if (nombre.empty() || curso.empty() || !esNotaValida(notaTeoria) ||
      !esNotaValida(notaPractica))
  {
    return nullptr;
  }

  Estudiante estudiante;
  estudiante.id = siguienteId++;
  estudiante.nombre = nombre;
  estudiante.curso = curso;
  estudiante.notaTeoria = notaTeoria;
  estudiante.notaPractica = notaPractica;
  estudiante.notaFinal = calcularNotaFinal(notaTeoria, notaPractica);
  estudiantes.push_back(estudiante);
  return &estudiantes.back();
}

const std::vector<Estudiante> &GestorEstudiantes::obtenerEstudiantes() const
{
  return estudiantes;
}

Estudiante *GestorEstudiantes::buscarPorId(int id)
{
  int indice = buscarIndicePorId(estudiantes, id);
  return indice < 0 ? nullptr : &estudiantes[static_cast<std::size_t>(indice)];
}

const Estudiante *GestorEstudiantes::buscarPorId(int id) const
{
  int indice = buscarIndicePorId(estudiantes, id);
  return indice < 0 ? nullptr : &estudiantes[static_cast<std::size_t>(indice)];
}

const Estudiante *GestorEstudiantes::obtenerConMayorNota() const
{
  if (estudiantes.empty())
  {
    return nullptr;
  }

  const Estudiante *mejor = &estudiantes.front();
  for (const Estudiante &estudiante : estudiantes)
  {
    if (estudiante.notaFinal > mejor->notaFinal)
    {
      mejor = &estudiante;
    }
  }
  return mejor;
}

float GestorEstudiantes::calcularPromedioGeneral() const
{
  if (estudiantes.empty())
  {
    return 0.0f;
  }

  float suma = 0.0f;
  for (const Estudiante &estudiante : estudiantes)
  {
    suma += estudiante.notaFinal;
  }
  return suma / static_cast<float>(estudiantes.size());
}

std::size_t GestorEstudiantes::cantidad() const
{
  return estudiantes.size();
}

int GestorEstudiantes::obtenerSiguienteId() const
{
  return siguienteId;
}
