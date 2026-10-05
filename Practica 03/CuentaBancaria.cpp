#include <string>

using namespace std;

class Cliente;

class CuentaBancaria {
private:
    string numeroCuenta;
    Cliente* titular;

protected:
    double saldo;

private:
    static int& contadorCuentas() {
        static int total = 0;
        return total;
    }

public:
    static const double SALDO_MINIMO;

    CuentaBancaria(string numeroCuenta, Cliente* titular, double saldoInicial)
        : numeroCuenta(numeroCuenta), titular(titular), saldo(saldoInicial) {
        ++contadorCuentas();
    }

    virtual ~CuentaBancaria() {
        --contadorCuentas();
    }

    CuentaBancaria(CuentaBancaria&) = delete;
    CuentaBancaria& operator=(CuentaBancaria&) = delete;

    string getNumeroCuenta() {
        return numeroCuenta;
    }

    Cliente* getTitular() {
        return titular;
    }

    double getSaldo() {
        return saldo;
    }

    static int getTotalCuentas() {
        return contadorCuentas();
    }

    virtual bool depositar(double monto) {
        if (monto <= 0) {
            return false;
        }
        saldo += monto;
        return true;
    }

    virtual bool retirar(double monto) = 0;
    virtual double calcularBeneficio() = 0;
    virtual void mostrarInformacion();
};

const double CuentaBancaria::SALDO_MINIMO = 0.0;