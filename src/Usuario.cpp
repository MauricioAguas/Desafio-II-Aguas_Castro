/**
 * @file Usuario.cpp
 * @brief Implementación de la clase base abstracta Usuario
 * @authors Mauricio Aguas, Jharlin Castro
 * @date Octubre 2025
 */

#include "Usuario.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructor de la clase Usuario
 * @param nick Nickname único del usuario
 * @param tipo Tipo de membresía (Premium/Estandar)
 */
Usuario::Usuario(const string& nick, const string& tipo) 
    : nickname(nick), tipoMembresia(tipo), activo(true) {
    fechaInscripcion = "2025-10-21"; // Por simplicidad, fecha fija por ahora
    ciudad = "";
    pais = "";
}

/**
 * @brief Destructor virtual de la clase Usuario
 */
Usuario::~Usuario() {
    // Destructor base - las clases derivadas manejan su memoria específica
}

/**
 * @brief Inicia sesión del usuario (implementación base)
 * @param password Contraseña del usuario
 * @return true si el inicio de sesión es exitoso
 */
bool Usuario::iniciarSesion(const string& password) {
    cout << "Iniciando sesion para usuario: " << nickname << endl;
    cout << "Tipo de membresia: " << tipoMembresia << endl;
    activo = true;
    return true;
}

/**
 * @brief Reproduce una canción según las características del usuario
 * @param nombreCancion Nombre de la canción a reproducir
 */
void Usuario::reproducirCancion(const string& nombreCancion) {
    cout << "Reproduciendo: " << nombreCancion << " para " << nickname << endl;
    cout << "Calidad de audio: " << (tipoMembresia == "Premium" ? "320 kbps" : "128 kbps") << endl;
}

/**
 * @brief Cierra la sesión actual del usuario
 */
void Usuario::cerrarSesion() {
    cout << "Cerrando sesion de " << nickname << endl;
    activo = false;
}

/**
 * @brief Obtiene el nickname del usuario
 * @return string con el nickname
 */
string Usuario::getNickname() const {
    return nickname;
}

/**
 * @brief Obtiene el tipo de membresía
 * @return string con el tipo de membresía
 */
string Usuario::getTipoMembresia() const {
    return tipoMembresia;
}

/**
 * @brief Verifica si el usuario está activo
 * @return true si el usuario está activo
 */
bool Usuario::estaActivo() const {
    return activo;
}