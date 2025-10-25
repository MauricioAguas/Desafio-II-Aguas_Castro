#pragma once
#include "usuario.h"
#include <iostream>

class UsuarioEstandar : public Usuario {
public:
    UsuarioEstandar(int id, const string& nick, const string& ciudad,
                    const string& pais, const string& fecha)
        : Usuario(id, nick, ciudad, pais, fecha, "Estandar") {}

    void mostrarInfo() const override {
        cout << "Usuario Estandar: " << nickname << " (" << ciudad << ", " << pais << ")\n";
    }
};
