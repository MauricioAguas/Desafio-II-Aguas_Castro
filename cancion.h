#ifndef CANCION_H
#define CANCION_H

#include "Elemento.h"
#include <string>
#include <sstream>
using namespace std;

class Cancion : public Elemento {
    string titulo;
    string artista;
    float duracion; // en minutos

public:
    Cancion(int id, const string& titulo, const string& artista, float duracion)
        : Elemento(id), titulo(titulo), artista(artista), duracion(duracion) {}

    string getTitulo() const { return titulo; }
    string getArtista() const { return artista; }
    float getDuracion() const { return duracion; }

    string toString() const override {
        stringstream ss;
        ss << "Cancion(ID: " << id
           << ", Título: " << titulo
           << ", Artista: " << artista
           << ", Duración: " << duracion << " min)";
        return ss.str();
    }
};

#endif
