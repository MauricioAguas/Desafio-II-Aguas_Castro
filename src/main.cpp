#include <iostream>
#include <string>
#include <limits> // Para numeric_limits
#include "UdeATunes.h"
#include "metricas.h"
using namespace std;

void mostrarMenuPrincipal(Usuario* usuario);
void ejecutarMenu(UdeATunes& app, Usuario* usuario);

// ------------------------------------------
// Se asume que estas constantes existen en la version completa del archivo
const string BASE_PATH = "C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio2_Aguas_Castro/Desafio-II-Aguas_Castro/data/";

const string CANCIONES_PATH = BASE_PATH + "canciones.txt";
const string ALBUMES_PATH = BASE_PATH + "albumes.txt";
const string ARTISTAS_PATH = BASE_PATH + "artistas.txt";
const string USUARIOS_PATH = BASE_PATH + "usuarios.txt";
const string ANUNCIOS_PATH = BASE_PATH + "anuncios.txt";
// ------------------------------------------

void mostrarMenuPrincipal(Usuario* usuario) {
    cout << "\n===============================================" << endl;
    cout << "  Bienvenido a UdeATunes, " << usuario->getNickname() << " (" << usuario->getTipo() << ")" << endl;
    cout << "===============================================" << endl;
    cout << "1. Reproducir todas las canciones (Aleatorio)" << endl;
    cout << "2. Reproducir mis favoritos (Premium)" << endl;
    cout << "3. Reproducir Favoritos de mi Seguido (Premium) NUEVO" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "4. Gestionar mis favoritos (Agregar/Quitar)" << endl;
    cout << "5. Gestionar Seguimiento (Seguir/Dejar)" << endl;
    cout << "6. Ver Resumen Estadistico" << endl;
    cout << "0. Cerrar Sesion" << endl;
    cout << "===============================================" << endl;
}

void ejecutarMenu(UdeATunes& app, Usuario* usuario) {
    string opcionStr;
    bool sesionActiva = true;

    while (sesionActiva) {
        mostrarMenuPrincipal(usuario);
        cout << "Ingrese opcion: ";
        // Intentamos leer la opcion como string para manejar entradas no numericas
        if (!(cin >> opcionStr)) {
            cout << "Error de entrada. Reiniciando menu." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            int opcion = stoi(opcionStr);

            switch (opcion) {
            case 1:
                medirEjecucion("Mostrar resumen", app, [&]() {

                    app.reproducirRandom(usuario);

                });
                // Reproduccion interactiva de TODAS las canciones (modo aleatorio)

                break;
            case 2:
                // Reproduccion de FAVORITOS
                medirEjecucion("Mostrar resumen", app, [&]() {

                    app.reproducirFavoritos(usuario);

                });
                break;
            case 3:
                // NUEVA OPCION: Reproducir favoritos del usuario seguido
                medirEjecucion("Mostrar resumen", app, [&]() {

                    app.reproducirFavoritosSeguidos(usuario);

                });
                break;
            case 4:
                // Gestionar Favoritos (Agregar/Quitar)
                medirEjecucion("Mostrar resumen", app, [&]() {

                   app.gestionarFavoritos(usuario);
                });

                break;
            case 5:
                // Gestionar Seguimiento
                medirEjecucion("Mostrar resumen", app, [&]() {

                    app.gestionarSeguimiento(usuario);

                });
                break;
            case 6:
                // Mostrar Resumen
                medirEjecucion("Mostrar resumen", app, [&]() {

                    app.mostrarResumen();
                });
                break;
            case 0:
                sesionActiva = false;
                cout << "Cerrando sesion de " << usuario->getNickname() << "..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
            }
        } catch (...) {
            cout << "Entrada invalida. Por favor, ingrese un numero del menu." << endl;
        }
    }
}

// ------------------------------------------
// FUNCION PRINCIPAL
// ------------------------------------------
int main() {
    // Inicializar el generador de numeros aleatorios una vez
    srand(time(0));
    UdeATunes app;

    cout << "Cargando datos..." << endl;
    app.cargarCanciones(CANCIONES_PATH);
    app.cargarAlbumes(ALBUMES_PATH);
    app.cargarArtistas(ARTISTAS_PATH);
    app.cargarUsuarios(USUARIOS_PATH);
    app.cargarAnuncios(ANUNCIOS_PATH);
    app.vincular();

    // ----------------------------------------------------
    // INICIO DE SESION
    // ----------------------------------------------------
    string nickname;
    Usuario* usuarioActual = nullptr;

    while (usuarioActual == nullptr) {
        cout << "\n==============================================" << endl;
        cout << "  INICIO DE SESION UdeATunes " << endl;
        cout << "==============================================" << endl;
        cout << "Ingrese su nickname (o '0' para salir): ";
        cin >> nickname;

        if (nickname == "0") return 0;

        usuarioActual = app.iniciarSesion(nickname);

        if (usuarioActual == nullptr) {
            cout << "Nickname no encontrado. Intente de nuevo." << endl;
        }
    }

    // ----------------------------------------------------
    // MENU PRINCIPAL
    // ----------------------------------------------------
    ejecutarMenu(app, usuarioActual);

    // Guardar los datos de reproduccion y favoritos antes de salir
    app.guardarUsuarios(USUARIOS_PATH);
    // (Asumiendo que tambien existe un metodo para guardar canciones con reproducciones)
    // app.guardarCanciones(CANCIONES_PATH);
    cout << "\nGracias por usar UdeATunes! Datos guardados." << endl;

    return 0;
}
