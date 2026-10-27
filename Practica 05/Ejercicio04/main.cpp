#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

// Valida los datos y construye una fecha con la biblioteca chrono.
sys_seconds crearFecha(int anio, int mes, int dia, int hora = 0) {
    if (anio < 1 || anio > 9999 || mes < 1 || mes > 12 || dia < 1 || dia > 31
        || hora < 0 || hora > 23) throw invalid_argument("Fecha u hora invalida.");
    year_month_day fecha = year{anio} / mes / dia;
    if (!fecha.ok()) throw invalid_argument("Dia invalido para el mes indicado.");
    return sys_days{fecha} + hours{hora};
}

class Cliente {
private:
    int id;
    string nombre;
    string correo;
    string telefono;
public:
    Cliente(int id, const string& nombre, const string& correo, const string& telefono)
        : id(id), nombre(nombre), correo(correo), telefono(telefono) {
        if (id <= 0 || nombre.empty() || correo.empty() || telefono.empty())
            throw invalid_argument("Datos de cliente invalidos.");
    }
    int getId() const { return id; }
    const string& getNombre() const { return nombre; }
    const string& getCorreo() const { return correo; }
    const string& getTelefono() const { return telefono; }
};

// ISP: los servicios son capacidades independientes de la clase Habitacion.
class ServicioLimpieza {
public:
    virtual ~ServicioLimpieza() {}
    virtual void solicitarLimpieza() const = 0;
};
class ServicioComida {
public:
    virtual ~ServicioComida() {}
    virtual void solicitarComida(const string& plato) const = 0;
};
class ServicioLavanderia {
public:
    virtual ~ServicioLavanderia() {}
    virtual void solicitarLavanderia(int prendas) const = 0;
};

class GestorDisponibilidadHabitacion;

class Habitacion {
private:
    int numero;
    int capacidad;
    double precioNoche;
    GestorDisponibilidadHabitacion& gestor;
    bool ocupada;
    bool sucia;
public:
    Habitacion(int numero, int capacidad, double precioNoche, GestorDisponibilidadHabitacion& gestor)
        : numero(numero), capacidad(capacidad), precioNoche(precioNoche), gestor(gestor), ocupada(false), sucia(false) {
        if (numero <= 0 || capacidad <= 0 || precioNoche <= 0)
            throw invalid_argument("Datos de habitacion invalidos.");
    }
    virtual ~Habitacion() {}
    virtual string getTipo() const = 0;
    int getNumero() const { return numero; }
    int getCapacidad() const { return capacidad; }
    double getPrecioNoche() const { return precioNoche; }
    double calcularPrecio(const sys_seconds& entrada, const sys_seconds& salida) const {
        seconds duracion = salida - entrada;
        if (duracion <= seconds{0} || duracion % days{1} != seconds{0})
            throw invalid_argument("La estancia debe tener noches completas de 24 horas.");
        return precioNoche * (duracion / days{1});
    }
    // SRP: la consulta de disponibilidad se delega al gestor de reservas.
    bool estaDisponible(const sys_seconds& entrada, const sys_seconds& salida) const;
    bool estaOcupada() const { return ocupada; }
    bool necesitaLimpieza() const { return sucia; }
    // LSP: las operaciones de ocupacion, salida y limpieza tienen condiciones comunes.
    void ocupar() {
        if (ocupada || sucia) throw runtime_error("La habitacion esta ocupada o requiere limpieza.");
        ocupada = true;
    }
    // El check-out deja la habitacion pendiente de limpieza antes de ocuparla de nuevo.
    void liberar() {
        if (!ocupada) throw runtime_error("La habitacion no esta ocupada.");
        ocupada = false;
        sucia = true;
    }
    void limpiar() {
        if (ocupada) throw runtime_error("La limpieza de salida requiere una habitacion desocupada.");
        sucia = false;
    }
};

