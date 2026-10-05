#include <memory>
#include <vector>

using namespace std;

void Cliente::mostrarInformacion() {
    cout << "DNI: " << getDni() << " | Nombre: " << getNombre()
         << " | Telefono: " << telefono << " | Cuentas: ";
    if (cuentas.empty()) {
        cout << "ninguna";
    }
    for (size_t i = 0; i < cuentas.size(); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << cuentas[i]->getNumeroCuenta();
    }
    cout << '\n';
}

void CuentaBancaria::mostrarInformacion() {
    cout << "Cuenta: " << numeroCuenta << " | Titular: "
         << titular->getNombre() << " | Saldo: " << saldo;
}

class Banco {
private:
    vector<unique_ptr<Cliente>> clientes;
    vector<unique_ptr<CuentaBancaria>> cuentas;

public:
    Banco() = default;
    ~Banco() = default;

    Banco(Banco&) = delete;
    Banco& operator=(Banco&) = delete;

    bool registrarCliente(string dni, string nombre, string telefono) {
        if (dni.empty() || nombre.empty() || buscarCliente(dni) != NULL) {
            return false;
        }
        clientes.push_back(unique_ptr<Cliente>(new Cliente(dni, nombre, telefono)));
        return true;
    }

    bool agregarCuenta(unique_ptr<CuentaBancaria> cuenta) {
        if (cuenta == NULL || cuenta->getNumeroCuenta().empty() ||
            buscarCuenta(cuenta->getNumeroCuenta()) != NULL ||
            cuenta->getSaldo() < CuentaBancaria::SALDO_MINIMO) {
            return false;
        }

        bool titularRegistrado = false;
        for (size_t i = 0; i < clientes.size(); ++i) {
            if (clientes[i].get() == cuenta->getTitular()) {
                titularRegistrado = true;
            }
        }
        if (!titularRegistrado) {
            return false;
        }

        CuentaBancaria* cuentaRegistrada = cuenta.get();
        cuentas.push_back(move(cuenta));
        cuentaRegistrada->getTitular()->agregarCuenta(cuentaRegistrada);
        return true;
    }

    Cliente* buscarCliente(string dni) {
        for (size_t i = 0; i < clientes.size(); ++i) {
            if (clientes[i]->getDni() == dni) {
                return clientes[i].get();
            }
        }
        return NULL;
    }

    CuentaBancaria* buscarCuenta(string numero) {
        for (size_t i = 0; i < cuentas.size(); ++i) {
            if (cuentas[i]->getNumeroCuenta() == numero) {
                return cuentas[i].get();
            }
        }
        return NULL;
    }

    void mostrarClientes() {
        if (clientes.empty()) {
            cout << "No hay clientes.\n";
        }
        for (size_t i = 0; i < clientes.size(); ++i) {
            clientes[i]->mostrarInformacion();
        }
    }

    void mostrarCuentas() {
        if (cuentas.empty()) {
            cout << "No hay cuentas.\n";
        }
        for (size_t i = 0; i < cuentas.size(); ++i) {
            cuentas[i]->mostrarInformacion();
        }
    }

    bool realizarDeposito(string numero, double monto) {
        CuentaBancaria* cuenta = buscarCuenta(numero);
        return cuenta != NULL && cuenta->depositar(monto);
    }

    bool realizarRetiro(string numero, double monto) {
        CuentaBancaria* cuenta = buscarCuenta(numero);
        return cuenta != NULL && cuenta->retirar(monto);
    }
};