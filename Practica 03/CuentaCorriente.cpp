#include <iostream>
#include <string>

using namespace std;

class CuentaCorriente : public CuentaBancaria {
private:
    double limiteSobregiro;
    double comisionMensual;

public:
    CuentaCorriente(string numero, Cliente* titular, double saldo,
                    double limiteSobregiro, double comisionMensual)
        : CuentaBancaria(numero, titular, saldo),
          limiteSobregiro(limiteSobregiro), comisionMensual(comisionMensual) {}

    bool retirar(double monto) override {
        if (monto <= 0 || saldo - monto < -limiteSobregiro) {
            return false;
        }
        saldo -= monto;
        return true;
    }

    double calcularBeneficio() override {
        return -comisionMensual;
    }

    void mostrarInformacion() override {
        cout << "[Corriente] ";
        CuentaBancaria::mostrarInformacion();
        cout << " | Sobregiro permitido: " << limiteSobregiro
             << " | Comision mensual: " << comisionMensual << '\n';
    }
};