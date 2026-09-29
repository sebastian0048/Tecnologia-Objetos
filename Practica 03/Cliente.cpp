#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CuentaBancaria;

class Cliente {
private:
    string dni;
    string nombre;
    string telefono;
    vector<CuentaBancaria*> cuentas;

public:
    Cliente(string dni, string nombre, string telefono)
        : dni(dni), nombre(nombre), telefono(telefono) {}

    ~Cliente() = default;

    Cliente(Cliente&) = delete;
    Cliente& operator=(Cliente&) = delete;

    string getDni() {
        return dni;
    }

    string getNombre() {
        return nombre;
    }

    void agregarCuenta(CuentaBancaria* cuenta) {
        cuentas.push_back(cuenta);
    }

    void mostrarInformacion();
};