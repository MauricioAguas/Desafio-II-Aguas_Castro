#ifndef USUARIO_PREMIUM_H
#define USUARIO_PREMIUM_H

#include "usuario.h"
#include "lista.h"
#include "cancion.h"

class UsuarioPremium : public Usuario {
    Lista<Cancion> cancionesFavoritas;    // lista de canciones propias
    UsuarioPremium* siguiendoA;           // referencia al premium seguido
    const int calidadReproduccion = 320;  // kbps
    const bool sinPublicidad = true;

public:
    UsuarioPremium(int id,
                   const string& nickname,
                   const string& ciudad,
                   const string& pais,
                   const string& fechaRegistro)
        : Usuario(id, nickname, ciudad, pais, fechaRegistro),
        cancionesFavoritas(100),
        siguiendoA(nullptr) {}

    // Gestión de canciones favoritas
    bool agregarCancion(Cancion* c) {
        if (cancionesFavoritas.tamanio() >= 10000) return false;
        return cancionesFavoritas.agregar(c);
    }

    void listarFavoritas() const {
        cout << "\n--- Canciones favoritas de " << nickname << " ---\n";
        for (int i = 0; i < cancionesFavoritas.tamanio(); ++i)
            cout << i + 1 << ". " << cancionesFavoritas.obtener(i)->toString() << endl;
    }

    // Seguir a otro premium
    void seguirA(UsuarioPremium* otro) {
        if (otro != nullptr && otro != this)
            siguiendoA = otro;
    }

    void mostrarSeguido() const {
        if (siguiendoA)
            cout << nickname << " sigue a " << siguiendoA->getNickname() << endl;
        else
            cout << nickname << " no sigue a ningún usuario." << endl;
    }

    // Métodos de estado premium
    int getCalidadReproduccion() const { return calidadReproduccion; }
    bool tienePublicidad() const { return !sinPublicidad; }

    // Identificación
    string tipoUsuario() const override { return "Premium"; }

    // Representación textual
    string toString() const override {
        stringstream ss;
        ss << "[" << tipoUsuario() << "] Nick: " << nickname
           << " | Ciudad: " << ciudad
           << " | País: " << pais
           << " | Registro: " << fechaRegistro
           << " | Calidad: " << calidadReproduccion << " kbps"
           << " | Sin Publicidad: " << boolalpha << sinPublicidad;
        return ss.str();
    }
};

#endif
