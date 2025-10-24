#include <iostream>
#include "lista.h"
using namespace std;

// Clase simple para probar la lista
class ElementoPrueba {
private:
    int id;
    string nombre;

public:
    ElementoPrueba(int i, string n) : id(i), nombre(n) {}
    int getId() const { return id; }
    string getNombre() const { return nombre; }

    void mostrar() const {
        cout << "ID: " << id << " | Nombre: " << nombre << endl;
    }
};

int main() {
    Lista<ElementoPrueba> lista(3);  // Lista inicial con capacidad 3

    // Agregar elementos
    lista.agregar(new ElementoPrueba(1, "Cancion A"));
    lista.agregar(new ElementoPrueba(2, "Cancion B"));
    lista.agregar(new ElementoPrueba(3, "Cancion C"));

    cout << "Lista inicial:" << endl;
    for (int i = 0; i < lista.tamanio(); ++i)
        lista.obtener(i)->mostrar();

    cout << "\nBuscando elemento con ID=2..." << endl;
    int pos = lista.buscarPorId(2);
    if (pos != -1)
        lista.obtener(pos)->mostrar();
    else
        cout << "No encontrado.\n";

    cout << "\nEliminando elemento en índice 1..." << endl;
    lista.eliminar(1);

    cout << "Lista después de eliminar:" << endl;
    for (int i = 0; i < lista.tamanio(); ++i)
        lista.obtener(i)->mostrar();

    cout << "\nLimpiando lista completa..." << endl;
    lista.limpiar();
    cout << "Tamaño actual: " << lista.tamanio() << endl;

    cout << "\nIteraciones realizadas: " << Lista<ElementoPrueba>::getIteraciones() << endl;

    return 0;
}
