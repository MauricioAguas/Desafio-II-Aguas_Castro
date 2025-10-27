

#pragma once
#include <iostream>
#include <string>

using namespace std;

class InterfazVisual {
public:

    static void mostrarReproduccion(const string& nombreCancion, const string& artista, const string& album) {
        cout << "\n+-------------------------------------------------+" << endl;
        cout << "|                                                 |" << endl;
        cout << "| Cantante: " << ajustarTexto(artista, 32) << "|" << endl;
        cout << "| Album: " << ajustarTexto(album, 35) << "|" << endl;
        cout << "| Ruta portada: /img/" << album << ".jpg         |" << endl;
        cout << "|                                                 |" << endl;
        cout << "| Titulo de la cancion reproducida:              |" << endl;
        cout << "| " << ajustarTexto(nombreCancion, 45) << " |" << endl;
        cout << "| Ruta audio: /music/128/" << nombreCancion << ".ogg |" << endl;
        cout << "| Duracion: 180 segundos                          |" << endl;
        cout << "|                                                 |" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Opciones de reproduccion:                      |" << endl;
        cout << "| 1.- Reproducir  2.- Detener ....               |" << endl;
        cout << "| *Todas las opciones que apliquen               |" << endl;
        cout << "+-------------------------------------------------+" << endl;
    }


    static void mostrarPublicidad(const string& mensaje, const string& categoria) {
        cout << "\n+-------------------------------------------------+" << endl;
        cout << "|              MENSAJE PUBLICITARIO               |" << endl;
        cout << "| " << ajustarTexto(mensaje, 45) << " |" << endl;
        cout << "| Categoria: " << categoria << "                              |" << endl;
        cout << "+-------------------------------------------------+" << endl;
    }

private:
    static string ajustarTexto(const string& texto, int longitud) {
        if (texto.length() <= longitud) {
            return texto + string(longitud - texto.length(), ' ');
        }
        return texto.substr(0, longitud - 3) + "...";
    }
};
