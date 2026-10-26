// ejercicio1.cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// =========================================================
// JERARQUIA PARA COVARIANZA Y CONTRAVARIANZA
// =========================================================
class RegistroClinico {
protected:
    string codigo;
public:
    RegistroClinico(string _cod) : codigo(_cod) {}
    virtual ~RegistroClinico() {}

    // Metodo Constante (const) e Inline
    inline string getCodigo() const { return codigo; }

    virtual void mostrar() const {
        cout << "[Registro Clinico General] Codigo: " << codigo << "\n";
    }

    // COVARIANZA: El metodo en la clase base retorna RegistroClinico*
    virtual RegistroClinico* clonar() const {
        return new RegistroClinico(*this);
    }
};

class RegistroEspecializado : public RegistroClinico {
private:
    string areaEspecialidad;
public:
    RegistroEspecializado(string _cod, string _area) 
        : RegistroClinico(_cod), areaEspecialidad(_area) {}

    void mostrar() const override {
        cout << "[Registro Especializado] Codigo: " << codigo 
             << " | Area: " << areaEspecialidad << "\n";
    }

    // COVARIANZA APLICADA: Sobrescribe el metodo retornando el tipo derivado (RegistroEspecializado*)
    RegistroEspecializado* clonar() const override {
        return new RegistroEspecializado(*this);
    }
};

// =========================================================
// CLASE PRINCIPAL PARA INLINE, FRIEND, CONST Y SOBRECARGA
// =========================================================
class HistorialMedico {
private:
    string paciente;
    string diagnosticoPrivado;
    float costoTratamiento;

public:
    HistorialMedico(string _pac, string _diag, float _costo)
        : paciente(_pac), diagnosticoPrivado(_diag), costoTratamiento(_costo) {}

    // 1. FUNCIONES INLINE Y 2. FUNCIONES CONSTANTES (const)
    inline string getPaciente() const { return paciente; }
    inline float getCosto() const { return costoTratamiento; }

    void mostrarResumen() const {
        cout << "Paciente: " << paciente << " | Costo: S/ " << costoTratamiento << "\n";
    }

    // 3. FUNCION FRIEND (Permite acceso externo controlado a atributos privados)
    friend void auditarHistorial(const HistorialMedico &h);

    // 4. SOBRECARGA DE OPERADORES (Fusiona dos historiales sumando costos y diagnosticos)
    HistorialMedico operator+(const HistorialMedico &otro) const {
        string nuevoDiag = this->diagnosticoPrivado + " + " + otro.diagnosticoPrivado;
        float nuevoCosto = this->costoTratamiento + otro.costoTratamiento;
        return HistorialMedico(this->paciente, nuevoDiag, nuevoCosto);
    }
};

// Implementacion de la funcion Friend
void auditarHistorial(const HistorialMedico &h) {
    cout << ">>> [AUDITORIA MEDICA - ACCESO FRIEND] <<<\n";
    cout << "    Paciente: " << h.paciente << "\n";
    cout << "    Diagnostico Reservado: " << h.diagnosticoPrivado << "\n";
    cout << "    Costo Registrado: S/ " << h.costoTratamiento << "\n";
}

int main() {
    cout << "=== EJERCICIO 1: CONCEPTOS AVANZADOS EN C++ ===\n\n";

    // Prueba de Inline, Const y Sobrecarga de Operadores
    HistorialMedico consulta1("Carlos Mendoza", "Gastritis Aguda", 120.50f);
    HistorialMedico consulta2("Carlos Mendoza", "Ecografia Abdominal", 180.00f);

    cout << "--- 1. Funciones Const e Inline ---\n";
    consulta1.mostrarResumen();
    consulta2.mostrarResumen();

    cout << "\n--- 2. Sobrecarga de Operador (+) ---\n";
    HistorialMedico historialTotal = consulta1 + consulta2;
    historialTotal.mostrarResumen();

    cout << "\n--- 3. Funcion Friend (Auditoria de atributos privados) ---\n";
    auditarHistorial(historialTotal);

    // 5. EXPRESIONES LAMBDA
    cout << "\n--- 4. Expresion Lambda (Filtrar costos mayores a S/ 150) ---\n";
    vector<HistorialMedico> lista = {
        consulta1, 
        consulta2, 
        HistorialMedico("Ana Torres", "Consulta General", 80.0f),
        HistorialMedico("Luis Gomez", "Tomografia", 450.0f)
    };

    float limite = 150.0f;
    for_each(lista.begin(), lista.end(), [limite](const HistorialMedico &h) {
        if (h.getCosto() > limite) {
            cout << "   -> [Filtro Lambda] " << h.getPaciente() 
                 << " supera el monto con S/ " << h.getCosto() << "\n";
        }
    });

    // 6. COVARIANZA
    cout << "\n--- 5. Covarianza en Clases Derivadas ---\n";
    RegistroEspecializado* regOriginal = new RegistroEspecializado("REG-2026-01", "Cardiologia");
    // Al clonar, devuelve directamente un RegistroEspecializado* sin necesitar casteo
    RegistroEspecializado* regClonado = regOriginal->clonar(); 
    regClonado->mostrar();

    // 7. CONTRAVARIANZA (En callbacks / punteros a funcion)
    cout << "\n--- 6. Contravarianza Funcional ---\n";
    // Funcion general que acepta la clase Base (RegistroClinico*)
    function<void(const RegistroClinico*)> validadorGeneral = [](const RegistroClinico* r) {
        cout << "   -> Validando en sistema general el registro: " << r->getCodigo() << "\n";
    };

    // Contravarianza: Un manejador específico para la clase Hija puede usar el validador de la clase Padre
    function<void(const RegistroEspecializado*)> validadorEspecializado = validadorGeneral;
    validadorEspecializado(regClonado);

    delete regOriginal;
    delete regClonado;

    return 0;
}
