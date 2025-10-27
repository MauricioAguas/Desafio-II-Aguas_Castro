#include <iostream>
#include <string>
#include <limits>
#include "UdeATunes.h"
#include "MenuInteractivo.h"

using namespace std;

int main() {
    srand(time(0));
    UdeATunes app;
    const string RUTA_BASE = "D:/Mis documentos/DesafioII/data/";

    app.cargarCanciones(RUTA_BASE + "canciones.txt");
    app.cargarAlbumes(RUTA_BASE + "albumes.txt");
    app.cargarArtistas(RUTA_BASE + "artistas.txt");
    app.cargarUsuarios(RUTA_BASE + "usuarios.txt");
    app.cargarAnuncios(RUTA_BASE + "anuncios.txt");
    app.vincular();

    while (true) {  // Bucle externo para volver al login tras cerrar sesion
        Usuario* usuarioActual = nullptr;
        string nickname;

        while (usuarioActual == nullptr) {
            cout << "Ingrese su Nickname para iniciar sesion (o 'salir'): ";
            cin >> nickname;

            if (nickname == "salir" || nickname == "SALIR") {
                cout << "Cerrando UdeATunes... Hasta pronto!" << endl;
                return 0;
            }

            usuarioActual = app.iniciarSesion(nickname);

            if (usuarioActual == nullptr) {
                cout << "\nERROR: Nickname no encontrado. Intente de nuevo.\n" << endl;
            } else {
                cout << "\nSesion iniciada con exito! Bienvenido, "
                     << usuarioActual->getNickname() << " (" << usuarioActual->getTipo() << ")." << endl;
            }
        }

        int opcion = -1;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

        while (true) {
            MenuInteractivo::mostrarMenuPrincipal(usuarioActual);
            cout << "\nIngrese su opcion: ";
            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Entrada invalida. Intente de nuevo." << endl;
                continue;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer

            if (opcion == 1) {
                app.reproducirRandom(usuarioActual);
                cout << "\nPresione Enter para continuar...";
                cin.get();
                continue;
            }

            bool salir = MenuInteractivo::procesarOpcion(opcion, usuarioActual);
            if (salir) {
                cout << "\nCerrando sesion de " << usuarioActual->getNickname() << "... Adios." << endl;
                usuarioActual = nullptr;
                break;
            }
        }
    }

    return 0;
}
