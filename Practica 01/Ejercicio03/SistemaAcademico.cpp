#include "SistemaAcademico.h"

SistemaAcademico::SistemaAcademico() : siguienteIdEstudiante(1), siguienteIdCurso(1)
{
}

Curso *SistemaAcademico::registrarCurso(const std::string &nombre, int capacidadMaxima)
{
    if (nombre.empty() || capacidadMaxima <= 0)
    {
        return nullptr;
    }

    std::string codigo = "CUR" + std::to_string(siguienteIdCurso);
    cursos.emplace_back(codigo, nombre, capacidadMaxima);
    ++siguienteIdCurso;
    return &cursos.back();
}

Curso *SistemaAcademico::obtenerCurso(std::size_t indice)
{
    if (indice >= cursos.size())
    {
        return nullptr;
    }
    return &cursos[indice];
}

const std::vector<Curso> &SistemaAcademico::obtenerCursos() const
{
    return cursos;
}

Estudiante *SistemaAcademico::registrarEstudiante(std::size_t indiceCurso,
                                                  const std::string &nombre,
                                                  float notaTeoria,
                                                  float notaPractica)
{
    Curso *curso = obtenerCurso(indiceCurso);
    if (curso == nullptr || nombre.empty() ||
        !Estudiante::esNotaValida(notaTeoria) ||
        !Estudiante::esNotaValida(notaPractica) ||
        curso->getEstudiantes().size() >= static_cast<std::size_t>(curso->getCapacidadMaxima()))
    {
        return nullptr;
    }

    curso->agregarEstudiante(Estudiante(siguienteIdEstudiante, nombre,
                                        notaTeoria, notaPractica));
    return curso->buscarEstudiante(siguienteIdEstudiante++);
}

Estudiante *SistemaAcademico::buscarEstudiante(int id)
{
    for (Curso &curso : cursos)
    {
        Estudiante *estudiante = curso.buscarEstudiante(id);
        if (estudiante != nullptr)
        {
            return estudiante;
        }
    }
    return nullptr;
}

bool SistemaAcademico::modificarNotas(int id, float notaTeoria, float notaPractica)
{
    Estudiante *estudiante = buscarEstudiante(id);
    if (estudiante == nullptr || !Estudiante::esNotaValida(notaTeoria) ||
        !Estudiante::esNotaValida(notaPractica))
    {
        return false;
    }

    estudiante->setNotaTeoria(notaTeoria);
    estudiante->setNotaPractica(notaPractica);
    return true;
}

float SistemaAcademico::calcularPromedioGeneral()
{
    float suma = 0.0f;
    std::size_t cantidad = 0;

    for (Curso &curso : cursos)
    {
        for (const Estudiante &estudiante : curso.getEstudiantes())
        {
            suma += estudiante.getNotaFinal();
            ++cantidad;
        }
    }

    return cantidad == 0 ? 0.0f : suma / static_cast<float>(cantidad);
}

const Estudiante *SistemaAcademico::obtenerEstudianteConMayorNota()
{
    const Estudiante *mejor = nullptr;
    for (Curso &curso : cursos)
    {
        const Estudiante *mejorCurso = curso.obtenerEstudianteConMayorNota();
        if (mejorCurso != nullptr &&
            (mejor == nullptr || mejorCurso->getNotaFinal() > mejor->getNotaFinal()))
        {
            mejor = mejorCurso;
        }
    }
    return mejor;
}

const Curso *SistemaAcademico::obtenerCursoDelEstudiante(const Estudiante *estudiante)
{
    if (estudiante == nullptr)
    {
        return nullptr;
    }

    for (Curso &curso : cursos)
    {
        if (curso.buscarEstudiante(estudiante->getId()) != nullptr)
        {
            return &curso;
        }
    }
    return nullptr;
}

bool SistemaAcademico::hayCursos() const
{
    return !cursos.empty();
}

int SistemaAcademico::obtenerSiguienteIdEstudiante() const
{
    return siguienteIdEstudiante;
}

int SistemaAcademico::obtenerSiguienteIdCurso() const
{
    return siguienteIdCurso;
}
