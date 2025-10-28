#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class InterfazVisual {
public:

    // ⬅️ FUNCIÓN CORREGIDA para recibir todos los datos y opciones de estado
    static void mostrarReproduccion(const string& titulo, const string& artista, const string& album,
                                    const string& rutaArchivo, int duracion, int reproducciones,
                                    const string& tipoUsuario, bool repActiva, bool hayPrevia, bool modoRepetir) {
        string calidad = "Baja (128kbps)";

        // --- Encabezado ---
        cout<<tipoUsuario;
        cout << "\n+-------------------------------------------------+\n";
        cout << "| Cantante: " << ajustarTexto(artista, 32) << "|\n";
        cout << "| Album: " << ajustarTexto(album, 35) << "|\n";
        cout << "| Ruta portada: /img/" << ajustarTexto(album, 20) << ".jpg    |\n";
        cout << "|                                                 |\n";
        cout << "| Titulo de la cancion:                          |\n";
        cout << "| " << ajustarTexto(titulo, 45) << " |\n";
        cout << "| Ruta audio: " << ajustarTexto(rutaArchivo + ".ogg", 28) << "    |\n";
        cout << "| Duracion: " << duracion << " segundos" << ajustarTexto("", 25 - to_string(duracion).length()) << "|\n";
        if (tipoUsuario == "Premium") {
            cout << "| Calidad: " << ajustarTexto("360kps", 32) << "|\n";}
        else{cout << "| Calidad: " << ajustarTexto("128kps", 32) << "|\n";}
        cout << "| Reproducciones: " << reproducciones << ajustarTexto("", 30 - to_string(reproducciones).length()) << "|\n";
        cout << "+-------------------------------------------------+\n";

        // --- Opciones de Reproducción ---
        stringstream ssOpciones;

        if (repActiva) {
            ssOpciones << "1. Detener  ";
        } else {
            ssOpciones << "1. Iniciar  ";
        }

        ssOpciones << "2. Siguiente ";

        if (tipoUsuario == "Premium") {
            ssOpciones << "3. Previa (" << (hayPrevia ? "Activa" : "Inactiva") << ") ";
            ssOpciones << "4. Repetir (" << (modoRepetir ? "ON" : "OFF") << ") ";
        }

        cout << "+-------------------------------------------------+\n";
        cout << "| Opciones de interaccion:                       |\n";
        cout << "| " << ajustarTexto(ssOpciones.str(), 45) << " |\n";
        cout << "+-------------------------------------------------+\n";
    }

    // Función auxiliar que pide la opción de interacción
    static string pedirOpcion(const string& tipoUsuario) {
        cout << "\n[MENU REPRODUCCIÓN] Ingrese opción (1-4 / 0 para salir): ";
        string opcion;
        cin >> opcion;
        return opcion;
    }


private:
    static string ajustarTexto(const string& texto, int longitud) {
        if (texto.length() <= longitud) {
            return texto + string(longitud - texto.length(), ' ');
        }
        return texto.substr(0, longitud - 3) + "...";
    }
};
