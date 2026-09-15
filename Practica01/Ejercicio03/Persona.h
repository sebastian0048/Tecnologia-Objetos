#include <string>

class Persona
{
protected:
    int id;
    std::string nombre;

public:
    Persona();

    Persona(int id, const std::string &nombre);

    virtual ~Persona();

    // ---------- Getters ----------

    int getId() const;

    std::string getNombre() const;

    // ---------- Setters ----------

    void setId(int id);

    void setNombre(const std::string &nombre);

    virtual void mostrarDatos() const;
};
