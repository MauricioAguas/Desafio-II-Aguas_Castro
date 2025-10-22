#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
protected:
    string nickname;
    string tipoMembresia;
    string ciudad;
    string pais;
    string fechaInscripcion;
    bool activo;

public:
    Usuario(const string& nick, const string& tipo);
    virtual ~Usuario();

    virtual void obtenerMenu() = 0;
    virtual bool iniciarSesion(const string& password);
    virtual void reproducirCancion(const string& nombreCancion);

    void cerrarSesion();
    string getNickname() const;
    string getTipoMembresia() const;
    bool estaActivo() const;
};

#endif