class HabitacionIndividual : public Habitacion, public ServicioLimpieza {
public:
    HabitacionIndividual(int numero, GestorDisponibilidadHabitacion& gestor)
        : Habitacion(numero, 1, 120, gestor) {}
    string getTipo() const override { return "Individual"; }
    void solicitarLimpieza() const override {
        cout << "Limpieza solicitada para habitacion " << getNumero() << ".\n";
    }
};
class HabitacionDoble : public Habitacion, public ServicioLimpieza, public ServicioComida {
public:
    HabitacionDoble(int numero, GestorDisponibilidadHabitacion& gestor)
        : Habitacion(numero, 2, 200, gestor) {}
    string getTipo() const override { return "Doble"; }
    void solicitarLimpieza() const override {
        cout << "Limpieza solicitada para habitacion " << getNumero() << ".\n";
    }
    void solicitarComida(const string& plato) const override {
        if (plato.empty()) throw invalid_argument("Debe indicar un plato.");
        cout << "Comida para habitacion " << getNumero() << ": " << plato << ".\n";
    }
};
class HabitacionSuite : public Habitacion, public ServicioLimpieza,
                        public ServicioComida, public ServicioLavanderia {
public:
    HabitacionSuite(int numero, GestorDisponibilidadHabitacion& gestor)
        : Habitacion(numero, 4, 450, gestor) {}
    string getTipo() const override { return "Suite"; }
    void solicitarLimpieza() const override {
        cout << "Limpieza solicitada para habitacion " << getNumero() << ".\n";
    }
    void solicitarComida(const string& plato) const override {
        if (plato.empty()) throw invalid_argument("Debe indicar un plato.");
        cout << "Comida para habitacion " << getNumero() << ": " << plato << ".\n";
    }
    void solicitarLavanderia(int prendas) const override {
        if (prendas <= 0) throw invalid_argument("Indique una cantidad positiva de prendas.");
        cout << "Lavanderia para habitacion " << getNumero() << ": " << prendas << " prenda(s).\n";
    }
};

// OCP: la reserva consulta una politica intercambiable para decidir y calcular la cancelacion.
class Reserva;
class PoliticaCancelacion {
public:
    virtual ~PoliticaCancelacion() {}
    virtual bool puedeCancelar(const Reserva& reserva, const sys_seconds& ahora) const = 0;
    virtual double calcularPenalizacion(const Reserva& reserva) const = 0;
};

class Reserva {
private:
    int id;
    const Cliente* cliente;
    Habitacion* habitacion;
    sys_seconds creacion;
    sys_seconds entrada;
    sys_seconds salida;
    const PoliticaCancelacion* politica;
    double total;
    double penalizacion;
    string estado;
    sys_seconds fechaMovimiento;
public:
    // Cliente, habitacion y politica son objetos externos que deben existir mientras se usa la reserva.
    Reserva(int id, const Cliente& cliente, Habitacion& habitacion, const sys_seconds& creacion,
            const sys_seconds& entrada, const sys_seconds& salida, double total, const PoliticaCancelacion& politica)
        : id(id), cliente(&cliente), habitacion(&habitacion), creacion(creacion), entrada(entrada),
          salida(salida), politica(&politica), total(total), penalizacion(0),
          estado("Confirmada"), fechaMovimiento(creacion) {
        if (id <= 0 || (entrada < creacion) || entrada >= salida || total < 0)
            throw invalid_argument("Datos de reserva invalidos.");
    }
    int getId() const { return id; }
    const Cliente& getCliente() const { return *cliente; }
    const Habitacion& getHabitacion() const { return *habitacion; }
    const sys_seconds& getEntrada() const { return entrada; }
    const sys_seconds& getSalida() const { return salida; }
    const sys_seconds& getFechaMovimiento() const { return fechaMovimiento; }
    double getTotal() const { return total; }
    double getPenalizacion() const { return penalizacion; }
    const string& getEstado() const { return estado; }
    double cancelar(const sys_seconds& ahora) {
        if (estado != "Confirmada") throw runtime_error("Solo se cancelan reservas confirmadas.");
        if ((ahora < creacion)) throw invalid_argument("Cancelacion anterior a la creacion.");
        if (!politica->puedeCancelar(*this, ahora)) throw runtime_error("La politica impide cancelar.");
        penalizacion = politica->calcularPenalizacion(*this);
        estado = "Cancelada";
        fechaMovimiento = ahora;
        return penalizacion;
    }
    void realizarCheckIn(const sys_seconds& ahora) {
        if (estado != "Confirmada" || (ahora < entrada) || ahora >= salida)
            throw runtime_error("El check-in requiere una reserva confirmada dentro de su periodo.");
        habitacion->ocupar();
        estado = "En curso";
        fechaMovimiento = ahora;
    }
    void realizarCheckOut(const sys_seconds& ahora) {
        // El check-out conserva el cobro de la estancia completa y debe realizarse dentro del periodo reservado.
        if (estado != "En curso" || (ahora < fechaMovimiento) || (salida < ahora))
            throw runtime_error("Check-out fuera del periodo de la estancia.");
        habitacion->liberar();
        estado = "Finalizada";
        fechaMovimiento = ahora;
    }
};

