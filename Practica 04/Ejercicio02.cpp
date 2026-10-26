// ejercicio2.cpp
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// =========================================================
// CLASE: Contacto
// =========================================================
class Contacto {
private:
    int id;
    string nombre;
    string telefono;
    string correo;

    // Metodo auxiliar privado para validar datos de entrada
    void validarDatos(int _id, const string &_nom, const string &_tel, const string &_cor) {
        if (_id <= 0) {
            throw invalid_argument("Error de entrada: El ID debe ser un numero positivo mayor a 0.");
        }
        if (_nom.empty()) {
            throw invalid_argument("Error de entrada: El nombre del contacto no puede estar vacio.");
        }
        if (_tel.length() != 9) {
            throw invalid_argument("Error de entrada: El telefono debe tener exactamente 9 digitos.");
        }
        for (char c : _tel) {
            if (!isdigit(c)) {
                throw invalid_argument("Error de entrada: El telefono solo debe contener numeros.");
            }
        }
        if (_cor.find('@') == string::npos) {
            throw invalid_argument("Error de entrada: El correo electronico debe contener un '@'.");
        }
    }

public:
    Contacto(int _id, string _nombre, string _telefono, string _correo) {
        validarDatos(_id, _nombre, _telefono, _correo);
        id = _id;
        nombre = _nombre;
        telefono = _telefono;
        correo = _correo;
    }

    // Getters
    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getTelefono() const { return telefono; }
    string getCorreo() const { return correo; }

    // Metodo para actualizar validando primero
    void actualizarDatos(string _nuevoNombre, string _nuevoTel, string _nuevoCorreo) {
        validarDatos(this->id, _nuevoNombre, _nuevoTel, _nuevoCorreo);
        nombre = _nuevoNombre;
        telefono = _nuevoTel;
        correo = _nuevoCorreo;
    }

    void mostrar() const {
        cout << "ID: [" << id << "] | Nombre: " << nombre 
             << " | Tel: " << telefono << " | Correo: " << correo << "\n";
    }
};

// =========================================================
// CLASE: GestorContacto
// =========================================================
class GestorContacto {
private:
    vector<Contacto> listaContactos;

public:
    // 1. Ingresar nuevo contacto
    void agregarContacto(int id, string nombre, string telefono, string correo) {
        // Validacion de procesamiento: verificar que no se repita el ID
        for (const auto &c : listaContactos) {
            if (c.getId() == id) {
                throw runtime_error("Error de procesamiento: Ya existe un contacto con el ID " + to_string(id) + ".");
            }
        }
        // Si los datos son invalidos, el constructor de Contacto lanzara invalid_argument
        Contacto nuevo(id, nombre, telefono, correo);
        listaContactos.push_back(nuevo);
        cout << "[OK] Contacto '" << nombre << "' agregado correctamente.\n";
    }

    // 2. Modificar contacto existente
    void modificarContacto(int id, string nuevoNombre, string nuevoTel, string nuevoCorreo) {
        if (listaContactos.empty()) {
            throw runtime_error("Error de procesamiento: La lista de contactos esta vacia.");
        }

        for (auto &c : listaContactos) {
            if (c.getId() == id) {
                c.actualizarDatos(nuevoNombre, nuevoTel, nuevoCorreo);
                cout << "[OK] Contacto con ID " << id << " modificado correctamente.\n";
                return;
            }
        }
        throw out_of_range("Error de busqueda: No se encontro ningun contacto con el ID " + to_string(id) + " para modificar.");
    }

    // 3. Eliminar contacto
    void eliminarContacto(int id) {
        if (listaContactos.empty()) {
            throw runtime_error("Error de procesamiento: No se puede eliminar porque la lista esta vacia.");
        }

        for (size_t i = 0; i < listaContactos.size(); i++) {
            if (listaContactos[i].getId() == id) {
                string nombreEliminado = listaContactos[i].getNombre();
                listaContactos.erase(listaContactos.begin() + i);
                cout << "[OK] Contacto '" << nombreEliminado << "' (ID " << id << ") eliminado.\n";
                return;
            }
        }
        throw out_of_range("Error de eliminacion: El contacto con ID " + to_string(id) + " no existe.");
    }

    // 4. Mostrar todos los contactos
    void mostrarContactos() const {
        if (listaContactos.empty()) {
            throw runtime_error("Aviso: Actualmente no hay contactos registrados en el gestor.");
        }
        cout << "\n--- LISTA DE CONTACTOS REGISTRADOS ---\n";
        for (const auto &c : listaContactos) {
            c.mostrar();
        }
        cout << "--------------------------------------\n";
    }
};

// =========================================================
// FUNCION PRINCIPAL (Pruebas y captura de Excepciones)
// =========================================================
int main() {
    cout << "=== EJERCICIO 2: GESTOR DE CONTACTOS Y EXCEPCIONES ===\n\n";
    GestorContacto gestor;

    // 1. Registro exitoso de contactos
    try {
        gestor.agregarContacto(1, "Johan Vilca", "987654321", "johan@unsa.edu.pe");
        gestor.agregarContacto(2, "Keneth Cutimbo", "912345678", "keneth@unsa.edu.pe");
        gestor.agregarContacto(3, "Dra. Elena Rios", "955443322", "elena.rios@clinica.com");
        gestor.mostrarContactos();
    } catch (const exception &e) {
        cout << "[EXCEPCION CAPTURADA] " << e.what() << "\n";
    }

    // 2. Prueba de Error al recibir datos (Telefono invalido y Correo sin @)
    cout << "\n--- Prueba de Excepcion al recibir datos invalidos ---\n";
    try {
        gestor.agregarContacto(4, "Pedro Perez", "12345", "pedro_correo_invalido.com");
    } catch (const invalid_argument &e) {
        cout << "[EXCEPCION CAPTURADA] " << e.what() << "\n";
    }

    // 3. Prueba de Error al procesar datos (ID duplicado)
    cout << "\n--- Prueba de Excepcion por ID duplicado ---\n";
    try {
        gestor.agregarContacto(1, "Usuario Clon", "999888777", "clon@correo.com");
    } catch (const runtime_error &e) {
        cout << "[EXCEPCION CAPTURADA] " << e.what() << "\n";
    }

    // 4. Modificacion exitosa y Eliminacion
    cout << "\n--- Prueba de Modificacion y Eliminacion ---\n";
    try {
        gestor.modificarContacto(2, "Keneth Sebastian", "999111222", "kcutimbo@unsa.edu.pe");
        gestor.eliminarContacto(3);
        gestor.mostrarContactos();
    } catch (const exception &e) {
        cout << "[EXCEPCION CAPTURADA] " << e.what() << "\n";
    }

    // 5. Prueba de Error al intentar eliminar un ID que no existe
    cout << "\n--- Prueba de Excepcion al eliminar contacto inexistente ---\n";
    try {
        gestor.eliminarContacto(99);
    } catch (const out_of_range &e) {
        cout << "[EXCEPCION CAPTURADA] " << e.what() << "\n";
    }

    return 0;
}
