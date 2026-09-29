#include "Cliente.cpp"
#include "CuentaBancaria.cpp"
#include "CuentaAhorro.cpp"
#include "CuentaCorriente.cpp"
#include "CuentaPlazoFijo.cpp"
#include "Banco.cpp"

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

    Cliente clienteNoRegistrado("99999999", "Cliente Prueba", "900000001");
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

    return 0;
}