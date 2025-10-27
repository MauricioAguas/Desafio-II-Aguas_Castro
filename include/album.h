#pragma once
#include <string>
#include "lista.h"
#include "cancion.h"
using namespace std;

class Album {
private:
    int id;
    string titulo;
    int anio;
    int idArtista;

    // Guardamos IDs y punteros
    Lista<int*> cancionesIDs;       // IDs de canciones (desde el archivo)
    Lista<Cancion*> canciones;      // Punteros reales vinculados

public:
    Album(int id, const string& titulo, int anio, int idArtista)
        : id(id), titulo(titulo), anio(anio), idArtista(idArtista) {}

    // Métodos para agregar canciones
    void agregarCancionID(int idCancion) {
        int* nuevo = new int(idCancion);
        cancionesIDs.agregar(nuevo);
    }

    void agregarCancion(Cancion* c) { canciones.agregar(c); }

    // 🔹 GETTERS
    int getId() const { return id; }
    const string& getTitulo() const { return titulo; }
    int getAnio() const { return anio; }
    int getIdArtista() const { return idArtista; }

    // Estos dos métodos te permitirán acceder desde UdeATunes y el main:
    const Lista<int*>& getCancionesIDs() const { return cancionesIDs; }
    const Lista<Cancion*>& getCanciones() const { return canciones; }

    // (opcional destructor si luego quieres liberar IDs)
};
