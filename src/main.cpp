#include <iostream>
#include <string>
#include "UdeATunes.h"
#include "MenuInteractivo.h"

using namespace std;

int main() {
    // Inicializar la semilla aleatoria UNA SOLA VEZ
    srand(time(0));

    cout << "=== UDEATUNES: VIVE LA MUSICA ===" << endl;
    UdeATunes app;

    // NOTA: Reemplaza estas rutas con las rutas absolutas correctas de tu sistema
    const string RUTA_BASE = "D:/Mis documentos/DesafioII/data/";

    app.cargarCanciones(RUTA_BASE + "canciones.txt");
    app.cargarAlbumes(RUTA_BASE + "albumes.txt");
    app.cargarArtistas(RUTA_BASE + "artistas.txt");
    app.cargarUsuarios(RUTA_BASE + "usuarios.txt");

    // CARGA DE ANUNCIOS
    app.cargarAnuncios(RUTA_BASE + "anuncios.txt");

    app.vincular();

    // --- 1. BUCLE DE PRE-LOGIN ---
    Usuario* usuarioActual = nullptr;
    string nickname;

    while (usuarioActual == nullptr) {
        cout << "Ingrese su Nickname para iniciar sesion (o 'salir'): ";
        cin >> nickname;

        if (nickname == "salir" || nickname == "SALIR") {
            cout << "Cerrando UdeATunes... Hasta pronto!" << endl;
            return 0; // Termina la aplicacion
        }

        usuarioActual = app.iniciarSesion(nickname);

        if (usuarioActual == nullptr) {
            cout << "\nERROR: Nickname no encontrado. Intente de nuevo.\n" << endl;
        } else {
            cout << "\nSesion iniciada con exito! Bienvenido, "
                 << usuarioActual->getNickname() << " (" << usuarioActual->getTipo() << ")." << endl;
        }
    }

    // --- 2. BUCLE DE POST-LOGIN (MENU INTERACTIVO) ---
    int opcion = -1;
    while (true) {
        // Mostrar menu segun tipo de usuario
        MenuInteractivo::mostrarMenuPrincipal(usuarioActual);

        cout << "\nIngrese su opcion: ";
        if (!(cin >> opcion)) {
            // Limpiar buffer si entrada invalida
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente de nuevo." << endl;
            continue;
        }

        if (opcion == 1) {
            // Tu funcionalidad ya implementada (reproduccion aleatoria)
            app.reproducirRandom(usuarioActual);

            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            continue;
        }

        // Otras opciones: las maneja MenuInteractivo
        bool salir = MenuInteractivo::procesarOpcion(opcion, usuarioActual);
        if (salir) {
            cout << "\nCerrando sesion de " << usuarioActual->getNickname() << "... Adios." << endl;
            usuarioActual = nullptr;
            break;
        }
    }

    return 0;
}
