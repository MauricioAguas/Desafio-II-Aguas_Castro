#pragma once
#include <string>
using namespace std;

class Cancion {
private:
    int id;
    string titulo;
    int duracionSeg;
    int idAlbum;
    string rutaArchivo;

public:
    Cancion(int id, const string& titulo, int duracion, int idAlbum, const string& ruta)
        : id(id), titulo(titulo), duracionSeg(duracion), idAlbum(idAlbum), rutaArchivo(ruta) {}

    // Getters
    int getId() const { return id; }
    const string& getTitulo() const { return titulo; }
    int getDuracion() const { return duracionSeg; }
    int getIdAlbum() const { return idAlbum; }
    const string& getRutaArchivo() const { return rutaArchivo; }
};


