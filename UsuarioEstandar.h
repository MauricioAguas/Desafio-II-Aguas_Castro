#pragma once
#include "usuario.h"
#include <iostream>

class UsuarioEstandar : public Usuario {
public:
    UsuarioEstandar(int id, const string& nick, const string& ciudad,
                    const string& pais, const string& fecha)
        : Usuario(id, nick, ciudad, pais, fecha, "Estandar") {}

    string obtenerCalidadAudio() const override {
        return "128 kbps (Calidad Estándar)";
    }
};
