#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <string>
#include <iostream>
using namespace std;

class Anuncio {
private:
    int id;
    string mensaje;
    string categoria; // Almacena el texto: 'AAA', 'B', o 'C'
    int peso;         // 3, 2 o 1, para la selección ponderada

public:
    // Constructor
    Anuncio(int id, const string& msg, const string& cat)
        : id(id), mensaje(msg), categoria(cat) {
        // Asignación de peso basada en la categoría (requisito del desafío)
        if (categoria == "AAA")
            peso = 3;
        else if (categoria == "B")
            peso = 2;
        else // Categoria C o cualquier otro valor por defecto
            peso = 1;
    }

    // Getters
    int getId() const { return id; }
    const string& getMensaje() const { return mensaje; }
    const string& getCategoria() const { return categoria; }
    int getPeso() const { return peso; } // Clave para la selección aleatoria

    void mostrar() const {
        cout << "[Anuncio " << categoria << " (" << peso << "x)] " << mensaje << endl;
    }

    // El requisito de "no repetir el último anuncio" lo manejaremos en la clase UdeATunes
    // para mantener la clase Anuncio enfocada solo en sus datos.
};

#endif