class PoliticaCancelacionFlexible : public PoliticaCancelacion {
public:
    bool puedeCancelar(const Reserva& reserva, const sys_seconds& ahora) const override {
        return reserva.getEntrada() - ahora >= hours{24};
    }
    double calcularPenalizacion(const Reserva&) const override { return 0; }
};
class PoliticaCancelacionModerada : public PoliticaCancelacion {
public:
    bool puedeCancelar(const Reserva& reserva, const sys_seconds& ahora) const override {
        return reserva.getEntrada() - ahora >= hours{72};
    }
    double calcularPenalizacion(const Reserva& reserva) const override { return reserva.getTotal() * 0.5; }
};
class PoliticaCancelacionEstricta : public PoliticaCancelacion {
public:
    bool puedeCancelar(const Reserva&, const sys_seconds&) const override { return false; }
    double calcularPenalizacion(const Reserva&) const override { return 0; }
};

class GestorDisponibilidadHabitacion {
private:
    vector<Reserva> reservas;
public:
    const vector<Reserva>& getReservas() const { return reservas; }
    bool estaDisponible(const Habitacion& habitacion, const sys_seconds& entrada, const sys_seconds& salida) const {
        // Los periodos [entrada, salida) permiten otra reserva justo al terminar la anterior.
        if (entrada >= salida) throw invalid_argument("Periodo de reserva invalido.");
        for (const Reserva& reserva : reservas) {
            if (reserva.getHabitacion().getNumero() == habitacion.getNumero()
                && reserva.getEstado() != "Cancelada" && (reserva.getEntrada() < salida)
                && (entrada < reserva.getSalida())) return false;
        }
        return true;
    }
    void registrar(const Reserva& reserva) {
        for (const Reserva& anterior : reservas)
            if (anterior.getId() == reserva.getId()) throw invalid_argument("ID de reserva duplicado.");
        if (!estaDisponible(reserva.getHabitacion(), reserva.getEntrada(), reserva.getSalida()))
            throw runtime_error("La habitacion ya tiene una reserva en esas fechas.");
        reservas.push_back(reserva);
    }
    Reserva& buscar(int id) {
        for (Reserva& reserva : reservas)
            if (reserva.getId() == id) return reserva;
        throw out_of_range("Reserva inexistente.");
    }
};

bool Habitacion::estaDisponible(const sys_seconds& entrada, const sys_seconds& salida) const {
    return gestor.estaDisponible(*this, entrada, salida);
}

class ControladorReservas {
private:
    GestorDisponibilidadHabitacion& gestor;
public:
    ControladorReservas(GestorDisponibilidadHabitacion& gestor) : gestor(gestor) {}
    void crearReserva(int id, const Cliente& cliente, Habitacion& habitacion, int personas,
                      const sys_seconds& creacion, const sys_seconds& entrada, const sys_seconds& salida,
                      const PoliticaCancelacion& politica) const {
        if (personas <= 0 || personas > habitacion.getCapacidad()) throw invalid_argument("Capacidad excedida.");
        if (!habitacion.estaDisponible(entrada, salida))
            throw runtime_error("La habitacion ya tiene una reserva en esas fechas.");
        double total = habitacion.calcularPrecio(entrada, salida);
        Reserva nueva(id, cliente, habitacion, creacion, entrada, salida, total, politica);
        gestor.registrar(nueva);
        cout << "Habitacion " << habitacion.getNumero() << " (" << habitacion.getTipo() << "), total S/ " << total << '\n';
    }
    void cancelarReserva(int id, const sys_seconds& ahora) const {
        Reserva& reserva = gestor.buscar(id);
        double penalizacion = reserva.cancelar(ahora);
        cout << "Penalizacion: S/ " << penalizacion << ". Reembolso: S/ " << reserva.getTotal() - penalizacion << '\n';
        cout << "Reserva " << id << ": " << reserva.getEstado() << '\n';
    }
    void realizarCheckIn(int id, const sys_seconds& ahora) const {
        Reserva& reserva = gestor.buscar(id);
        reserva.realizarCheckIn(ahora);
        cout << "Reserva " << id << ": " << reserva.getEstado() << '\n';
    }
    void realizarCheckOut(int id, const sys_seconds& ahora) const {
        Reserva& reserva = gestor.buscar(id);
        reserva.realizarCheckOut(ahora);
        cout << "Reserva " << id << ": " << reserva.getEstado() << '\n';
    }
};

