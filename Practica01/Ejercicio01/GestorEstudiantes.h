#include <vector>
#include "estudiante.h"

class GestorEstudiantes
{
private:
	std::vector<Estudiante> estudiantes;
	int siguienteId;

public:
	GestorEstudiantes();

	Estudiante *registrar(const std::string &nombre,
						  const std::string &curso,
						  float notaTeoria,
						  float notaPractica);
	const std::vector<Estudiante> &obtenerEstudiantes() const;
	Estudiante *buscarPorId(int id);
	const Estudiante *buscarPorId(int id) const;
	const Estudiante *obtenerConMayorNota() const;
	float calcularPromedioGeneral() const;
	std::size_t cantidad() const;
	int obtenerSiguienteId() const;
};
