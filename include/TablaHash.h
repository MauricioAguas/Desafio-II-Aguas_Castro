/**
 * @file TablaHash.h
 * @brief Implementación de Tabla Hash genérica sin usar STL
 * @authors Mauricio Aguas, Jharlin Castro
 * @date Octubre 2025
 */

#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <string>
#include <iostream>
using namespace std;

/**
 * @class TablaHash
 * @brief Tabla hash genérica implementada sin STL
 * 
 * Proporciona operaciones de inserción, búsqueda y eliminación con complejidad
 * O(1) promedio. Utiliza sondeo lineal para resolución de colisiones.
 * 
 * @tparam K Tipo de la clave
 * @tparam V Tipo del valor
 */
template<typename K, typename V>
class TablaHash {
private:
    /**
     * @struct Entrada
     * @brief Estructura interna que representa una entrada de la tabla
     */
    struct Entrada {
        K clave;          // Clave de la entrada
        V valor;          // Valor almacenado
        bool ocupada;     // Flag que indica si la entrada está ocupada
        bool eliminada;   // Flag para lazy deletion
        
        /**
         * @brief Constructor de entrada vacía
         */
        Entrada() : ocupada(false), eliminada(false) {}
        
        /**
         * @brief Constructor de entrada con datos
         * @param k Clave
         * @param v Valor
         */
        Entrada(const K& k, const V& v) : clave(k), valor(v), ocupada(true), eliminada(false) {}
    };
    
    Entrada* tabla;        // Array dinámico de entradas
    int capacidad;         // Tamaño total de la tabla
    int elementos;         // Número de elementos activos
    double factorCarga;    // Factor de carga máximo permitido
    
public:
    /**
     * @brief Constructor con capacidad inicial
     * @param capacidadInicial Tamaño inicial de la tabla (debe ser primo)
     */
    TablaHash(int capacidadInicial = 101);
    
    /**
     * @brief Constructor de copia
     * @param otra Tabla a copiar
     */
    TablaHash(const TablaHash<K,V>& otra);
    
    /**
     * @brief Destructor - libera memoria
     */
    ~TablaHash();
    
    /**
     * @brief Operador de asignación
     * @param otra Tabla a asignar
     * @return Referencia a esta tabla
     */
    TablaHash<K,V>& operator=(const TablaHash<K,V>& otra);
    
    // Operaciones principales
    /**
     * @brief Inserta un par clave-valor en la tabla
     * @param clave Clave a insertar
     * @param valor Valor asociado
     * @return true si se insertó exitosamente
     */
    bool insertar(const K& clave, const V& valor);
    
    /**
     * @brief Busca un valor por su clave
     * @param clave Clave a buscar
     * @return Puntero al valor si se encuentra, nullptr caso contrario
     */
    V* buscar(const K& clave);
    
    /**
     * @brief Busca un valor por su clave (versión const)
     * @param clave Clave a buscar
     * @return Puntero const al valor si se encuentra, nullptr caso contrario
     */
    const V* buscar(const K& clave) const;
    
    /**
     * @brief Elimina una entrada por su clave
     * @param clave Clave del elemento a eliminar
     * @return true si se eliminó exitosamente
     */
    bool eliminar(const K& clave);
    
    // Información de la tabla
    /**
     * @brief Obtiene el número de elementos activos
     * @return Número de elementos
     */
    int obtenerTamano() const;
    
    /**
     * @brief Verifica si la tabla está vacía
     * @return true si no hay elementos
     */
    bool estaVacia() const;
    
    /**
     * @brief Obtiene el factor de carga actual
     * @return Factor de carga (elementos/capacidad)
     */
    double obtenerFactorCarga() const;
    
    /**
     * @brief Elimina todos los elementos de la tabla
     */
    void limpiar();
    
    // Operador de acceso
    /**
     * @brief Operador de acceso por clave (con inserción automática)
     * @param clave Clave a buscar/insertar
     * @return Referencia al valor
     */
    V& operator[](const K& clave);
    
private:
    /**
     * @brief Función hash para strings
     * @param clave String a hashear
     * @return Valor hash
     */
    int hash(const string& clave) const;
    
    /**
     * @brief Función hash para enteros
     * @param clave Entero a hashear
     * @return Valor hash
     */
    int hash(int clave) const;
    
    /**
     * @brief Función hash genérica para otros tipos
     * @param clave Clave a hashear
     * @return Valor hash
     */
    template<typename T>
    int hash(const T& clave) const;
    
    /**
     * @brief Redimensiona la tabla cuando el factor de carga es alto
     */
    void redimensionar();
    
    /**
     * @brief Encuentra la siguiente capacidad prima
     * @param n Número base
     * @return Siguiente número primo mayor a n
     */
    int siguientePrimo(int n) const;
    
    /**
     * @brief Verifica si un número es primo
     * @param n Número a verificar
     * @return true si es primo
     */
    bool esPrimo(int n) const;
    
    /**
     * @brief Copia todos los elementos de otra tabla
     * @param otra Tabla fuente
     */
    void copiar(const TablaHash<K,V>& otra);
    
    /**
     * @brief Libera toda la memoria de la tabla
     */
    void liberar();
};

// Incluir implementación (necesario para templates)
#include "TablaHash.tpp"

#endif // TABLA_HASH_H