class ControladorServicios {
public:
    // Consulta comida y lavanderia por sus interfaces; PersonalLimpieza coordina la limpieza.
    void solicitarServicios(const Habitacion& habitacion) const {
        const ServicioComida* comida = dynamic_cast<const ServicioComida*>(&habitacion);
        const ServicioLavanderia* lavanderia = dynamic_cast<const ServicioLavanderia*>(&habitacion);
        if (comida) comida->solicitarComida("Sopa de verduras");
        if (lavanderia) lavanderia->solicitarLavanderia(3);
        if (!comida && !lavanderia)
            cout << "Habitacion " << habitacion.getNumero() << ": sin comida ni lavanderia.\n";
    }
};

// Cada trabajador conserva sus tareas pendientes; completarlas limpia la habitacion y retira la tarea.
class PersonalLimpieza {
private:
    string nombre;
    vector<int> habitaciones;
public:
    PersonalLimpieza(const string& nombre) : nombre(nombre) {
        if (nombre.empty()) throw invalid_argument("Indique el nombre del personal.");
    }
    const string& getNombre() const { return nombre; }
    int getCargaTrabajo() const {
        int total = 0;
        for (int numero : habitaciones) {
            if (numero > 0) total++;
        }
        return total;
    }
    void asignar(const Habitacion& habitacion) {
        const ServicioLimpieza* servicio = dynamic_cast<const ServicioLimpieza*>(&habitacion);
        if (!servicio || habitacion.estaOcupada() || !habitacion.necesitaLimpieza())
            throw runtime_error("La habitacion no esta pendiente de limpieza de salida.");
        for (int numero : habitaciones)
            if (numero == habitacion.getNumero()) throw runtime_error("La tarea ya fue asignada.");
        habitaciones.push_back(habitacion.getNumero());
        servicio->solicitarLimpieza();
    }
    void completar(Habitacion& habitacion) {
        bool encontrada = false;
        vector<int> pendientes;
        for (int numero : habitaciones) {
            if (numero == habitacion.getNumero()) encontrada = true;
            else pendientes.push_back(numero);
        }
        if (!encontrada) throw runtime_error("La tarea no pertenece a este trabajador.");
        habitacion.limpiar();
        habitaciones = pendientes;
        cout << nombre << " completo la limpieza de habitacion " << habitacion.getNumero() << ".\n";
    }
};

// SRP: esta clase genera los informes y consulta el historial de reservas.
class GeneradorInformes {
public:
    void mostrarHistorial(const Cliente& cliente, const vector<Reserva>& reservas) const {
        cout << "Historial de " << cliente.getNombre() << ":\n";
        for (const Reserva& reserva : reservas)
            if (reserva.getCliente().getId() == cliente.getId())
                cout << "Reserva " << reserva.getId() << ": " << reserva.getEstado() << ", S/ " << reserva.getTotal() << '\n';
    }
    // Mide tiempo reservado, incluidas reservas confirmadas; no mide presencia fisica real.
    double calcularOcupacion(const string& tipo, const vector<Habitacion*>& habitaciones,
                            const vector<Reserva>& reservas, const sys_seconds& inicio, const sys_seconds& fin) const {
        seconds duracionPeriodo = fin - inicio;
        if (duracionPeriodo <= seconds{0}) throw invalid_argument("Periodo de informe invalido.");
        int cantidad = 0;
        for (const Habitacion* habitacion : habitaciones)
            if (habitacion->getTipo() == tipo) cantidad++;
        if (cantidad == 0) return 0;
        seconds tiempoReservado{0};
        for (const Reserva& reserva : reservas) {
            if (reserva.getHabitacion().getTipo() != tipo || reserva.getEstado() == "Cancelada") continue;
            sys_seconds desde = reserva.getEntrada();
            sys_seconds hasta = reserva.getSalida();
            if (desde < inicio) desde = inicio;
            if (hasta > fin) hasta = fin;
            if (desde < hasta) tiempoReservado += hasta - desde;
        }
        return tiempoReservado.count() * 100.0 / (double(duracionPeriodo.count()) * cantidad);
    }
    double calcularIngresos(const vector<Reserva>& reservas, const sys_seconds& inicio, const sys_seconds& fin) const {
        if (inicio >= fin) throw invalid_argument("Periodo de informe invalido.");
        double ingresos = 0;
        // La estancia se contabiliza al finalizar; la penalizacion, al cancelar.
        for (const Reserva& reserva : reservas) {
            const sys_seconds& movimiento = reserva.getFechaMovimiento();
            if (movimiento >= inicio && (movimiento < fin)) {
                if (reserva.getEstado() == "Finalizada") ingresos += reserva.getTotal();
                if (reserva.getEstado() == "Cancelada") ingresos += reserva.getPenalizacion();
            }
        }
        return ingresos;
    }
};

