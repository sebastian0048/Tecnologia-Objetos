#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Persona {
protected:
    string id;
    string nombre;

public:
    Persona(string id, string nombre) {
        this->id = id;
        this->nombre = nombre;
    }
    
    string getId() const { return id; }
    string getNombre() const { return nombre; }
};

class Estudiante : public Persona {
private:
    string curso;
    float notaTeoria;
    float notaPractica;
    float notaFinal;
    bool evaluado;
    
    static int totalEstudiantesEvaluados; 

public:
    Estudiante(string id, string nombre, string curso, float teoria, float practica) 
        : Persona(id, nombre) {
        this->curso = curso;
        this->notaTeoria = (teoria >= 0 && teoria <= 20) ? teoria : 0;
        this->notaPractica = (practica >= 0 && practica <= 20) ? practica : 0;
        this->notaFinal = 0.0;
        this->evaluado = false;
    }

    string getCurso() const { return curso; }
    float getNotaTeoria() const { return notaTeoria; }
    float getNotaPractica() const { return notaPractica; }
    float getNotaFinal() const { return notaFinal; }
    bool isEvaluado() const { return evaluado; }

    void setNotaFinal(float nota) { this->notaFinal = nota; }
    void setEvaluado(bool estado) { this->evaluado = estado; }

    static int getTotalEvaluados() { return totalEstudiantesEvaluados; }
    static void incrementarEvaluados() { totalEstudiantesEvaluados++; }
};

int Estudiante::totalEstudiantesEvaluados = 0;

class CalculadoraNotas {
public:
    static float calcularPromedio(float teoria, float practica) {
        return (teoria + practica) / 2.0f;
    }
};

class GestorColegio {
private:
    queue<Estudiante> colaPendientes;
    stack<Estudiante> historialRecientes;
    vector<Estudiante> registroTotal; 

public:
    void encolarExamen(Estudiante nuevoEstudiante) {
        colaPendientes.push(nuevoEstudiante);
    }

    bool procesarSiguiente() {
        if (colaPendientes.empty()) return false;

        Estudiante actual = colaPendientes.front();
        colaPendientes.pop();

        float promedio = CalculadoraNotas::calcularPromedio(actual.getNotaTeoria(), actual.getNotaPractica());
        actual.setNotaFinal(promedio);
        actual.setEvaluado(true);
        
        Estudiante::incrementarEvaluados();

        historialRecientes.push(actual);
        registroTotal.push_back(actual);
        
        return true;
    }

    Estudiante* buscarEstudiante(string idBusqueda) {
        for (auto& ex : registroTotal) {
            if (ex.getId() == idBusqueda) {
                return &ex; 
            }
        }
        return nullptr; 
    }

    vector<Estudiante> obtenerRegistroCompleto() const {
        return registroTotal;
    }
    
    int getExamenesPendientes() const {
        return colaPendientes.size();
    }
};


int main() {

    GestorColegio gestor;

    Estudiante e1("E001", "Juan Perez", "Programacion", 15, 18);
    Estudiante e2("E002", "Maria Lopez", "Programacion", 17, 16);
    Estudiante e3("E003", "Carlos Torres", "Programacion", 12, 14);
    Estudiante e4("E004", "Ana Garcia", "Programacion", 19, 18);

    gestor.encolarExamen(e1);
    gestor.encolarExamen(e2);
    gestor.encolarExamen(e3);
    gestor.encolarExamen(e4);

    cout << "Examenes pendientes: ";
    cout << gestor.getExamenesPendientes() << endl;

    while (gestor.procesarSiguiente()) {
        cout << "Examen procesado." << endl;
    }

    cout << "\nTotal de estudiantes evaluados: ";
    cout << Estudiante::getTotalEvaluados() << endl;

    cout << "Examenes pendientes: ";
    cout << gestor.getExamenesPendientes() << endl;

    vector<Estudiante> registro = gestor.obtenerRegistroCompleto();

    cout << "\nRegistro de estudiantes\n";

    for (int i = 0; i < registro.size(); i++) {

        cout << "\nID: " << registro[i].getId() << endl;
        cout << "Nombre: " << registro[i].getNombre() << endl;
        cout << "Curso: " << registro[i].getCurso() << endl;
        cout << "Nota teoria: " << registro[i].getNotaTeoria() << endl;
        cout << "Nota practica: " << registro[i].getNotaPractica() << endl;
        cout << "Nota final: " << registro[i].getNotaFinal() << endl;
    }

    string idBusqueda;

    cout << "\nIngrese ID del estudiante: ";
    cin >> idBusqueda;

    Estudiante* encontrado = gestor.buscarEstudiante(idBusqueda);

    if (encontrado != nullptr) {

        cout << "\nEstudiante encontrado\n";
        cout << "ID: " << encontrado->getId() << endl;
        cout << "Nombre: " << encontrado->getNombre() << endl;
        cout << "Curso: " << encontrado->getCurso() << endl;
        cout << "Nota final: " << encontrado->getNotaFinal() << endl;

    } else {

        cout << "\nEstudiante no encontrado\n";
    }

    return 0;
}
