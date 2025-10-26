#pragma once
#include <string>
using namespace std;

class Usuario {
protected:
    int id;
    string nickname;
    string ciudad;
    string pais;
    string fechaRegistro;
    string tipo;

    // Nuevo campo temporal para vincular luego
    int idSeguidoTemporal;

public:
    Usuario(int id, const string& nick, const string& ciudad, const string& pais,
            const string& fecha, const string& tipo)
        : id(id), nickname(nick), ciudad(ciudad), pais(pais),
        fechaRegistro(fecha), tipo(tipo), idSeguidoTemporal(-1) {}

    virtual ~Usuario() {}
    virtual string obtenerCalidadAudio() const = 0;

    int getId() const { return id; }
    const string& getNickname() const { return nickname; }
    const string& getCiudad() const { return ciudad; }
    const string& getPais() const { return pais; }
    const string& getFechaRegistro() const { return fechaRegistro; }
    const string& getTipo() const { return tipo; }

    // Nuevo setter temporal
    void setIdSeguidoTemporal(int idSeg) { idSeguidoTemporal = idSeg; }
    int getIdSeguidoTemporal() const { return idSeguidoTemporal; }
};
