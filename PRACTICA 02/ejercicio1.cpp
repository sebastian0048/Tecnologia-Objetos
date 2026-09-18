// ejercicio1.cpp
#include <iostream>

using namespace std;

// Función para calcular el promedio general
void calcularPromedio(float* notas, int n) {
    float suma = 0;
    for(int i = 0; i < n; i++) {
        suma += *(notas + i); // Acceso al valor mediante aritmética de punteros
    }
    cout << "Promedio general: " << suma / n << endl;
}

// Función para encontrar la nota mayor
void calcularMayor(float* notas, int n) {
    float mayor = *notas; // Inicializamos con el primer elemento
    for(int i = 1; i < n; i++) {
        if(*(notas + i) > mayor) {
            mayor = *(notas + i);
        }
    }
    cout << "Nota mayor: " << mayor << endl;
}

// Función para encontrar la nota menor
void calcularMenor(float* notas, int n) {
    float menor = *notas; // Inicializamos con el primer elemento
    for(int i = 1; i < n; i++) {
        if(*(notas + i) < menor) {
            menor = *(notas + i);
        }
    }
    cout << "Nota menor: " << menor << endl;
}

// Función para imprimir las notas en orden inverso
void imprimirInverso(float* notas, int n) {
    cout << "Notas en orden inverso: ";
    for(int i = n - 1; i >= 0; i--) {
        cout << *(notas + i) << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "--- Sistema de Registro de Notas ---" << endl;
    cout << "Ingrese la cantidad de estudiantes a evaluar: ";
    cin >> n;

    if (n <= 0) {
        cout << "Cantidad invalida. Debe ser mayor a 0." << endl;
        return 1;
    }

    // RESERVA DE MEMORIA DINÁMICA
    // Se utiliza 'new' para reservar el espacio exacto que se necesita en tiempo de ejecución.
    float* notas = new float[n];

    // Ingreso de datos
    cout << "\n--- Ingreso de Notas ---\n";
    for(int i = 0; i < n; i++) {
        cout << "Ingrese la nota del estudiante " << i + 1 << ": ";
        cin >> *(notas + i);
    }

    // Llamado a las funciones pasando el puntero como argumento
    cout << "\n--- Resultados Estadisticos ---\n";
    calcularPromedio(notas, n);
    calcularMayor(notas, n);
    calcularMenor(notas, n);
    imprimirInverso(notas, n);

    // LIBERACIÓN DE MEMORIA
    // Es obligatorio liberar la memoria dinámica para evitar fugas de memoria (memory leaks).
    delete[] notas;

    return 0;
}