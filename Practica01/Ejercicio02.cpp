#include <iostream>
#include <string>

using namespace std;

// ALTA COHESIÓN: La clase Personaje solo se encarga de gestionar sus propios atributos básicos.
class Personaje {
private:
    // 1. Cuatro variables de diferentes tipos
    string nombre;
    int nivel;
    float vida;
    bool estaVivo;

    // 2. Método PRIVATE: Solo la clase lo necesita para uso interno.
    void evaluarEstadoVital() {
        if (vida <= 0) {
            vida = 0;
            estaVivo = false;
        }
    }

protected:
    // 3. Método PROTECTED: Accesible si decides crear clases hijas (Herencia).
    void mostrarEfectoDanio(float danio) {
        cout << nombre << " recibe " << danio << " de danio magico/fisico." << endl;
    }

public:
    // 4. CONSTRUCTOR
    Personaje(string _nombre, int _nivel, float _vidaMaxima) {
        nombre = _nombre;
        nivel = _nivel;
        vida = _vidaMaxima;
        estaVivo = true;
    }

    // 5. GETTERS Y SETTERS (Métodos PUBLIC)
    float getVida() {
        return vida;
    }

    void setVida(float nuevaVida) {
        vida = nuevaVida;
        evaluarEstadoVital(); // Llamada al método privado
    }

    string getNombre() {
        return nombre;
    }

    bool getEstado() {
        return estaVivo;
    }

    // 6. Método PUBLIC de interacción
    void recibirAtaque(float danioBase) {
        mostrarEfectoDanio(danioBase); // Llamada al método protegido
        setVida(vida - danioBase);     // Llamada al setter
    }
};

// BAJO ACOPLAMIENTO: Separamos la lógica de la pelea en otra entidad.
class SistemaCombate {
public:
    static void ejecutarAtaque(Personaje& atacante, Personaje& defensor, float danio) {
        cout << "\n>>> " << atacante.getNombre() << " ataca! <<<" << endl;
        defensor.recibirAtaque(danio);
        
        if (!defensor.getEstado()) {
            cout << defensor.getNombre() << " ha sido eliminado." << endl;
        } else {
            cout << "Vida restante de " << defensor.getNombre() << ": " << defensor.getVida() << endl;
        }
    }
};

int main() {
    // 7. INSTANCIACIÓN DE CLASES
    Personaje wei("Wei (Anti-Mage)", 25, 1500.5f);
    Personaje invoker("Mago Enemigo", 20, 950.0f);

    cout << "--- INICIO DEL ENFRENTAMIENTO ---" << endl;
    
    // Llamado a las funciones para que interactúen
    SistemaCombate::ejecutarAtaque(wei, invoker, 450.5f);
    SistemaCombate::ejecutarAtaque(invoker, wei, 120.0f);
    SistemaCombate::ejecutarAtaque(wei, invoker, 600.0f);

    return 0;
}

