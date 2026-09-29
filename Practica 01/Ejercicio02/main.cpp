#include <iostream>
#include <string>

using namespace std;

class Personaje {
private:
    string nombre;
    int nivel;
    float vida;
    bool estaVivo;

    void evaluarEstadoVital() {
        if (vida <= 0) {
            vida = 0;
            estaVivo = false;
        }
    }

protected:
    void mostrarEfectoDanio(float danio) {
        cout << nombre << " recibe " << danio << " de danio magico/fisico." << endl;
    }

public:
    Personaje(string _nombre, int _nivel, float _vidaMaxima) {
        nombre = _nombre;
        nivel = _nivel;
        vida = _vidaMaxima;
        estaVivo = true;
    }

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

    void recibirAtaque(float danioBase) {
        mostrarEfectoDanio(danioBase); // Llamada al método protegido
        setVida(vida - danioBase);     // Llamada al setter
    }
};

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
    Personaje wei("Wei (Anti-Mage)", 25, 1500.5f);
    Personaje invoker("Mago Enemigo", 20, 950.0f);

    cout << "--- INICIO DEL ENFRENTAMIENTO ---" << endl;
    
    SistemaCombate::ejecutarAtaque(wei, invoker, 450.5f);
    SistemaCombate::ejecutarAtaque(invoker, wei, 120.0f);
    SistemaCombate::ejecutarAtaque(wei, invoker, 600.0f);

    return 0;
}