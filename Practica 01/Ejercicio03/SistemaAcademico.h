#include <string>
#include <vector>
#include "Curso.h"

class SistemaAcademico
{
private:
  std::vector<Curso> cursos;
  int siguienteIdEstudiante;
  int siguienteIdCurso;

public:
  SistemaAcademico();

  Curso *registrarCurso(const std::string &nombre, int capacidadMaxima);
  Curso *obtenerCurso(std::size_t indice);
  const std::vector<Curso> &obtenerCursos() const;

  Estudiante *registrarEstudiante(std::size_t indiceCurso,
                                  const std::string &nombre,
                                  float notaTeoria,
                                  float notaPractica);
  Estudiante *buscarEstudiante(int id);
  bool modificarNotas(int id, float notaTeoria, float notaPractica);

  float calcularPromedioGeneral();
  const Estudiante *obtenerEstudianteConMayorNota();
  const Curso *obtenerCursoDelEstudiante(const Estudiante *estudiante);

  bool hayCursos() const;
  int obtenerSiguienteIdEstudiante() const;
  int obtenerSiguienteIdCurso() const;
};
