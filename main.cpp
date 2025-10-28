#include <iostream>
#include <string>
#include "UdeATunes.h"
#include "Usuario.h"

using namespace std;

static void mostrarMenuBasico(Usuario* u) {
    cout << "\n==============================================" << endl;
    cout << "  UdeATunes - Usuario: " << u->getNickname() << " (" << u->getTipo() << ")" << endl;
    cout << "==============================================" << endl;
    cout << "1. Reproducir 5 canciones aleatorias" << endl;
    cout << "2. Favoritos (Premium)" << endl;
    cout << "3. Seguimiento (Premium)" << endl;
    cout << "4. Resumen del sistema" << endl;
    cout << "0. Cerrar sesion" << endl;
    cout << "Opcion: ";
}

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

    while (true) {
        Usuario* usuarioActual = nullptr;
        string nick;

        while (usuarioActual == nullptr) {
            cout << "\nInicio de sesion" << endl;
            cout << "Ingrese nickname (o 'salir'): ";
            cin >> nick;
            if (nick == "salir" || nick == "SALIR") {
                cout << "Cerrando UdeATunes..." << endl;
                return 0;
            }
            usuarioActual = app.iniciarSesion(nick);
            if (!usuarioActual) cout << "Nickname no encontrado." << endl;
        }

        int op = -1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true) {
            mostrarMenuBasico(usuarioActual);
            if (!(cin >> op)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida." << endl;
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (op == 1) {
                app.reproducirRandom(usuarioActual);
                cout << "Presione Enter para continuar...";
                cin.get();
                continue;
            } else if (op == 2) {
                app.gestionarFavoritos(usuarioActual);
            } else if (op == 3) {
                app.gestionarSeguimiento(usuarioActual);
            } else if (op == 4) {
                app.mostrarResumen();
            } else if (op == 0) {
                cout << "Cerrando sesion de " << usuarioActual->getNickname() << endl;
                break;
            } else {
                cout << "Opcion invalida." << endl;
            }
        }
    }
    return 0;
}
