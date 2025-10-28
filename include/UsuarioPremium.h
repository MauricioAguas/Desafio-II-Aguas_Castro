#pragma once
#include "usuario.h"
#include "lista.h"
#include "cancion.h"
#include <iostream>
#include <sstream>
class UsuarioPremium : public Usuario {
private:
    Lista<Cancion*> favoritas;
    UsuarioPremium* siguiendoA;
    Lista<int*> favoritosIDs;

public:
    UsuarioPremium(int id, const string& nick, const string& ciudad,
                   const string& pais, const string& fecha)
        : Usuario(id, nick, ciudad, pais, fecha, "Premium"), siguiendoA(nullptr) {}

    void agregarCancionFavorita(Cancion* c) {
        favoritas.agregar(c);
    }

    void seguirA(UsuarioPremium* otro) {
        if (otro && otro != this)
            siguiendoA = otro;
    }

    void dejarDeSeguir() { siguiendoA = nullptr; }

    UsuarioPremium* getSiguiendoA() const { return siguiendoA; }

    const Lista<Cancion*>& getFavoritas() const { return favoritas; }
    string obtenerCalidadAudio() const override {
        return "320 kbps (Alta Calidad)";
    }
    bool quitarCancionFavorita(int idCancion) {
        int pos = favoritas.buscarPorId(idCancion); // Usa el método de la Lista
        if (pos != -1) {
            return favoritas.eliminar(pos);
        }
        return false;
    }
    void cargarFavoritosDesdeCSV(const string& csvIds) {
        if (csvIds.empty()) return;

        stringstream ss(csvIds);
        string idStr;

        // Almacenamos temporalmente los IDs para la vinculación
        while (getline(ss, idStr, ',')) {
            int* nuevoId = new int(stoi(idStr));
            // Usamos una lista temporal para IDs, asumiendo que ya existe en UsuarioPremium
            // Si no existe, debes agregar: Lista<int*> favoritosIDs; a la sección private
            favoritosIDs.agregar(nuevoId); // Usaremos una lista temporal de IDs.
        }
    }

    // ... (Asumiendo que has añadido Lista<int*> favoritosIDs; a private)
    // Y necesitas un getter para esa lista temporal
    const Lista<int*>& getFavoritosIDs() const { return favoritosIDs; }
    void mostrarInfo() const override {
        cout << "Usuario Premium: " << nickname << " (" << ciudad << ", " << pais << ")";
        if (siguiendoA)
            cout << " | Siguiendo a: " << siguiendoA->getNickname();
        cout << endl;
    }
};

