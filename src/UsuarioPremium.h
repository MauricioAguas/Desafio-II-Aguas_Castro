/**
 * @file UsuarioPremium.h
 * @brief Clase derivada para usuarios Premium del sistema UdeATunes
 * @authors Mauricio Aguas, Jharlin Castro
 * @date Octubre 2025
 */

#ifndef USUARIO_PREMIUM_H
#define USUARIO_PREMIUM_H

#include "Usuario.h"
#include "ListaEnlazada.h"

// Forward declarations
class Cancion;

/**
 * @class UsuarioPremium
 * @brief Clase que representa un usuario Premium con funcionalidades avanzadas
 * 
 * Los usuarios Premium pagan $19,900 COP mensuales y obtienen:
 * - Calidad de audio 320 kbps
 * - Lista de favoritos hasta 10,000 canciones
 * - Sin publicidad
 * - Navegación avanzada (retroceder canciones)
 * - Capacidad de seguir listas de otros usuarios
 */
class UsuarioPremium : public Usuario {
private:
    ListaEnlazada<Cancion*>* listaFavoritos;         // Lista de canciones favoritas
    ListaEnlazada<UsuarioPremium*>* listasSeguidas;  // Listas de otros usuarios que sigue
    ListaEnlazada<Cancion*>* historialNavegacion;   // Historial para navegación
    
    static const int LIMITE_FAVORITOS = 10000;      // Límite máximo de favoritos
    static const int NAVEGACION_GENERAL = 4;        // Retroceso general
    static const int NAVEGACION_FAVORITOS = 6;      // Retroceso en favoritos
    
public:
    /**
     * @brief Constructor de UsuarioPremium
     * @param nick Nickname único del usuario
     */
    UsuarioPremium(const string& nick);
    
    /**
     * @brief Destructor - libera memoria de listas
     */
    virtual ~UsuarioPremium();
    
    // Métodos virtuales implementados
    /**
     * @brief Obtiene el menú específico para usuarios Premium
     */
    virtual void obtenerMenu() override;
    
    // Gestión de favoritos
    /**
     * @brief Agrega una canción a la lista de favoritos
     * @param cancion Puntero a la canción a agregar
     * @return true si se agregó exitosamente
     */
    bool agregarFavorito(Cancion* cancion);
    
    /**
     * @brief Elimina una canción de la lista de favoritos
     * @param cancion Puntero a la canción a eliminar
     * @return true si se eliminó exitosamente
     */
    bool eliminarFavorito(Cancion* cancion);
    
    /**
     * @brief Verifica si una canción está en favoritos
     * @param cancion Puntero a la canción a verificar
     * @return true si está en favoritos
     */
    bool estaEnFavoritos(Cancion* cancion) const;
    
    /**
     * @brief Reproduce la lista de favoritos
     */
    void reproducirFavoritos();
    
    // Gestión de listas seguidas
    /**
     * @brief Sigue la lista de favoritos de otro usuario Premium
     * @param usuario Usuario Premium cuya lista se quiere seguir
     * @return true si se siguió exitosamente
     */
    bool seguirLista(UsuarioPremium* usuario);
    
    /**
     * @brief Deja de seguir la lista de un usuario
     * @param usuario Usuario cuya lista se deja de seguir
     * @return true si se dejó de seguir exitosamente
     */
    bool dejarDeSeguir(UsuarioPremium* usuario);
    
    // Navegación avanzada
    /**
     * @brief Navega hacia atrás en el historial de reproducción
     * @param posiciones Número de posiciones a retroceder
     * @param enFavoritos true si está reproduciendo favoritos
     * @return Puntero a la canción encontrada
     */
    Cancion* navegarAtras(int posiciones, bool enFavoritos = false);
    
    // Información y estadísticas
    /**
     * @brief Obtiene la cantidad actual de favoritos
     * @return Número de canciones en favoritos
     */
    int obtenerCantidadFavoritos() const;
    
    /**
     * @brief Obtiene la cantidad de listas que sigue
     * @return Número de listas seguidas
     */
    int obtenerCantidadListasSeguidas() const;
    
    /**
     * @brief Verifica si puede agregar más favoritos
     * @return true si no ha alcanzado el límite
     */
    bool puedeAgregarFavoritos() const;

private:
    /**
     * @brief Inicializa las estructuras de datos del usuario Premium
     */
    void inicializarEstructuras();
    
    /**
     * @brief Libera toda la memoria de las listas
     */
    void liberarMemoria();
};

#endif // USUARIO_PREMIUM_H