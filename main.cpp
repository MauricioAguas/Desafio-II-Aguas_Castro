#include <iostream>
#include <string>
#include "UdeATunes.h"
#include "Usuario.h" // Se necesita para manejar el puntero a Usuario

using namespace std;
void mostrarMenu(Usuario* usuario);
void ejecutarMenu(UdeATunes& app, Usuario* usuario);
const string BASE_PATH = "C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio2_Aguas_Castro/data/";

const string CANCIONES_PATH = BASE_PATH + "canciones.txt";
const string ALBUMES_PATH = BASE_PATH + "albumes.txt";
const string ARTISTAS_PATH = BASE_PATH + "artistas.txt";
const string USUARIOS_PATH = BASE_PATH + "usuarios.txt";
const string ANUNCIOS_PATH = BASE_PATH + "anuncios.txt";
// ------------------------------------------

void mostrarMenuPrincipal(Usuario* usuario) {
    cout << "\n==============================================" << endl;
    cout << "  Bienvenido a UdeATunes, " << usuario->getNickname() << " (" << usuario->getTipo() << ")" << endl;
    cout << "==============================================" << endl;
    cout << "1. Reproducir 5 canciones aleatorias 🎧" << endl;
    cout << "2. Gestionar Favoritos (Premium) ⭐" << endl;
    cout << "3. Gestionar Seguimiento (Premium) 👥" << endl;
    cout << "4. Ver Resumen del Sistema (Info general)" << endl;
    cout << "5. Cerrar Sesión y Guardar Cambios" << endl;
    cout << "==============================================" << endl;
    cout << "Seleccione una opción: ";
}


int main() {
    // 1. Inicialización de la aplicación
    UdeATunes app;
    Usuario* usuarioActual = nullptr;
    string nickname;

    cout << "========================================" << endl;
    cout << "         🎧 INICIANDO UDEATUNES 🎶      " << endl;
    cout << "========================================" << endl;

    // 2. Carga de datos
    try {
        cout << "\n[CARGANDO DATOS...]" << endl;
        app.cargarCanciones(CANCIONES_PATH);
        app.cargarAlbumes(ALBUMES_PATH);
        app.cargarArtistas(ARTISTAS_PATH);
        app.cargarUsuarios(USUARIOS_PATH);
        app.cargarAnuncios(ANUNCIOS_PATH);

        cout << "\n[VINCULANDO RELACIONES...]" << endl;
        // La vinculación asigna IDs finales y conecta objetos (Cancion -> Album -> Artista)
        app.vincular();
        cout << "✅ Datos vinculados correctamente." << endl;

    } catch (const exception& e) {
        cerr << "❌ Error fatal durante la carga o vinculación: " << e.what() << endl;
        // Espera de entrada para ver el error antes de cerrar
        cout << "Presione ENTER para salir..." << endl;
        cin.get();
        return 1;
    }

    // 3. Inicio de sesión
    while (usuarioActual == nullptr) {
        cout << "\n----------------------------------------" << endl;
        cout << "       INICIO DE SESIÓN / REGISTRO      " << endl;
        cout << "----------------------------------------" << endl;
        cout << "Ingrese su Nickname (o '0' para salir): ";
        cin >> nickname;

        if (nickname == "0") {
            cout << "Saliendo de UdeATunes..." << endl;
            return 0;
        }

        // Se asume que iniciarSesion maneja la autenticación o creación del usuario.
        usuarioActual = app.iniciarSesion(nickname);

        if (usuarioActual == nullptr) {
            cout << "🚫 Nickname no encontrado. Verifique sus datos o regístrese." << endl;
        } else {
            cout << "\n========================================" << endl;
            cout << "       ✅ BIENVENIDO: " << usuarioActual->getNickname() << " (" << usuarioActual->getTipo() << ")" << endl;
            cout << "========================================" << endl;
        }
    }

    // 4. Ejecutar menú principal
    ejecutarMenu(app, usuarioActual);

    // 5. Persistencia y limpieza
    cout << "\n[GUARDANDO CAMBIOS...]" << endl;
    app.guardarCanciones(CANCIONES_PATH); // Guardar reproducciones
    app.guardarUsuarios(USUARIOS_PATH); // Guardar favoritos/seguimientos/etc.
    cout << "\n¡Gracias por usar UdeATunes!" << endl;

    return 0;
}

// ----------------------------------------------------
// --- LÓGICA DEL MENÚ ---
// ----------------------------------------------------

void mostrarMenu(Usuario* usuario) {
    cout << "\n--- MENÚ PRINCIPAL --- [" << usuario->getTipo() << "]" << endl;
    cout << "1. 🎵 Reproducir todas las canciones (Aleatorio)" << endl;
    cout << "2. ⭐ Reproducir Favoritos" << endl;
    cout << "3. 📝 Gestionar Favoritos" << endl;
    cout << "4. 🫂 Gestionar Seguimiento (Artistas/Usuarios)" << endl;
    cout << "5. ℹ️  Mostrar Resumen (Depuración)" << endl;
    cout << "0. 🚪 Cerrar Sesión y Salir" << endl;
    cout << "Ingrese su opción: ";
}

void ejecutarMenu(UdeATunes& app, Usuario* usuario) {
    string opcionStr;
    bool sesionActiva = true;

    while (sesionActiva) {
        mostrarMenu(usuario);
        // Intentamos leer la opción como string para manejar entradas no numéricas
        if (!(cin >> opcionStr)) {
            cout << "❌ Error de entrada. Reiniciando menú." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            int opcion = stoi(opcionStr);

            switch (opcion) {
            case 1:
                // Llama a la reproducción interactiva de TODAS las canciones (modo aleatorio)
                app.reproducirRandom(usuario);
                break;
            case 2:
                // Llama a la reproducción de FAVORITOS (pide orden: aleatorio o secuencial)
                app.reproducirFavoritos(usuario);
                break;
            case 3:
                app.gestionarFavoritos(usuario);
                break;
            case 4:
                app.gestionarSeguimiento(usuario);
                break;
            case 5:
                app.mostrarResumen();
                break;
            case 0:
                sesionActiva = false;
                cout << "Cerrando sesión de " << usuario->getNickname() << "..." << endl;
                break;
            default:
                cout << "❌ Opción no válida. Intente de nuevo." << endl;
                break;
            }
        } catch (...) {
            cout << "❌ Entrada inválida. Por favor, ingrese un número del menú." << endl;
        }
    }
}
