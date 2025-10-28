#pragma once
#include <iostream>
#include <string>

using namespace std;

class InterfazVisual {
public:
    static void mostrarReproduccion(const string& titulo,
                                    const string& artista,
                                    const string& album,
                                    const string& ruta,
                                    int duracionSeg,
                                    int reproducciones,
                                    const string& tipoUsuario,
                                    bool reproduccionActiva,
                                    bool tieneAnterior,
                                    bool repetir,
                                    int idCancion) {
        const size_t ancho = 49;

        cout << "\n+-------------------------------------------------+" << endl;
        cout << "| ID Cancion: " << idCancion << ajustarTexto("", 34 - to_string(idCancion).length()) << "|\n";
        cout << "| Cantante: " << ajustarTexto(artista, ancho - 12) << "|" << endl;
        cout << "| Album: " << ajustarTexto(album, ancho - 9) << "|" << endl;
        cout << "| Ruta portada: " << ajustarTexto("/img/" + album + ".jpg", ancho - 16) << "|" << endl;
        cout << "|                                                 |" << endl;
        cout << "| Titulo de la cancion:                           |" << endl;
        cout << "| " << ajustarTexto(titulo, ancho - 2) << "|" << endl;
        cout << "| Ruta audio: " << ajustarTexto(ruta + ".ogg", ancho - 13) << "|" << endl;
        cout << "| Duracion: " << ajustarTexto(to_string(duracionSeg) + " segundos", ancho - 12) << "|" << endl;
        cout << "| Calidad: " << ajustarTexto(tipoUsuario == "Premium" ? "320kbps" : "128kbps", ancho - 11) << "|" << endl;
        cout << "| Reproducciones: " << ajustarTexto(to_string(reproducciones), ancho - 18) << "|" << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "| Opciones de interaccion:                        |" << endl;
        cout << "| 1. Reproducir/Detener  2. Siguiente             |" << endl;
        cout << "| 3. Previa (Premium)     4. Repetir (Premium)    |" << endl;
        cout << "| 0. Salir                                       |" << endl;
        cout << "+-------------------------------------------------+" << endl;
    }

    static string pedirOpcion(const string& tipoUsuario) {
        cout << "\n[MENU REPRODUCCION] Ingrese opcion (1-4 / 0 para salir): ";
        string op;
        cin >> op;
        return op;
    }

private:
    static string ajustarTexto(const string& texto, size_t longitud) {
        if (texto.length() < longitud) {
            return texto + string(longitud - texto.length(), ' ');
        }
        if (longitud <= 3) return string(longitud, '.');
        return texto.substr(0, longitud - 3) + "...";
    }
};
