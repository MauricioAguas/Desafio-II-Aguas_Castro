#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "lista.h"
#include "cancion.h"
#include "album.h"
#include "artista.h"
#include "UsuarioEstandar.h"
#include "UsuarioPremium.h"

using namespace std;

class UdeATunes {
private:
    Lista<Cancion*> canciones;
    Lista<Album*> albumes;
    Lista<Artista*> artistas;
    Lista<Usuario*> usuarios;

public:
    UdeATunes();
    ~UdeATunes();
    const Lista<Usuario*>& getUsuarios() const { return usuarios; }
    const Lista<Cancion*>& getCanciones() const { return canciones; }
    const Lista<Artista*>& getArtistas() const { return artistas; }

    // Métodos de carga
    void cargarCanciones(const string& ruta);
    void cargarAlbumes(const string& ruta);
    void cargarArtistas(const string& ruta);
    void cargarUsuarios(const string& ruta);

    // Método para vincular relaciones
    void vincular();

    // Métodos de depuración
    void mostrarResumen() const;
};
