#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
using namespace std;

template<typename T>
class ListaEnlazada {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };
    Nodo* cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}
    ~ListaEnlazada() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void agregar(const T& d) {
        Nodo* nuevo = new Nodo(d);
        if (!cabeza) cabeza = nuevo;
        else {
            Nodo* aux = cabeza;
            while (aux->siguiente) aux = aux->siguiente;
            aux->siguiente = nuevo;
        }
    }

    void imprimir() const {
        Nodo* aux = cabeza;
        int i = 1;
        while (aux) {
            cout << i++ << ". " << aux->dato << endl;
            aux = aux->siguiente;
        }
    }
};

#endif