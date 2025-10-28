#pragma once
#include <iostream>
#include <iomanip>
#include "UdeATunes.h"
#include "lista.h" // Se necesita para acceder a Lista<T>::getIteraciones()
#include "cancion.h" // Se necesita para especificar el tipo en la plantilla Lista<T>
using namespace std;

// ------------------------------------------------------------
// 💾 Estimación del uso total de memoria (versión portable)
// ------------------------------------------------------------
inline size_t calcularMemoriaTotal(const UdeATunes& app) {
    size_t memoria = 0;

    // Tamaño base de las listas
    memoria += sizeof(app.getCanciones());
    memoria += sizeof(app.getAlbumes());
    memoria += sizeof(app.getArtistas());
    memoria += sizeof(app.getUsuarios());

    // Estimación: cada puntero ocupa sizeof(void*)
    memoria += (app.getCanciones().tamanio() +
                app.getAlbumes().tamanio() +
                app.getArtistas().tamanio() +
                app.getUsuarios().tamanio()) * sizeof(void*);

    // Estimación de objetos concretos
    memoria += app.getCanciones().tamanio() * sizeof(Cancion);
    // Nota: El tamaño de Album/Artista/Usuario puede variar, usamos sizeof(void*) como aproximación
    memoria += app.getAlbumes().tamanio() * sizeof(Album);
    memoria += app.getArtistas().tamanio() * sizeof(Artista);
    memoria += app.getUsuarios().tamanio() * sizeof(Usuario);

    // ✅ Ajuste: reservas internas o atributos adicionales
    memoria += 512; // margen base por variables locales pequeñas

    return memoria;
}

// Se necesita para sizeof(Usuario) en calcularMemoriaTotal

// ... (código de calcularMemoriaTotal y mostrarMetricas, se mantienen)

// ------------------------------------------------------------
// ⏱️ Medir y ejecutar una función (CORREGIDO: Limpiar antes de medir)
// ------------------------------------------------------------
template <typename F>
void medirEjecucion(const string& nombre, UdeATunes& app, F funcion) {
    cout << "\n➡ Ejecutando: " << nombre << endl;

    // 1. 💡 REINICIAR: Limpia el contador global de iteraciones
    Lista<Cancion*>::limpiarIteraciones();

    // 2. OBTENER EL CONTEO DE ITERACIONES ANTES DE LA EJECUCIÓN (Ahora es 0)
    int iteracionesInicio = Lista<Cancion*>::getIteraciones();

    // 3. EJECUTAR LA FUNCIÓN (Aquí se generan las iteraciones)
    funcion();

    // 4. OBTENER EL CONTEO DE ITERACIONES DESPUÉS DE LA EJECUCIÓN
    // (Será el total de iteraciones de la función ejecutada)
    int iteracionesFin = Lista<Cancion*>::getIteraciones();

    // 5. MOSTRAR MÉTRICAS
    cout << "--- MÉTRICAS DE EFICIENCIA ---\n";
    // Si iteracionesInicio es 0, el resultado es el valor final.
    cout << "Iteraciones realizadas: " << (iteracionesFin - iteracionesInicio) << endl;
    cout << "Memoria total estimada: " << fixed << setprecision(2)
         << (calcularMemoriaTotal(app) / 1024.0) << " KB" << endl;
}
