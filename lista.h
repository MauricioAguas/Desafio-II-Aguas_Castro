#ifndef LISTA_H
#define LISTA_H

#include <iostream>
using namespace std;

template <typename T>
class Lista {
private:
    T** elementos;
    int tam;
    int capacidad;
    static int iteraciones;

    void redimensionar();

public:
    Lista(int capInicial = 10);
    ~Lista();

    bool agregar(T* nuevo);
    bool eliminar(int indice);
    T* obtener(int indice) const;
    int buscarPorId(int id) const;
    int tamanio() const;
    void limpiar();

    static int getIteraciones();
};

// Inicialización del miembro estático
template <typename T>
int Lista<T>::iteraciones = 0;

// Implementación de métodos

template <typename T>
Lista<T>::Lista(int capInicial) {
    capacidad = capInicial;
    tam = 0;
    elementos = new T*[capacidad];
}

template <typename T>
Lista<T>::~Lista() {
    for (int i = 0; i < tam; ++i)
        delete elementos[i];
    delete[] elementos;
}

template <typename T>
void Lista<T>::redimensionar() {
    iteraciones++;
    int nuevaCap = capacidad * 2;
    T** nuevos = new T*[nuevaCap];
    for (int i = 0; i < tam; ++i) {
        nuevos[i] = elementos[i];
        iteraciones++;
    }
    delete[] elementos;
    elementos = nuevos;
    capacidad = nuevaCap;
}

template <typename T>
bool Lista<T>::agregar(T* nuevo) {
    iteraciones++;
    if (tam == capacidad) redimensionar();
    elementos[tam++] = nuevo;
    return true;
}

template <typename T>
bool Lista<T>::eliminar(int indice) {
    iteraciones++;
    if (indice < 0 || indice >= tam) return false;
    delete elementos[indice];
    for (int i = indice; i < tam - 1; ++i) {
        elementos[i] = elementos[i + 1];
        iteraciones++;
    }
    tam--;
    return true;
}

template <typename T>
T* Lista<T>::obtener(int indice) const {
    iteraciones++;
    if (indice < 0 || indice >= tam) return nullptr;
    return elementos[indice];
}

template <typename T>
int Lista<T>::buscarPorId(int id) const {
    iteraciones++;
    for (int i = 0; i < tam; ++i) {
        iteraciones++;
        if (elementos[i]->getId() == id)
            return i;
    }
    return -1;
}

template <typename T>
int Lista<T>::tamanio() const { return tam; }

template <typename T>
void Lista<T>::limpiar() {
    iteraciones++;
    for (int i = 0; i < tam; ++i) {
        delete elementos[i];
        iteraciones++;
    }
    tam = 0;
}

template <typename T>
int Lista<T>::getIteraciones() { return iteraciones; }

#endif
