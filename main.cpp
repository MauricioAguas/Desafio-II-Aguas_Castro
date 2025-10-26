#include <iostream>
#include <string>
#include "UdeATunes.h"


 using namespace std;

// Función para mostrar el menú de opciones (lo implementaremos después)
void mostrarMenu(Usuario* u);

int main() {
    // Inicializar la semilla aleatoria UNA SOLA VEZ
    srand(time(0));

    cout << "=== UDEATUNES: VIVE LA MÚSICA ===" << endl;
    UdeATunes app;

    // NOTA: Reemplaza estas rutas con las rutas absolutas correctas de tu sistema
    const string RUTA_BASE = "C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio2_Aguas_Castro/Desafio-II-Aguas_Castro/data/";

    app.cargarCanciones(RUTA_BASE + "canciones.txt");
    app.cargarAlbumes(RUTA_BASE + "albumes.txt");
    app.cargarArtistas(RUTA_BASE + "artistas.txt");
    app.cargarUsuarios(RUTA_BASE + "usuarios.txt");

    // ⬅️ CARGA DE ANUNCIOS
    app.cargarAnuncios(RUTA_BASE + "anuncios.txt");

    app.vincular();

    // --- 1. BUCLE DE PRE-LOGIN ---
    Usuario* usuarioActual = nullptr;
    string nickname, comando;

    while (usuarioActual == nullptr) {
        cout << "Ingrese su Nickname para iniciar sesión (o 'salir'): ";
        cin >> nickname;

        if (nickname == "salir" || nickname == "SALIR") {
            cout << "Cerrando UdeATunes... ¡Hasta pronto! 🎧" << endl;
            return 0; // Termina la aplicación
        }

        usuarioActual = app.iniciarSesion(nickname);

        if (usuarioActual == nullptr) {
            cout << "\n❌ ERROR: Nickname no encontrado. Intente de nuevo.\n" << endl;
        } else {
            cout << "\n✅ ¡Sesión iniciada con éxito! Bienvenido, "
                 << usuarioActual->getNickname() << " (" << usuarioActual->getTipo() << ")." << endl;
        }
    }

    // --- 2. BUCLE DE POST-LOGIN (MENÚ PRINCIPAL) ---
    while (true) {
        mostrarMenu(usuarioActual); // Muestra las opciones según el tipo de usuario
        cout << "\nIngrese su opción: ";
        cin >> comando;

        // Ejecutar las funcionalidades
        if (comando == "1") {
            app.reproducirRandom(usuarioActual);
        }
        else if (comando == "2" && usuarioActual->getTipo() == "Premium") {
            // Futura función de Lista de Favoritos (Solo Premium)
            cout << "Funcionalidad 'Mi Lista de Favoritos' en desarrollo." << endl;
        }
        else if (comando == "0" || comando == "salir") {
            cout << "\nCerrando sesión de " << usuarioActual->getNickname() << "... Adiós." << endl;
            usuarioActual = nullptr; // Opcional: permitiría volver al login si se implementa un bucle exterior
            break;
        }
        else {
            cout << "\nComando no reconocido o no disponible para su membresía.\n" << endl;
        }
    }

    return 0;
}


// Implementación de la función mostrarMenu
void mostrarMenu(Usuario* u) {
    cout << "\n======== MENÚ PRINCIPAL ========" << endl;
    cout << "1. Reproducción Aleatoria Global (K=5)" << endl;

    if (u->getTipo() == "Premium") {
        cout << "2. Mi Lista de Favoritos (Premium)" << endl;
        // Podríamos agregar más opciones aquí
    }

    cout << "0. Cerrar Sesión / Salir" << endl;
    cout << "================================" << endl;
}
