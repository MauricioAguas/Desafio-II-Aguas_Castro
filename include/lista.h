#ifndef LISTA_H
#define LISTA_H

#include <iostream>
using namespace std;

template <typename T>
class Lista {
private:
    T* elementos;       // arreglo dinámico de punteros T
    int tam;
    int capacidad;
    static int iteraciones;
    static size_t memoriaConsumida; // ⬅️ NUEVO: para rastrear la memoria total de los arreglos

    void redimensionar();

public:
    Lista(int capInicial = 10);
    ~Lista();

    bool agregar(T nuevo);
    bool eliminar(int indice);
    T obtener(int indice) const;
    int buscarPorId(int id) const;
    int tamanio() const;
    void limpiar();

    static int getIteraciones();
    static size_t getMemoria(); // ⬅️ NUEVO: Getter para el consumo de memoria
    static void limpiarIteraciones() { iteraciones = 0; }
};

// ----------------------------------------------------------------------
// 🔹 Inicialización de variables estáticas
// ----------------------------------------------------------------------
template <typename T>
int Lista<T>::iteraciones = 0;

template <typename T>
size_t Lista<T>::memoriaConsumida = 0; // ⬅️ Inicialización

// ----------------------------------------------------------------------
// 🔹 Constructor y Destructor
// ----------------------------------------------------------------------
template <typename T>
Lista<T>::Lista(int capInicial)
    : tam(0), capacidad(capInicial)
{
    elementos = new T[capInicial];
    memoriaConsumida += sizeof(T) * capacidad; // ⬅️ Se suma la memoria al crear
}

template <typename T>
Lista<T>::~Lista() {
    memoriaConsumida -= sizeof(T) * capacidad; // ⬅️ Se resta la memoria al destruir
    delete[] elementos;
}

// ----------------------------------------------------------------------
// 🔹 Redimensionamiento (Optimización y Medición)
// ----------------------------------------------------------------------
template <typename T>
void Lista<T>::redimensionar() {
    iteraciones++;
    int nuevaCap = capacidad * 2;
    T* nuevos = new T[nuevaCap];
    for (int i = 0; i < tam; ++i) {
        nuevos[i] = elementos[i];
        iteraciones++;
    }

    // Ajuste de memoria: Resta la antigua y suma la nueva
    memoriaConsumida -= sizeof(T) * capacidad;
    delete[] elementos;
    elementos = nuevos;
    capacidad = nuevaCap;
    memoriaConsumida += sizeof(T) * capacidad;
}

// ----------------------------------------------------------------------
// 🔹 Métodos CRUD
// ----------------------------------------------------------------------
template <typename T>
bool Lista<T>::agregar(T nuevo) {
    iteraciones++;
    if (tam == capacidad) redimensionar();
    elementos[tam++] = nuevo;
    return true;
}

template <typename T>
bool Lista<T>::eliminar(int indice) {
    iteraciones++;
    if (indice < 0 || indice >= tam) return false;
    for (int i = indice; i < tam - 1; ++i) {
        elementos[i] = elementos[i + 1];
        iteraciones++;
    }
    tam--;
    return true;
}

template <typename T>
T Lista<T>::obtener(int indice) const {
    iteraciones++;
    if (indice < 0 || indice >= tam) return nullptr;
    return elementos[indice];
}

template <typename T>
int Lista<T>::buscarPorId(int id) const {
    iteraciones++;
    // Búsqueda lineal O(n) - simple por ahora
    for (int i = 0; i < tam; ++i) {
        // Asumiendo que T tiene un método getId()
        if (elementos[i]->getId() == id) {
            iteraciones++;
            return i;
        }
        iteraciones++;
    }
    return -1;
}

// ----------------------------------------------------------------------
// 🔹 Getters e Inicializadores de Métricas
// ----------------------------------------------------------------------

template <typename T>
int Lista<T>::tamanio() const {
    return tam;
}

template <typename T>
void Lista<T>::limpiar() {
    tam = 0;
}

template <typename T>
int Lista<T>::getIteraciones() {
    int temp = iteraciones;
    iteraciones = 0; // Se reinicia el contador estático al pedir el valor
    return temp;
}

template <typename T>
size_t Lista<T>::getMemoria() { // ⬅️ NUEVO: Implementación del Getter
    return memoriaConsumida;
}


#endif // LISTA_H
