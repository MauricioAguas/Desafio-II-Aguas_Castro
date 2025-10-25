#pragma once
#include "usuario.h"
#include "lista.h"
#include "cancion.h"
#include <iostream>

class UsuarioPremium : public Usuario {
private:
    Lista<Cancion*> favoritas;
    UsuarioPremium* siguiendoA;

public:
    UsuarioPremium(int id, const string& nick, const string& ciudad,
                   const string& pais, const string& fecha)
        : Usuario(id, nick, ciudad, pais, fecha, "Premium"), siguiendoA(nullptr) {}

    void agregarCancionFavorita(Cancion* c) {
        favoritas.agregar(c);
    }

    void seguirA(UsuarioPremium* otro) {
        if (otro && otro != this)
            siguiendoA = otro;
    }

    void dejarDeSeguir() { siguiendoA = nullptr; }

    UsuarioPremium* getSiguiendoA() const { return siguiendoA; }

    void mostrarInfo() const override {
        cout << "Usuario Premium: " << nickname << " (" << ciudad << ", " << pais << ")";
        if (siguiendoA)
            cout << " | Siguiendo a: " << siguiendoA->getNickname();
        cout << endl;
    }

    const Lista<Cancion*>& getFavoritas() const { return favoritas; }
};

