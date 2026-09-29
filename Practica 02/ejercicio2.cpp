#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. CLASE: Paciente
// ==========================================
class Paciente {
private:
    string nombre;
    int edad;
    float peso;

public:
    // Constructor
    Paciente(string _nombre, int _edad, float _peso) 
        : nombre(_nombre), edad(_edad), peso(_peso) {}

    // Getters y Setters
    void setPeso(float _peso) { peso = _peso; }
    float getPeso() const { return peso; }
    string getNombre() const { return nombre; }

    void mostrarDatos() const {
        cout << "Paciente: " << nombre << " | Edad: " << edad << " | Peso: " << peso << " kg\n";
    }
};

// ==========================================
// 2. CLASE: Medico
// ==========================================
class Medico {
private:
    string nombre;
    string especialidad;
    int añosExperiencia;

public:
    // Constructor
    Medico(string _nombre, string _especialidad, int _experiencia)
        : nombre(_nombre), especialidad(_especialidad), añosExperiencia(_experiencia) {}

    // Getters y Setters
    void setExperiencia(int _experiencia) { añosExperiencia = _experiencia; }
    int getExperiencia() const { return añosExperiencia; }

    void mostrarDatos() const {
        cout << "Medico: " << nombre << " | Especialidad: " << especialidad 
             << " | Experiencia: " << añosExperiencia << " años\n";
    }
};

// ==========================================
// 3. CLASE: CitaMedica
// ==========================================
class CitaMedica {
private:
    string codigoCita;
    string diagnostico;

public:
    // Constructor
    CitaMedica(string _codigo, string _diagnostico)
        : codigoCita(_codigo), diagnostico(_diagnostico) {}

    // Getters y Setters
    void setDiagnostico(string _diagnostico) { diagnostico = _diagnostico; }
    string getDiagnostico() const { return diagnostico; }

    void mostrarDatos() const {
        cout << "Cita [" << codigoCita << "] | Diagnostico actual: " << diagnostico << "\n";
    }
};

// ==========================================
// FUNCIONES EXTERNAS
// ==========================================

// 1. Recibe un objeto por VALOR (Se crea una copia, NO modifica el original)
void simularDietaValor(Paciente p, float reduccion) {
    p.setPeso(p.getPeso() - reduccion);
    cout << "   -> (Dentro de la funcion) Peso temporal proyectado: " << p.getPeso() << " kg\n";
}

// 2. Recibe un objeto por REFERENCIA (Modifica el objeto original directamente)
void actualizarExperienciaReferencia(Medico &m, int añosExtra) {
    m.setExperiencia(m.getExperiencia() + añosExtra);
}

// 3. Recibe un PUNTERO al objeto (Modifica el objeto original a traves de su direccion en memoria)
void registrarDiagnosticoPuntero(CitaMedica *c, string nuevoDiagnostico) {
    if (c != nullptr) {
        c->setDiagnostico(nuevoDiagnostico);
    }
}

// ==========================================
// FUNCION PRINCIPAL
// ==========================================
int main() {
    cout << "=== SISTEMA DE GESTION CLINICA ===\n\n";

    // Creacion dinamica de objetos usando 'new'
    Paciente* paciente1 = new Paciente("Carlos Mendoza", 45, 85.5f);
    Medico* medico1 = new Medico("Dra. Elena Rios", "Medicina General", 5);
    CitaMedica* cita1 = new CitaMedica("CM-2026-001", "Pendiente de evaluacion");

    // ---------------------------------------------------------
    // PRUEBA 1: Paso por Valor
    // ---------------------------------------------------------
    cout << "--- PRUEBA 1: Paso por Valor ---\n";
    cout << "ANTES: ";
    paciente1->mostrarDatos();
    
    // Al pasar el objeto desreferenciado (*paciente1), pasamos una copia
    simularDietaValor(*paciente1, 5.0f); 
    
    cout << "DESPUES: ";
    paciente1->mostrarDatos(); // El peso original no cambia
    cout << "\n";

    // ---------------------------------------------------------
    // PRUEBA 2: Paso por Referencia
    // ---------------------------------------------------------
    cout << "--- PRUEBA 2: Paso por Referencia ---\n";
    cout << "ANTES: ";
    medico1->mostrarDatos();
    
    actualizarExperienciaReferencia(*medico1, 2); 
    
    cout << "DESPUES: ";
    medico1->mostrarDatos(); // La experiencia original SI cambia
    cout << "\n";

    // ---------------------------------------------------------
    // PRUEBA 3: Paso por Puntero
    // ---------------------------------------------------------
    cout << "--- PRUEBA 3: Paso por Puntero ---\n";
    cout << "ANTES: ";
    cita1->mostrarDatos();
    
    registrarDiagnosticoPuntero(cita1, "Infeccion respiratoria leve - Recetar antibioticos"); 
    
    cout << "DESPUES: ";
    cita1->mostrarDatos(); // El diagnostico original SI cambia
    cout << "\n";

    // ---------------------------------------------------------
    // Liberacion de memoria
    // ---------------------------------------------------------
    delete paciente1;
    delete medico1;
    delete cita1;

    return 0;
}