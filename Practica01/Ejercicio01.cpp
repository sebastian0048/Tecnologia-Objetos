#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

//Esto es la estruutrs 
struct Alumno{
    string codigoEstudiante;
    float notaTeoria;
    float notaPractica;
    float notaFinal;
    bool evaluado;
};

class GestorColegio {// crear otras clases para el colegio y sus funciones
private:
    queue<Alumno> colaPendientes;
    stack<Alumno> historialRecientes;
    vector<Alumno> registroTotal; 

public:
    // 1. GESTIÓN DE COLAS
    void recibirExamen(string codigo, float teoria, float practica) {// Crear un constructor de examen de alumno 
        Alumno nuevoAlumno = {codigo, teoria, practica, 0.0, false};
        colaPendientes.push(nuevoAlumno);
        cout << "Examen de " << codigo << " recibido en cola." << endl;
    }

    // 2. Aqui calculamos su promedio y guardamos y actualizamos la  PILAS 
    void calificarSiguiente() {
        if (colaPendientes.empty()) {
            cout << "No hay examenes pendientes." << endl;
            return;
        }

        Alumno actual = colaPendientes.front();
        colaPendientes.pop();

        float suma = actual.notaTeoria + actual.notaPractica;//separar esto en otra clase para que sea mas limpio y ordenado
        actual.notaFinal = suma / 2.0; 
        actual.evaluado = true;

        cout << "Calificado: " << actual.codigoEstudiante << " | Nota Final: " << actual.notaFinal;
        
       
        if(actual.notaFinal < 20) {
            cout << " (Le faltaron " << 20.0 - actual.notaFinal << " puntos para la nota maxima)";
        }
        cout << endl;

        // Guardar en pila y en registro
        historialRecientes.push(actual);
        registroTotal.push_back(actual);
    }

    // 3. BUSCADOR INTEGRADO
    void buscarEstudiante(string codigoBusqueda) {// Mejorar el metodo de busqueda de estudainte 
        bool encontrado = false;
        for (const auto& ex : registroTotal) {
            if (ex.codigoEstudiante == codigoBusqueda) {
                cout << "\nRESULTADO DE BUSQUEDA: Estudiante " << ex.codigoEstudiante 
                     << " tiene " << ex.notaFinal << endl;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) cout << "\nEstudiante " << codigoBusqueda << " no encontrado." << endl;
    }
};

int main() {
    GestorColegio miSistema;

    // Ingresan a la cola
    miSistema.recibirExamen("2025001", 14.0, 16.0);
    miSistema.recibirExamen("2025002", 10.0, 12.0);

    cout << "\n--- PROCESANDO EXAMENES ---" << endl;
    miSistema.calificarSiguiente(); // Califica al 2025001
    miSistema.calificarSiguiente(); // Califica al 2025002

    cout << "\n--- BUSCADOR ---" << endl;
    miSistema.buscarEstudiante("2025001");

    return 0;
}