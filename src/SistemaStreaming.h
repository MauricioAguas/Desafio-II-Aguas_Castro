/**
 * @file SistemaStreaming.h
 * @brief Controlador principal del sistema UdeATunes
 * @authors Mauricio Aguas, Jharlin Castro
 * @date Octubre 2025
 */

#ifndef SISTEMA_STREAMING_H
#define SISTEMA_STREAMING_H

#include <iostream>
#include <string>
#include "ListaEnlazada.h"
#include "TablaHash.h"

using namespace std;

// Forward declarations
class Usuario;
class UsuarioEstandar;
class Artista;
class Cancion;
class MensajePublicitario;

/**
 * @class SistemaStreaming
 * @brief Controlador principal que gestiona todo el sistema UdeATunes
 * 
 * Esta clase coordina todas las operaciones del sistema de streaming musical,
 * incluyendo gestión de usuarios, reproducción, persistencia y estadísticas.
 */
class SistemaStreaming {
private:
    // Estructuras de datos principales
    TablaHash<string, Usuario*>* usuarios;           // Tabla hash de usuarios por nickname
    ListaEnlazada<Artista*>* artistas;              // Lista de artistas del sistema
    TablaHash<int, Cancion*>* canciones;            // Tabla hash de canciones por ID
    MensajePublicitario* mensajesPublicitarios[50]; // Array fijo de mensajes publicitarios
    
    // Estado del sistema
    Usuario* usuarioActual;    // Usuario que tiene sesión activa
    int totalMensajes;         // Contador de mensajes publicitarios activos
    bool sistemaIniciado;      // Flag de estado del sistema
    
    // Constantes del sistema
    static const int MAX_MENSAJES_PUBLICIDAD = 50;
    static const string RUTA_DATOS;
    
public:
    /**
     * @brief Constructor del sistema de streaming
     */
    SistemaStreaming();
    
    /**
     * @brief Destructor - libera todos los recursos
     */
    ~SistemaStreaming();
    
    // Gestión del sistema
    /**
     * @brief Inicializa el sistema y sus componentes
     * @return true si la inicialización fue exitosa
     */
    bool iniciarSistema();
    
    /**
     * @brief Cierra el sistema y libera recursos
     */
    void cerrarSistema();
    
    // Persistencia de datos
    /**
     * @brief Carga todos los datos desde archivos
     * @return true si la carga fue exitosa
     */
    bool cargarDatos();
    
    /**
     * @brief Guarda todos los datos en archivos
     * @return true si el guardado fue exitoso
     */
    bool guardarDatos();
    
    // Gestión de usuarios
    /**
     * @brief Autentica un usuario en el sistema
     * @param nickname Nombre de usuario
     * @param password Contraseña del usuario
     * @return Puntero al usuario si la autenticación es exitosa, nullptr caso contrario
     */
    Usuario* autenticarUsuario(const string& nickname, const string& password = "");
    
    /**
     * @brief Registra un nuevo usuario en el sistema
     * @param datos Información del usuario a registrar
     * @return true si el registro fue exitoso
     */
    bool registrarUsuario(const string& datos);
    
    // Funcionalidad de streaming
    /**
     * @brief Reproduce una canción de forma aleatoria
     * @return Puntero a la canción seleccionada
     */
    Cancion* reproducirAleatorio();
    
    /**
     * @brief Busca una canción por su identificador de 9 dígitos
     * @param id Identificador único de la canción
     * @return Puntero a la canción si se encuentra, nullptr caso contrario
     */
    Cancion* buscarCancion(int id);
    
    /**
     * @brief Gestiona la publicidad para usuarios estándar
     * @param usuario Usuario estándar que necesita ver publicidad
     * @return Puntero al mensaje publicitario seleccionado
     */
    MensajePublicitario* gestionarPublicidad(UsuarioEstandar* usuario);
    
    // Estadísticas y utilidades
    /**
     * @brief Obtiene estadísticas generales del sistema
     * @return string con las estadísticas formateadas
     */
    string obtenerEstadisticas() const;
    
    /**
     * @brief Obtiene el usuario con sesión activa
     * @return Puntero al usuario actual
     */
    Usuario* getUsuarioActual() const;
    
    /**
     * @brief Verifica si el sistema está iniciado
     * @return true si el sistema está operativo
     */
    bool estaIniciado() const;

private:
    // Métodos auxiliares de carga de datos
    bool cargarUsuarios();
    bool cargarArtistas();
    bool cargarCanciones();
    bool cargarPublicidad();
    
    // Métodos auxiliares de guardado de datos
    bool guardarUsuarios();
    bool guardarArtistas();
    bool guardarCanciones();
    bool guardarPublicidad();
    
    // Utilidades internas
    void inicializarEstructuras();
    void liberarMemoria();
    void crearDatosEjemplo();
};

#endif // SISTEMA_STREAMING_H