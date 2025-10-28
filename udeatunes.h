#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <algorithm>
#include "lista.h"
#include "cancion.h"
#include "album.h"
#include "artista.h"
#include "anuncio.h"
#include "UsuarioEstandar.h"
#include "UsuarioPremium.h"
#include "TiempoPausa.h"
#include "InterfazVisual.h"
#include <list>
using namespace std;
// Constantes
const int MAX_HISTORIAL_PREMIUM = 5; // Índice 0 es la canción actual, hasta 4 previas.

class UdeATunes {
private:
    Lista<Cancion*> canciones;
    Lista<Album*> albumes;
    Lista<Artista*> artistas;
    Lista<Usuario*> usuarios;
    Lista<Anuncio*> anuncios;
    int ultimoAnuncioId;
    int ultimoIdTemporalCancion;
    // Método auxiliar para la lógica de reproducción interactiva
    void sesionReproduccion(Usuario* usuario, const Lista<Cancion*>& lista, bool aleatorio);
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
    void cargarAnuncios(const string& ruta);

    // Método para vincular relaciones
    void vincular();

    // Métodos de depuración
    void mostrarResumen() const;
    //metodo para optener anuncios
    Anuncio* obtenerAnuncioAleatorio();
    Usuario* iniciarSesion(const string& nickname);
    void reproducirRandom(Usuario* usuario);
    Cancion* buscarCancionPorId(int id);
    void gestionarFavoritos(Usuario* usuario);
    void gestionarSeguimiento(Usuario* usuario);
    void guardarUsuarios(const string& ruta) const;
    void listarUsuarios() const;
    void reproducirLista(Usuario* usuario, const Lista<Cancion*>& lista, bool aleatorio); // NUEVA AUXILIAR
    void reproducirFavoritos(Usuario* usuario);
    void guardarCanciones(const string& ruta) const;
    Album* buscarAlbumPorId(int id);
    Artista* buscarArtistaPorId(int id);
};
