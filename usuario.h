#ifndef USUARIO_H
#define USUARIO_H

#include "Elemento.h"
#include <string>
#include <sstream>
using namespace std;

class Usuario : public Elemento {
protected:
    string nickname;     // nombre de usuario único
    string ciudad;
    string pais;
    string fechaRegistro; // formato: "YYYY-MM-DD" o similar

public:
    Usuario(int id,
            const string& nickname,
            const string& ciudad,
            const string& pais,
            const string& fechaRegistro)
        : Elemento(id),
        nickname(nickname),
        ciudad(ciudad),
        pais(pais),
        fechaRegistro(fechaRegistro) {}

    virtual ~Usuario() {}

    // Métodos de acceso
    string getNickname() const { return nickname; }
    string getCiudad() const { return ciudad; }
    string getPais() const { return pais; }
    string getFechaRegistro() const { return fechaRegistro; }

    // Métodos abstractos
    virtual string tipoUsuario() const = 0;

    // Representación común
    virtual string toString() const override {
        stringstream ss;
        ss << "[" << tipoUsuario() << "] ID: " << id
           << " | Nick: " << nickname
           << " | Ciudad: " << ciudad
           << " | País: " << pais
           << " | Registro: " << fechaRegistro;
        return ss.str();
    }
};

#endif
