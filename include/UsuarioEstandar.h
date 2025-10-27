
#pragma once
#include "usuario.h"
#include <iostream>

class UsuarioEstandar : public Usuario {
private:
    int contadorCanciones;        // NUEVO: contador para publicidad cada 2 canciones

public:
    UsuarioEstandar(int id, const string& nick, const string& ciudad,
                    const string& pais, const string& fecha)
        : Usuario(id, nick, ciudad, pais, fecha, "Estandar"),
        contadorCanciones(0) {}   // NUEVO: inicializar contador en 0

    string obtenerCalidadAudio() const override {
        return "128 kbps (Calidad Estandar)";
    }

    // ===== NUEVOS METODOS PARA PUBLICIDAD =====


    bool necesitaPublicidad() const {
        return (contadorCanciones > 0 && contadorCanciones % 2 == 0);
    }


    void incrementarContador() {
        contadorCanciones++;
    }


    int getContadorCanciones() const {
        return contadorCanciones;
    }

    void reiniciarContador() {
        contadorCanciones = 0;
    }

    void mostrarEstadisticas() const {
        cout << "Usuario: " << getNickname() << " (Estandar)" << endl;
        cout << "Canciones reproducidas: " << contadorCanciones << endl;
        cout << "Proxima publicidad en: " << (2 - (contadorCanciones % 2)) << " canciones" << endl;
    }
};
