#include <iostream>
#include <string>

using namespace std;

class CuentaAhorro : public CuentaBancaria {
private:
    double tasaInteres;
    int limiteRetiros;
    int retirosRealizados;

public:
    CuentaAhorro(string numero, Cliente* titular, double saldo,
                 double tasaInteres, int limiteRetiros)
        : CuentaBancaria(numero, titular, saldo), tasaInteres(tasaInteres),
          limiteRetiros(limiteRetiros), retirosRealizados(0) {}

    bool retirar(double monto) override {
        if (monto <= 0 || retirosRealizados >= limiteRetiros || saldo - monto < 0) {
            return false;
        }
        saldo -= monto;
        ++retirosRealizados;
        return true;
    }

    double calcularBeneficio() override {
        return saldo * tasaInteres / 100.0;
    }

    void mostrarInformacion() override {
        cout << "[Ahorro] ";
        CuentaBancaria::mostrarInformacion();
        cout << " | Interes anual estimado: " << calcularBeneficio()
             << " | Retiros: " << retirosRealizados << '/' << limiteRetiros << '\n';
    }
};