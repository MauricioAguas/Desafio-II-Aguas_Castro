#pragma once
#include <iostream>
#include <string>
#include "usuario.h"
#include "UsuarioEstandar.h"

using namespace std;

class MenuInteractivo {
public:
    // Muestra el menu principal
    static void mostrarMenuPrincipal(Usuario* usuario) {
        cout << "\n=======================================" << endl;
        cout << "           UDEATUNES - MENU" << endl;
        cout << "=======================================" << endl;
        cout << "Usuario: " << usuario->getNickname() << endl;
        cout << "Tipo: " << usuario->getTipo() << endl;

        // Mostrar contador si es estandar
        if (usuario->getTipo() == "Estandar") {
            UsuarioEstandar* usuarioEst = static_cast<UsuarioEstandar*>(usuario);
            cout << "Canciones: " << usuarioEst->getContadorCanciones() << endl;
        }

        cout << "=======================================" << endl;
        cout << "1. Reproducir musica aleatoria" << endl;

        if (usuario->getTipo() == "Premium") {
            cout << "2. Mi lista de favoritos" << endl;
            cout << "3. Navegar hacia atras" << endl;
        } else {
            cout << "2. Ver mi perfil" << endl;
            cout << "3. Upgrade a Premium ($19,900)" << endl;
        }

        cout << "4. Ver estadisticas" << endl;
        cout << "0. Cerrar sesion" << endl;
        cout << "=======================================" << endl;
    }

    // Procesa la opcion elegida por el usuario
    static bool procesarOpcion(int opcion, Usuario* usuario) {
        switch(opcion) {
        case 2:
            if (usuario->getTipo() == "Premium") {
                mostrarFavoritos();
            } else {
                mostrarPerfil(usuario);
            }
            return false;

        case 3:
            if (usuario->getTipo() == "Premium") {
                navegarAtras();
            } else {
                mostrarUpgrade();
            }
            return false;

        case 4:
            mostrarEstadisticas(usuario);
            return false;

        case 0:
            cout << "Cerrando sesion... Hasta luego!" << endl;
            return true; // Salir

        default:
            cout << "Opcion invalida" << endl;
            return false;
        }
    }

private:
    // Funciones simples para cada opcion
    static void mostrarFavoritos() {
        cout << "\n=== FAVORITOS ===" << endl;
        cout << "Funcionalidad en desarrollo" << endl;
        pausar();
    }

    static void mostrarPerfil(Usuario* usuario) {
        cout << "\n=== PERFIL ===" << endl;
        cout << "Nickname: " << usuario->getNickname() << endl;
        cout << "Tipo: " << usuario->getTipo() << endl;
        cout << "Ciudad: " << usuario->getCiudad() << endl;
        cout << "Pais: " << usuario->getPais() << endl;

        if (usuario->getTipo() == "Estandar") {
            UsuarioEstandar* usuarioEst = static_cast<UsuarioEstandar*>(usuario);
            cout << "Canciones reproducidas: " << usuarioEst->getContadorCanciones() << endl;
        }

        pausar();
    }

    static void mostrarUpgrade() {
        cout << "\n=== UPGRADE A PREMIUM ===" << endl;
        cout << "Beneficios:" << endl;
        cout << "- Sin publicidad" << endl;
        cout << "- Calidad 320 kbps" << endl;
        cout << "- Lista de favoritos" << endl;
        cout << "- Navegar hacia atras" << endl;
        cout << "\nPrecio: $19,900 COP/mes" << endl;
        pausar();
    }

    static void navegarAtras() {
        cout << "\n=== NAVEGAR ATRAS ===" << endl;
        cout << "Funcionalidad en desarrollo" << endl;
        pausar();
    }

    static void mostrarEstadisticas(Usuario* usuario) {
        cout << "\n=== ESTADISTICAS ===" << endl;
        cout << "Usuario: " << usuario->getNickname() << endl;

        if (usuario->getTipo() == "Estandar") {
            UsuarioEstandar* usuarioEst = static_cast<UsuarioEstandar*>(usuario);
            cout << "Canciones: " << usuarioEst->getContadorCanciones() << endl;
            cout << "Publicidad vista: " << (usuarioEst->getContadorCanciones() / 2) << endl;
        }

        pausar();
    }

    // Pausa para que el usuario lea
    static void pausar() {
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
};
