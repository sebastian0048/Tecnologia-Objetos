#include "Cliente.cpp"
#include "CuentaBancaria.cpp"
#include "CuentaAhorro.cpp"
#include "CuentaCorriente.cpp"
#include "CuentaPlazoFijo.cpp"
#include "Banco.cpp"

void ejecutarMenu(Banco& banco) {
    int opcion;

    do {
        cout << "\nMenu del sistema bancario\n"
             << "1. Registrar cliente\n"
             << "2. Buscar cliente\n"
             << "3. Crear cuenta\n"
             << "4. Buscar cuenta\n"
             << "5. Realizar deposito\n"
             << "6. Realizar retiro\n"
             << "7. Mostrar clientes\n"
             << "8. Mostrar cuentas\n"
             << "9. Consultar beneficio de una cuenta\n"
             << "0. Salir\n"
             << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "\nEntrada invalida o finalizada. Cerrando el menu.\n";
            return;
        }

        string dni;
        string numero;
        double monto;

        switch (opcion) {
        case 1: {
            string nombre;
            string telefono;
            cout << "DNI: ";
            if (!(cin >> dni)) {
                cout << "\nNo se pudo leer el DNI. Cerrando el menu.\n";
                return;
            }
            cout << "Nombre completo: ";
            cin >> ws;
            if (!getline(cin, nombre)) {
                cout << "\nNo se pudo leer el nombre. Cerrando el menu.\n";
                return;
            }
            cout << "Telefono: ";
            if (!(cin >> telefono)) {
                cout << "\nNo se pudo leer el telefono. Cerrando el menu.\n";
                return;
            }
            cout << (banco.registrarCliente(dni, nombre, telefono)
                         ? "Cliente registrado correctamente.\n"
                         : "No se pudo registrar el cliente (datos vacios o DNI duplicado).\n");
            break;
        }

        case 2: {
            cout << "DNI del cliente: ";
            if (!(cin >> dni)) {
                cout << "\nNo se pudo leer el DNI. Cerrando el menu.\n";
                return;
            }
            Cliente* cliente = banco.buscarCliente(dni);
            if (cliente == NULL) {
                cout << "No se encontro el cliente.\n";
            } else {
                cout << "Cliente encontrado: " << cliente->getNombre()
                     << " | DNI: " << cliente->getDni() << '\n';
            }
            break;
        }

        case 3: {
            int tipo;
            cout << "Numero de cuenta: ";
            if (!(cin >> numero)) {
                cout << "\nNo se pudo leer el numero. Cerrando el menu.\n";
                return;
            }
            cout << "DNI del titular: ";
            if (!(cin >> dni)) {
                cout << "\nNo se pudo leer el DNI. Cerrando el menu.\n";
                return;
            }
            Cliente* titular = banco.buscarCliente(dni);
            if (titular == NULL) {
                cout << "No se puede crear la cuenta: el cliente no esta registrado.\n";
                break;
            }
            cout << "Saldo inicial: ";
            if (!(cin >> monto)) {
                cout << "\nMonto invalido. Cerrando el menu.\n";
                return;
            }
            cout << "Tipo (1=Ahorro, 2=Corriente, 3=Plazo fijo): ";
            if (!(cin >> tipo)) {
                cout << "\nTipo invalido. Cerrando el menu.\n";
                return;
            }

            unique_ptr<CuentaBancaria> cuenta;
            if (tipo == 1) {
                double tasa;
                int limiteRetiros;
                cout << "Tasa de interes (%): ";
                if (!(cin >> tasa)) {
                    cout << "\nTasa invalida. Cerrando el menu.\n";
                    return;
                }
                cout << "Limite de retiros: ";
                if (!(cin >> limiteRetiros)) {
                    cout << "\nLimite invalido. Cerrando el menu.\n";
                    return;
                }
                cuenta.reset(new CuentaAhorro(numero, titular, monto, tasa, limiteRetiros));
            } else if (tipo == 2) {
                double sobregiro;
                double comision;
                cout << "Limite de sobregiro: ";
                if (!(cin >> sobregiro)) {
                    cout << "\nLimite invalido. Cerrando el menu.\n";
                    return;
                }
                cout << "Comision mensual: ";
                if (!(cin >> comision)) {
                    cout << "\nComision invalida. Cerrando el menu.\n";
                    return;
                }
                cuenta.reset(new CuentaCorriente(numero, titular, monto, sobregiro, comision));
            } else if (tipo == 3) {
                int plazo;
                double tasa;
                cout << "Plazo en meses: ";
                if (!(cin >> plazo)) {
                    cout << "\nPlazo invalido. Cerrando el menu.\n";
                    return;
                }
                cout << "Tasa de ganancia (%): ";
                if (!(cin >> tasa)) {
                    cout << "\nTasa invalida. Cerrando el menu.\n";
                    return;
                }
                cuenta.reset(new CuentaPlazoFijo(numero, titular, monto, plazo, tasa));
            } else {
                cout << "Tipo de cuenta no valido.\n";
                break;
            }

            cout << (banco.agregarCuenta(move(cuenta))
                         ? "Cuenta creada correctamente.\n"
                         : "No se pudo crear la cuenta (numero duplicado o saldo inicial invalido).\n");
            break;
        }

        case 4: {
            cout << "Numero de cuenta: ";
            if (!(cin >> numero)) {
                cout << "\nNo se pudo leer el numero. Cerrando el menu.\n";
                return;
            }
            CuentaBancaria* cuenta = banco.buscarCuenta(numero);
            if (cuenta == NULL) {
                cout << "No se encontro la cuenta.\n";
            } else {
                cuenta->mostrarInformacion();
                cout << '\n';
            }
            break;
        }

        case 5:
        case 6:
            cout << "Numero de cuenta: ";
            if (!(cin >> numero)) {
                cout << "\nNo se pudo leer el numero. Cerrando el menu.\n";
                return;
            }
            cout << "Monto: ";
            if (!(cin >> monto)) {
                cout << "\nMonto invalido. Cerrando el menu.\n";
                return;
            }
            if (opcion == 5) {
                cout << (banco.realizarDeposito(numero, monto)
                             ? "Deposito realizado correctamente.\n"
                             : "No se pudo realizar el deposito.\n");
            } else {
                cout << (banco.realizarRetiro(numero, monto)
                             ? "Retiro realizado correctamente.\n"
                             : "No se pudo realizar el retiro (saldo, limite o cuenta no valida).\n");
            }
            break;

        case 7:
            banco.mostrarClientes();
            break;

        case 8:
            banco.mostrarCuentas();
            cout << "Total de cuentas: " << CuentaBancaria::getTotalCuentas() << '\n';
            break;

        case 9: {
            cout << "Numero de cuenta: ";
            if (!(cin >> numero)) {
                cout << "\nNo se pudo leer el numero. Cerrando el menu.\n";
                return;
            }
            CuentaBancaria* cuenta = banco.buscarCuenta(numero);
            if (cuenta == NULL) {
                cout << "No se encontro la cuenta.\n";
            } else {
                cout << "Beneficio estimado: " << cuenta->calcularBeneficio() << '\n';
            }
            break;
        }

        case 0:
            cout << "Menu finalizado.\n";
            break;

        default:
            cout << "Opcion no valida.\n";
            break;
        }
    } while (opcion != 0);
}

