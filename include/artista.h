#pragma once
#include <string>
#include "lista.h"
#include "album.h"
using namespace std;

class Artista {
private:
    int id;
    string nombre;
    string pais;
    string genero;

    Lista<int*> albumesIDs;    // IDs leídos desde el archivo
    Lista<Album*> albumes;     // Punteros vinculados luego

public:
    Artista(int id, const string& nombre, const string& pais, const string& genero)
        : id(id), nombre(nombre), pais(pais), genero(genero) {}

    void agregarAlbumID(int idAlbum) {
        int* nuevo = new int(idAlbum);
        albumesIDs.agregar(nuevo);
    }

    void agregarAlbum(Album* a) { albumes.agregar(a); }

    // 🔹 GETTERS
    int getId() const { return id; }
    const string& getNombre() const { return nombre; }
    const string& getPais() const { return pais; }
    const string& getGenero() const { return genero; }

    const Lista<int*>& getAlbumesIDs() const { return albumesIDs; }
    const Lista<Album*>& getAlbumes() const { return albumes; }
};
