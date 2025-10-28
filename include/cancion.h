#pragma once
#include <string>
using namespace std;

class Cancion {
private:
    int id;               // ⬅️ ID final de 9 dígitos
    int id_temporal_cancion; // ⬅️ NUEVO: ID de 1 o 2 dígitos del archivo
    string titulo;
    int duracionSeg;
    int idAlbum;
    string rutaArchivo;
    int reproducciones;

public:
    // ⬅️ CONSTRUCTOR CORREGIDO: Ahora el primer parámetro es el ID temporal
    // y ACEPTA el campo opcional 'reproducciones'
    Cancion(int idTemp, const string& titulo, int duracion, int idAlbum, const string& ruta, int reproduccionesIniciales = 0)
        : id(0), id_temporal_cancion(idTemp), titulo(titulo), duracionSeg(duracion), idAlbum(idAlbum), rutaArchivo(ruta), reproducciones(reproduccionesIniciales) {}

    // ⬅️ NUEVO SETTER para asignar el ID de 9 dígitos durante la vinculación
    void setID(int nuevoID) { this->id = nuevoID; }
    int getReproducciones() const { return reproducciones; }
    void contarReproduccion() { reproducciones++; }
    // Getters
    int getId() const { return id; } // Retorna el ID de 9 dígitos (o 0 si no se ha vinculado)
    int getIdTemporal() const { return id_temporal_cancion; } // Útil para la vinculación
    const string& getTitulo() const { return titulo; }
    int getDuracion() const { return duracionSeg; }
    int getIdAlbum() const { return idAlbum; }
    const string& getRutaArchivo() const { return rutaArchivo; }
};