int main() {
    Banco banco;

    cout << "Pruebas del sistema bancario\n\n";

    cout << "Registro de clientes\n";
    cout << "Registrando a Ana Perez\n";
    banco.registrarCliente("12345678", "Ana Perez", "987654321");
    cout << "Registrando a Bob Torres\n";
    banco.registrarCliente("87654321", "Bob Torres", "912345678");
    cout << "Intentando registrar a Raquel Garcia con el DNI 12345678\n";
    banco.registrarCliente("12345678", "Raquel García", "900000000");

    cout << "\nBusqueda de clientes\n";
    Cliente* ana = banco.buscarCliente("12345678");
    Cliente* bob = banco.buscarCliente("87654321");
    banco.buscarCliente("00000000");
    cout << "Se buscaron los clientes con DNI 12345678 87654321 y 00000000\n\n";

    cout << "Creacion de cuentas\n";
    cout << "Creando una cuenta de ahorro para Ana\n";
    banco.agregarCuenta(unique_ptr<CuentaBancaria>(
        new CuentaAhorro("CTA001", ana, 1500.0, 4.5, 2)
    ));
    cout << "Creando una cuenta corriente para Ana\n";
    banco.agregarCuenta(unique_ptr<CuentaBancaria>(
        new CuentaCorriente("CTA002", ana, 800.0, 500.0, 10.0)
    ));
    cout << "Creando una cuenta a plazo fijo para Bob\n";
    banco.agregarCuenta(unique_ptr<CuentaBancaria>(
        new CuentaPlazoFijo("CTA003", bob, 2000.0, 12, 6.0)
    ));

    cout << "Intentando crear otra cuenta con el numero CTA001\n";
    banco.agregarCuenta(unique_ptr<CuentaBancaria>(
        new CuentaAhorro("CTA001", ana, 100.0, 2.0, 1)
    ));

    Cliente clienteNoRegistrado("99999999", "Pedro Lopez", "900000001");
    cout << "Intentando crear una cuenta para un cliente no registrado\n";
    banco.agregarCuenta(unique_ptr<CuentaBancaria>(
        new CuentaCorriente("CTA004", &clienteNoRegistrado, 100.0, 50.0, 5.0)
    ));

    cout << "Intentando crear una cuenta con saldo inicial negativo\n\n";
    banco.agregarCuenta(unique_ptr<CuentaBancaria>(
        new CuentaAhorro("CTA005", ana, -10.0, 2.0, 3)
    ));

    cout << "Busqueda de cuentas\n";
    CuentaBancaria* ahorro = banco.buscarCuenta("CTA001");
    CuentaBancaria* corriente = banco.buscarCuenta("CTA002");
    CuentaBancaria* plazoFijo = banco.buscarCuenta("CTA003");
    banco.buscarCuenta("CTA999");
    cout << "Se buscaron las cuentas CTA001 CTA002 CTA003 y CTA999\n\n";

    cout << "Depositos\n";
    cout << "Depositando 200 en CTA001\n";
    banco.realizarDeposito("CTA001", 200.0);
    cout << "Intentando depositar 0 en CTA001\n";
    banco.realizarDeposito("CTA001", 0.0);
    cout << "Intentando depositar en la cuenta inexistente CTA999\n\n";
    banco.realizarDeposito("CTA999", 100.0);

    cout << "Retiros por tipo de cuenta\n";
    cout << "Retirando 100 y 200 de CTA001 dentro de su limite\n";
    banco.realizarRetiro("CTA001", 100.0);
    banco.realizarRetiro("CTA001", 200.0);
    cout << "Intentando un tercer retiro de 50 de CTA001\n";
    banco.realizarRetiro("CTA001", 50.0);
    cout << "Retirando 1000 de CTA002 usando parte del sobregiro\n";
    banco.realizarRetiro("CTA002", 1000.0);
    cout << "Intentando retirar 400 adicionales de CTA002\n";
    banco.realizarRetiro("CTA002", 400.0);
    cout << "Intentando retirar 100 de CTA003 cuenta a plazo fijo\n";
    banco.realizarRetiro("CTA003", 100.0);
    cout << "Intentando retirar de la cuenta inexistente CTA999\n\n";
    banco.realizarRetiro("CTA999", 100.0);

    cout << "Beneficios\n";
    cout << "Beneficio estimado de ahorro "
         << ahorro->calcularBeneficio() << '\n';
    cout << "Beneficio de cuenta corriente "
         << corriente->calcularBeneficio() << '\n';
    cout << "Beneficio estimado de plazo fijo "
         << plazoFijo->calcularBeneficio() << '\n';
    cout << "Cantidad total de cuentas creadas "
         << CuentaBancaria::getTotalCuentas() << "\n\n";

    cout << "Informacion de clientes\n";
    banco.mostrarClientes();
    cout << "\nInformacion de cuentas\n";
    banco.mostrarCuentas();

    ejecutarMenu(banco);
    return 0;
}