int main() {
    try {
        Cliente ana(1, "Ana Perez", "ana@example.com", "999111222");
        Cliente luis(2, "Luis Torres", "luis@example.com", "999333444");
        GestorDisponibilidadHabitacion gestor;
        HabitacionIndividual individual(101, gestor);
        HabitacionDoble doble(201, gestor);
        HabitacionSuite suite(301, gestor);
        vector<Habitacion*> habitaciones{&individual, &doble, &suite};
        PoliticaCancelacionFlexible flexible;
        PoliticaCancelacionModerada moderada;
        PoliticaCancelacionEstricta estricta;
        const PoliticaCancelacion* politicas[] = {&flexible, &moderada, &estricta};
        cout << "Politica de cancelacion: 1. Flexible, 2. Moderada, 3. Estricta\nSeleccione: ";
        int opcion;
        if (!(cin >> opcion) || opcion < 1 || opcion > 3)
            throw invalid_argument("Seleccione un numero entre 1 y 3.");
        const PoliticaCancelacion& seleccionada = *politicas[opcion - 1];
        string nombresPoliticas[] = {"Flexible", "Moderada", "Estricta"};
        cout << "Politica seleccionada: " << nombresPoliticas[opcion - 1] << '\n';
        ControladorReservas controlador(gestor);
        sys_seconds creacion = crearFecha(2027, 1, 1, 12);
        sys_seconds entrada = crearFecha(2027, 1, 10, 12);
        sys_seconds salida = crearFecha(2027, 1, 13, 12);
        cout << fixed << setprecision(2);

        controlador.crearReserva(1, ana, individual, 1, creacion, entrada, salida, flexible);
        controlador.crearReserva(2, luis, doble, 2, creacion, entrada, salida, seleccionada);
        controlador.crearReserva(3, ana, suite, 2, creacion, entrada, salida, estricta);
        try {
            controlador.crearReserva(4, luis, individual, 1, creacion, entrada, salida, flexible);
        } catch (const runtime_error& error) {
            cout << "Reserva rechazada: " << error.what() << '\n';
        }
        try {
            controlador.cancelarReserva(2, crearFecha(2027, 1, 7, 12));
        } catch (const runtime_error& error) {
            cout << "Cancelacion rechazada: " << error.what() << '\n';
        }
        cout << "Habitacion 201 disponible del 10 al 13: "
             << (doble.estaDisponible(entrada, salida) ? "Si" : "No") << '\n';
        try {
            controlador.cancelarReserva(3, crearFecha(2027, 1, 7, 12));
        } catch (const runtime_error& error) {
            cout << "Cancelacion rechazada: " << error.what() << '\n';
        }
        controlador.realizarCheckIn(1, entrada);
        controlador.realizarCheckIn(3, entrada);
        ControladorServicios servicios;
        for (const Habitacion* habitacion : habitaciones)
            servicios.solicitarServicios(*habitacion);
        controlador.realizarCheckOut(1, salida);
        controlador.realizarCheckOut(3, salida);

        PersonalLimpieza personal("Elena Rios");
        personal.asignar(individual);
        personal.asignar(suite);
        cout << "Carga de " << personal.getNombre() << ": " << personal.getCargaTrabajo() << " habitaciones.\n";
        personal.completar(individual);
        personal.completar(suite);
        cout << "Tareas pendientes: " << personal.getCargaTrabajo() << '\n';

        // La salida de una reserva permite otra entrada en ese mismo instante.
        controlador.crearReserva(5, luis, individual, 1, creacion, salida, crearFecha(2027, 1, 15, 12), flexible);
        controlador.realizarCheckIn(5, salida);
        controlador.realizarCheckOut(5, crearFecha(2027, 1, 15, 12));
        personal.asignar(individual);
        personal.completar(individual);

        GeneradorInformes informes;
        informes.mostrarHistorial(ana, gestor.getReservas());
        informes.mostrarHistorial(luis, gestor.getReservas());
        sys_seconds finInforme = crearFecha(2027, 1, 16, 12);
        for (const Habitacion* habitacion : habitaciones)
            cout << "Ocupacion reservada de tipo " << habitacion->getTipo() << " del 10 al 16 de enero: "
                 << informes.calcularOcupacion(habitacion->getTipo(), habitaciones, gestor.getReservas(), entrada, finInforme)
                 << "%\n";
        cout << "Ingresos del 1 al 16 de enero: S/ "
             << informes.calcularIngresos(gestor.getReservas(), creacion, finInforme) << '\n';
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
