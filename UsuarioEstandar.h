#ifndef USUARIO_ESTANDAR_H
#define USUARIO_ESTANDAR_H

#include "Usuario.h"
#include <sstream>

class UsuarioEstandar : public Usuario {
    const int calidadReproduccion = 128;  // kbps
    const bool sinPublicidad = false;

public:
    UsuarioEstandar(int id,
                    const string& nickname,
                    const string& ciudad,
                    const string& pais,
                    const string& fechaRegistro)
        : Usuario(id, nickname, ciudad, pais, fechaRegistro) {}

    // Propiedades específicas del estándar
    int getCalidadReproduccion() const { return calidadReproduccion; }
    bool tienePublicidad() const { return !sinPublicidad; }

    // Implementación obligatoria
    string tipoUsuario() const override { return "Estandar"; }

    // Representación textual
    string toString() const override {
        stringstream ss;
        ss << "[" << tipoUsuario() << "] Nick: " << nickname
           << " | Ciudad: " << ciudad
           << " | País: " << pais
           << " | Registro: " << fechaRegistro
           << " | Calidad: " << calidadReproduccion << " kbps"
           << " | Con Publicidad: " << boolalpha << tienePublicidad();
        return ss.str();
    }
};

#endif
