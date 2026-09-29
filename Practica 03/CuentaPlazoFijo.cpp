#include <iostream>
#include <string>

using namespace std;

class CuentaPlazoFijo : public CuentaBancaria {
private:
    int plazoMeses;
    double tasaGanancia;

public:
    CuentaPlazoFijo(string numero, Cliente* titular, double saldo,
                    int plazoMeses, double tasaGanancia)
        : CuentaBancaria(numero, titular, saldo), plazoMeses(plazoMeses),
          tasaGanancia(tasaGanancia) {}

    bool retirar(double monto) override {
        (void)monto;
        return false;
    }

    double calcularBeneficio() override {
        return saldo * tasaGanancia / 100.0 * plazoMeses / 12.0;
    }

    void mostrarInformacion() override {
        cout << "[Plazo fijo] ";
        CuentaBancaria::mostrarInformacion();
        cout << " | Plazo: " << plazoMeses << " meses"
             << " | Ganancia estimada: " << calcularBeneficio() << '\n';
    }
};