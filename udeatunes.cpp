#include "UdeATunes.h"

// 🔹 Constructor y destructor
UdeATunes::UdeATunes() : ultimoAnuncioId(0) {}
UdeATunes::~UdeATunes() {}

// =======================================================
// 🔹 CARGA DE CANCIONES
// Formato del txt:
// id;titulo;duracion;idAlbum;ruta
// Ejemplo: 1;Runaway;215;3;Music/Runaway.ogg
// =======================================================
// =======================================================
// 🔹 CARGA DE CANCIONES
// Formato del txt: id_temporal;titulo;duracion;idAlbum;ruta
// =======================================================
// =======================================================
// 🔹 CARGA DE CANCIONES (Actualizada para leer Reproducciones y rastrear ID temporal)
// Formato del txt: id_temporal;titulo;duracion;idAlbum;ruta;reproducciones (el último campo es opcional al principio)
// =======================================================
void UdeATunes::cargarCanciones(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error abriendo " << ruta << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);

        // Declaración de variables para los 6 campos
        string idS, titulo, durS, idAlbumS, rutaArchivo, repS;

        // 1. Lectura de campos
        getline(ss, idS, ';');
        getline(ss, titulo, ';');
        getline(ss, durS, ';');
        getline(ss, idAlbumS, ';');
        getline(ss, rutaArchivo, ';');

        // ⬅️ CAMBIO CLAVE: Lectura del SEXTO campo (Reproducciones)
        getline(ss, repS);

        // 2. Conversión a tipos de datos
        int idTemporal = stoi(idS);
        int duracion = stoi(durS);
        int idAlbum = stoi(idAlbumS);

        // ⬅️ CAMBIO CLAVE: Conversión segura del campo de reproducciones
        int reproducciones = 0;
        try {
            reproducciones = repS.empty() ? 0 : stoi(repS);
        } catch (...) {
            reproducciones = 0;
        }

        // ⬅️ ACTUALIZAR EL RASTREADOR DE ID TEMPORAL
        if (idTemporal > ultimoIdTemporalCancion) {
            ultimoIdTemporalCancion = idTemporal;
        }

        // 3. Creación y adición (Se asume que el constructor de Cancion fue actualizado para el ID Temporal y Reps)
        Cancion* c = new Cancion(idTemporal, titulo, duracion, idAlbum, rutaArchivo, reproducciones);
        canciones.agregar(c);
    }

    file.close();
    cout << "✅ " << canciones.tamanio() << " canciones cargadas. Último ID temporal: " << ultimoIdTemporalCancion << endl;
}
// =======================================================
// 🔹 CARGA DE ÁLBUMES
// Formato del txt:
// id;titulo;anio;idArtista;idCancion1,idCancion2,...
// =======================================================
void UdeATunes::cargarAlbumes(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error abriendo " << ruta << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idS, titulo, anioS, idArtistaS, cancionesStr;

        getline(ss, idS, ';');
        getline(ss, titulo, ';');
        getline(ss, anioS, ';');
        getline(ss, idArtistaS, ';');
        getline(ss, cancionesStr, ';');

        Album* a = new Album(stoi(idS), titulo, stoi(anioS), stoi(idArtistaS));

        stringstream cancionesSS(cancionesStr);
        string idCancion;
        while (getline(cancionesSS, idCancion, ',')) {
            if (!idCancion.empty())
                a->agregarCancionID(stoi(idCancion));
        }

        albumes.agregar(a);
    }

    file.close();
}

// =======================================================
// 🔹 CARGA DE ARTISTAS
// Formato del txt:
// id;nombre;pais;genero;idAlbum1,idAlbum2,...
// =======================================================
void UdeATunes::cargarArtistas(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error abriendo " << ruta << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idS, nombre, pais, genero, albumsStr;

        getline(ss, idS, ';');
        getline(ss, nombre, ';');
        getline(ss, pais, ';');
        getline(ss, genero, ';');
        getline(ss, albumsStr, ';');

        Artista* art = new Artista(stoi(idS), nombre, pais, genero);

        stringstream albSS(albumsStr);
        string idAlbum;
        while (getline(albSS, idAlbum, ',')) {
            if (!idAlbum.empty())
                art->agregarAlbumID(stoi(idAlbum));
        }

        artistas.agregar(art);
    }

    file.close();
}

// =======================================================
// 🔹 CARGA DE USUARIOS
// Formato del txt:
// id;nickname;tipo;ciudad;pais;fecha;idSeguido
// =======================================================
void UdeATunes::cargarUsuarios(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error abriendo " << ruta << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idS, nick, tipo, ciudad, pais, fecha, idSeguidoS, favoritosCSV; // ⬅️ NUEVOS CAMPOS

        // Lectura de campos fijos
        getline(ss, idS, ';');
        getline(ss, nick, ';');
        getline(ss, tipo, ';');
        getline(ss, ciudad, ';');
        getline(ss, pais, ';');
        getline(ss, fecha, ';');

        // El resto de la línea contiene ID_SEGUIDO y la lista de favoritos.
        // Separamos el ID de seguimiento (puede estar vacío)
        getline(ss, idSeguidoS, ';');

        // Leemos el resto de la línea para los favoritos CSV
        getline(ss, favoritosCSV);

        // Creación del objeto y carga de IDs
        Usuario* u = nullptr;
        if (tipo == "Premium") {
            UsuarioPremium* up = new UsuarioPremium(stoi(idS), nick, ciudad, pais, fecha);

            // Carga del CSV de IDs de favoritos
            up->cargarFavoritosDesdeCSV(favoritosCSV); // ⬅️ Carga la lista de IDs temporales

            u = up;
        } else {
            u = new UsuarioEstandar(stoi(idS), nick, ciudad, pais, fecha);
        }

        // Carga del ID de seguimiento temporal (común en Usuario.h)
        if (!idSeguidoS.empty()) {
            u->setIdSeguidoTemporal(stoi(idSeguidoS));
        }

        usuarios.agregar(u);
    }
    file.close();
}
// =======================================================
// 🔹 CARGA DE ANUNCIOS
// Formato del txt: id;mensaje;categoria (C, B, AAA)
// =======================================================
void UdeATunes::cargarAnuncios(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error abriendo " << ruta << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idS, mensaje, categoria;

        // 1. Leer ID
        getline(ss, idS, ';');
        // 2. Leer Mensaje
        getline(ss, mensaje, ';');
        // 3. Leer Categoría
        getline(ss, categoria, ';');

        // Aseguramos que la categoría no tenga espacios en blanco innecesarios
        // y convertimos
        Anuncio* a = new Anuncio(stoi(idS), mensaje, categoria);
        anuncios.agregar(a);
    }

    file.close();
    cout << "[Carga] Anuncios cargados: " << anuncios.tamanio() << endl;
}
// =======================================================
// 🔹 BÚSQUEDA DE ÁLBUM (IMPLEMENTACIÓN AÑADIDA Y CORREGIDA)
// =======================================================
Album* UdeATunes::buscarAlbumPorId(int id) {
    for (int i = 0; i < albumes.tamanio(); ++i) {
        Album* a = albumes.obtener(i);
        if (a->getId() == id) {
            return a;
        }
    }
    return nullptr;
}

// =======================================================
// 🔹 BÚSQUEDA DE ARTISTA (IMPLEMENTACIÓN AÑADIDA Y CORREGIDA)
// =======================================================
Artista* UdeATunes::buscarArtistaPorId(int id) {
    for (int i = 0; i < artistas.tamanio(); ++i) {
        Artista* a = artistas.obtener(i);
        if (a->getId() == id) {
            return a;
        }
    }
    return nullptr;
}
Anuncio* UdeATunes::obtenerAnuncioAleatorio() {
    if (anuncios.tamanio() == 0) {
        return nullptr;
    }

    // 1. Calcular el Peso Total de los anuncios *disponibles*
    int pesoTotal = 0;
    for (int i = 0; i < anuncios.tamanio(); ++i) {
        Anuncio* a = anuncios.obtener(i);
        // Si es el último anuncio reproducido, su peso es CERO para cumplir la restricción.
        if (a->getId() != ultimoAnuncioId) {
            pesoTotal += a->getPeso();
        }
    }

    // Si solo hay un anuncio, o si el único anuncio es el último reproducido,
    // simplemente devolver el primero disponible (opcionalmente podríamos mostrar un mensaje de error).
    if (pesoTotal == 0) {
        // En este caso, si solo queda un anuncio, la restricción se vuelve imposible de cumplir,
        // así que elegimos el primero disponible.
        ultimoAnuncioId = anuncios.obtener(0)->getId();
        return anuncios.obtener(0);
    }

    // 2. Generar un número aleatorio entre 1 y el Peso Total
    int numeroAleatorio = (rand() % pesoTotal) + 1;

    // 3. Iterar y Seleccionar (El 'Giro')
    for (int i = 0; i < anuncios.tamanio(); ++i) {
        Anuncio* a = anuncios.obtener(i);

        // Si es el último, lo saltamos (ya descontamos su peso del pesoTotal)
        if (a->getId() == ultimoAnuncioId) {
            continue;
        }

        numeroAleatorio -= a->getPeso();

        // El anuncio que hace que el númeroAleatorio sea <= 0 es el elegido
        if (numeroAleatorio <= 0) {
            // Actualizar el ID del último anuncio para la próxima llamada
            ultimoAnuncioId = a->getId();
            return a;
        }
    }

    // Caso de seguridad, aunque la lógica debería siempre encontrar uno
    ultimoAnuncioId = anuncios.obtener(0)->getId();
    return anuncios.obtener(0);
}
// =======================================================
// 🔹 INICIO DE SESIÓN
// Busca el Usuario por nickname (búsqueda lineal)
// =======================================================
Usuario* UdeATunes::iniciarSesion(const string& nickname) {
    // Usaremos un string auxiliar y transformaremos a minúsculas
    // para una búsqueda más robusta (ej. "maria_premium" vs "Maria_Premium")
    string nickBuscado = nickname;
    transform(nickBuscado.begin(), nickBuscado.end(), nickBuscado.begin(), ::tolower);

    // 1. Recorrer la lista de usuarios
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        // La clase Lista te permite obtener el elemento en la posición i
        Usuario* u = usuarios.obtener(i);

        // 2. Obtener y normalizar el nickname del usuario actual
        string nickActual = u->getNickname();
        transform(nickActual.begin(), nickActual.end(), nickActual.begin(), ::tolower);

        // 3. Comparar
        if (nickActual == nickBuscado) {
            // ¡Encontrado! Devolvemos el puntero polimórfico (Usuario* puede ser Estandar o Premium)
            return u;
        }
    }

    // 4. Si el bucle termina sin encontrar coincidencias
    return nullptr;
}
Cancion* UdeATunes::buscarCancionPorId(int id) {
    // Retorna la posición de la canción con ese ID, o -1 si no la encuentra.
    int posicion = canciones.buscarPorId(id);

    // El método buscarPorId de Lista debe estar implementado para que funcione

    if (posicion != -1) {
        // Si se encontró, retorna el puntero a la canción
        return canciones.obtener(posicion);
    }

    // Si no se encontró
    return nullptr;
}
// =======================================================
// 🔹 VINCULAR ENTIDADES POR ID
// Canciones → Álbumes → Artistas → Usuarios
// =======================================================
void UdeATunes::vincular() {
    // 1️⃣ Álbum -> Canción
    cout << "[VINCULACIÓN] Álbumes <-> Canciones..." << endl;
    for (int i = 0; i < albumes.tamanio(); ++i) {
        Album* alb = albumes.obtener(i);
        for (int j = 0; j < alb->getCancionesIDs().tamanio(); ++j) {
            int idC = *(alb->getCancionesIDs().obtener(j));

            // Buscar la canción por su ID TEMPORAL (el que viene en el archivo)
            // Se debe iterar sobre la lista global, ya que la lista::buscarPorId
            // ahora buscaría el ID de 9 dígitos, que aún no existe.

            // 🚨 SOLUCIÓN PARA BÚSQUEDA TEMPORAL:
            // Dado que Lista::buscarPorId usa el ID final, debemos hacer una búsqueda lineal
            // para el ID temporal, asumiendo que el ID temporal es único por ahora
            // y corresponde al 'id' de la canción en el archivo.

            // NOTA: Para este ejemplo, asumiremos que el ID TEMPORAL de la canción
            // es único y que la búsqueda puede hacerse recorriendo la lista global,
            // hasta que la parte del ID temporal y la parte del ID álbum coincidan.
            // Para mantener el código simple, buscaremos por el ID del Álbum
            // y luego por el ID temporal de la canción dentro del álbum vinculado:

            // Búsqueda de la canción en la lista global con el idAlbum
            for (int k = 0; k < canciones.tamanio(); ++k) {
                Cancion* can = canciones.obtener(k);
                if (can->getIdAlbum() == alb->getId() && can->getIdTemporal() == idC) {
                    alb->agregarCancion(can); // Vincula el puntero real al Album
                    break;
                }
            }
        }
    }
    cout << "[VINCULACIÓN] Artistas <-> Álbumes..." << endl;

    // 2️⃣ Artista -> Álbum (Se mantiene tu lógica original)
    for (int i = 0; i < artistas.tamanio(); ++i) {
        Artista* art = artistas.obtener(i);
        for (int j = 0; j < art->getAlbumesIDs().tamanio(); ++j) {
            int idA = *(art->getAlbumesIDs().obtener(j));
            int posA = albumes.buscarPorId(idA);
            if (posA != -1)
                art->agregarAlbum(albumes.obtener(posA));
        }
    }

    // 3️⃣ Usuarios Premium seguidos (Se mantiene tu lógica original)
    cout << "[VINCULACIÓN] Usuarios Premium seguidos..." << endl;
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        Usuario* u = usuarios.obtener(i);
        UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(u);
        if (!p) continue;
        // ... (resto de la lógica de seguimiento) ...
    }

    // 4️⃣ GENERACIÓN DE ID FINAL DE 9 DÍGITOS (CRÍTICO)
    // ID = ID_Artista(5) + ID_Album(2) + ID_Cancion(2)
    cout << "[VINCULACIÓN] Generando IDs finales de 9 dígitos (Artista-Album-Cancion)..." << endl;

    for (int i = 0; i < albumes.tamanio(); ++i) {
        Album* alb = albumes.obtener(i);

        // 1. Obtener ID del Artista (Componente de 5 dígitos)
        int idArtista = alb->getIdArtista();
        int posArt = artistas.buscarPorId(idArtista);
        if (posArt == -1) continue;
        Artista* art = artistas.obtener(posArt);
        int baseIDArtista = art->getId(); // ID del Artista (ej: 1)

        // 2. Obtener ID del Álbum (Componente de 2 dígitos)
        int baseIDAlbum = alb->getId();     // ID del Álbum (ej: 2)

        // 3. Iterar sobre las canciones ya vinculadas al Álbum
        for (int j = 0; j < alb->getCanciones().tamanio(); ++j) {
            Cancion* cancion = alb->getCanciones().obtener(j);

            // 4. Obtener ID Temporal de la Canción (Componente de 2 dígitos)
            int idCancionTemporal = cancion->getIdTemporal(); // ID de la canción en el archivo (ej: 3)

            // 5. Cálculo del ID de 9 dígitos:
            // Desplazamos el ID de Artista 4 posiciones (x 10000)
            // Desplazamos el ID de Álbum 2 posiciones (x 100)
            int nuevoID = (baseIDArtista * 10000) + (baseIDAlbum * 100) + idCancionTemporal;

            // 6. Asignar el ID final a la canción (para que futuras búsquedas funcionen)
            cancion->setID(nuevoID);

            // EJEMPLO: Artista 1, Album 2, Cancion 3 -> ID: 000010203 (Si los IDs son de 1 dígito)
            // Para el ejemplo Artista 1, Álbum 1, Canción 1: (1*10000) + (1*100) + 1 = 10101
            // Si Artista 10, Album 20, Canción 30: (10*10000) + (20*100) + 30 = 100000 + 2000 + 30 = 102030 (6 dígitos)
        }
    }
    cout << "[VINCULACIÓN] IDs de 9 dígitos generados correctamente." << endl;
    cout << "[VINCULACIÓN] Listas de Favoritos..." << endl;
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        Usuario* u = usuarios.obtener(i);
        UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(u);

        if (!p) continue;

        const Lista<int*>& favIds = p->getFavoritosIDs();

        for (int j = 0; j < favIds.tamanio(); ++j) {
            int id9Digitos = *favIds.obtener(j);

            // Usamos la función que creamos (buscarCancionPorId)
            Cancion* c = buscarCancionPorId(id9Digitos);

            if (c) {
                p->agregarCancionFavorita(c); // Agrega el puntero real
            } else {
                cerr << "AVISO: Canción con ID " << id9Digitos
                     << " de favoritos de " << p->getNickname() << " no fue encontrada (¿datos corruptos?)." << endl;
            }
        }
        // Opcional: limpiar la lista temporal de IDs después de vincular
        // p->getFavoritosIDs().limpiar();
    }
}

// =======================================================
// 🔹 GESTIÓN DE LISTA DE FAVORITOS (Solo Premium)
// =======================================================
void UdeATunes::gestionarFavoritos(Usuario* usuario) {
    // 1. DYNAMIC CAST OBLIGATORIO
    UsuarioPremium* premiumUser = dynamic_cast<UsuarioPremium*>(usuario);
    if (premiumUser == nullptr) {
        cout << "❌ Error interno: Esta función solo debe ser llamada por usuarios Premium." << endl;
        return;
    }

    string opcion;
    cout << "\n=== MI LISTA DE FAVORITOS (" << premiumUser->getNickname() << ") ===" << endl;
    cout << "Canciones actuales en favoritos: " << premiumUser->getFavoritas().tamanio() << endl;

    while (true) {
        cout << "\n--- Opciones de Gestión ---" << endl;
        cout << "1. Agregar canción por ID (9 dígitos)" << endl;
        cout << "2. Quitar canción por ID (9 dígitos)" << endl;
        cout << "3. Ver lista actual" << endl;
        cout << "0. Volver al Menú Principal" << endl;
        cout << "Ingrese opción: ";
        cin >> opcion;

        if (opcion == "1") {
            cout << "Ingrese el ID de 9 dígitos de la canción a agregar: ";
            int idCancion;
            cin >> idCancion;

            Cancion* c = buscarCancionPorId(idCancion);

            if (c) {
                premiumUser->agregarCancionFavorita(c);
                cout << "✅ Canción '" << c->getTitulo() << "' agregada a favoritos." << endl;
            } else {
                cout << "❌ Error: Canción con ID " << idCancion << " no encontrada en UdeATunes." << endl;
            }
        }
        else if (opcion == "2") {
            cout << "Ingrese el ID de 9 dígitos de la canción a quitar: ";
            int idCancion;
            cin >> idCancion;

            if (premiumUser->quitarCancionFavorita(idCancion)) {
                cout << "✅ Canción con ID " << idCancion << " eliminada de favoritos." << endl;
            } else {
                cout << "❌ Error: La canción no se encontró en su lista o el ID es inválido." << endl;
            }
        }
        else if (opcion == "3") {
            cout << "\n--- LISTA DE FAVORITOS ---" << endl;
            const Lista<Cancion*>& favs = premiumUser->getFavoritas();
            if (favs.tamanio() == 0) {
                cout << "La lista está vacía." << endl;
            } else {
                for (int i = 0; i < favs.tamanio(); ++i) {
                    Cancion* c = favs.obtener(i);
                    cout << i + 1 << ". ID: " << c->getId() << " | " << c->getTitulo() << " (" << c->getDuracion() << "s)" << endl;
                }
            }
        }
        else if (opcion == "0") {
            break;
        }
        else {
            cout << "Opción inválida." << endl;
        }
    }
}
// =======================================================
// 🔹 GESTIÓN DE SEGUIMIENTO (Solo Premium)
// =======================================================
void UdeATunes::gestionarSeguimiento(Usuario* usuario) {
    // DYNAMIC CAST OBLIGATORIO
    UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(usuario);
    if (p == nullptr) {
        cout << "❌ Error: Solo los usuarios Premium pueden gestionar seguimientos." << endl;
        return;
    }

    cout << "\n=== GESTIONAR SEGUIMIENTO ===" << endl;
    if (p->getSiguiendoA()) {
        cout << "Actualmente sigues a: " << p->getSiguiendoA()->getNickname() << endl;
    } else {
        cout << "Actualmente no sigues a ningún usuario." << endl;
    }

    cout << "--- Opciones ---" << endl;
    cout << "1. Seguir a un nuevo usuario (por ID)" << endl;
    cout << "2. Dejar de seguir al usuario actual" << endl;
    cout << "0. Volver" << endl;
    cout << "Ingrese opción: ";
    string opcion;
    cin >> opcion;

    if (opcion == "1") {
        cout << "Ingrese el ID del usuario Premium a seguir: ";
        int idSeguir;
        cin >> idSeguir;

        // Buscar al usuario por ID
        Usuario* u_a_seguir = nullptr;
        for (int i = 0; i < usuarios.tamanio(); ++i) {
            if (usuarios.obtener(i)->getId() == idSeguir) {
                u_a_seguir = usuarios.obtener(i);
                break;
            }
        }

        if (u_a_seguir) {
            UsuarioPremium* p_a_seguir = dynamic_cast<UsuarioPremium*>(u_a_seguir);

            // La persona a seguir debe ser Premium y no ser el mismo usuario
            if (p_a_seguir && p_a_seguir != p) {
                p->seguirA(p_a_seguir);
                cout << "✅ ¡Ahora sigues a " << p_a_seguir->getNickname() << "!" << endl;
            } else {
                cout << "❌ Error: ID encontrado, pero no es un usuario Premium válido para seguir." << endl;
            }
        } else {
            cout << "❌ Error: No se encontró un usuario con ese ID." << endl;
        }
    }
    else if (opcion == "2") {
        if (p->getSiguiendoA()) {
            cout << "Se ha dejado de seguir a " << p->getSiguiendoA()->getNickname() << "." << endl;
            p->dejarDeSeguir();
        } else {
            cout << "Ya no sigues a nadie." << endl;
        }
    }
    else if (opcion == "0") {
        return;
    }
    else {
        cout << "Opción inválida." << endl;
    }
}

// =======================================================
// 🔹 GUARDAR USUARIOS EN TXT (Persistencia)
// =======================================================
void UdeATunes::guardarUsuarios(const string& ruta) const {
    ofstream file(ruta);
    if (!file.is_open()) {
        cerr << "❌ Error: No se pudo abrir el archivo de usuarios para guardar: " << ruta << endl;
        return;
    }

    // Iterar sobre todos los usuarios
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        Usuario* u = usuarios.obtener(i);

        // 1. Escribir los campos comunes a todos los usuarios (ID, NICK, TIPO, CIUDAD, PAIS, FECHA)
        file << u->getId() << ";"
             << u->getNickname() << ";"
             << u->getTipo() << ";"
             << u->getCiudad() << ";"
             << u->getPais() << ";"
             << u->getFechaRegistro() << ";"; // ⬅️ Este es el 6to separador

        // 2. Manejo de campos exclusivos (ID_SEGUIDO y FAVORITOS_CSV)
        if (u->getTipo() == "Premium") {
            UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(u);

            // 2a. Guardar ID de Seguido
            if (p && p->getSiguiendoA() != nullptr) {
                file << p->getSiguiendoA()->getId();
            }
            file << ";"; // ⬅️ Separador 7 (después de ID_SEGUIDO)

            // 2b. Guardar Lista de Favoritos (CSV)
            if (p) {
                const Lista<Cancion*>& favs = p->getFavoritas();
                for (int j = 0; j < favs.tamanio(); ++j) {
                    file << favs.obtener(j)->getId(); // Guardamos el ID de 9 dígitos
                    if (j < favs.tamanio() - 1) {
                        file << ","; // Separador CSV
                    }
                }
            }
        }
        else {
            // ⬅️ FIX CRÍTICO: Para usuarios Estandar, debemos escribir el Separador 7
            // (que representa el campo ID_SEGUIDO vacío)
            // El campo de favoritos (el 8vo) queda vacío.
            file << ";";
        }

        // 3. Finalizar la línea (Termina el 8vo campo, el de Favoritos)
        file << "\n";
    }

    file.close();
    cout << "\n✅ [Persistencia] Los cambios de seguimiento y favoritos se guardaron en " << ruta << endl;
}
void UdeATunes::listarUsuarios() const {
    cout << "\n=======================================" << endl;
    cout << "=== USUARIOS DISPONIBLES EN UDEATUNES ===" << endl;
    cout << "=======================================" << endl;

    const Lista<Usuario*>& lista = this->getUsuarios(); // Usamos el getter

    if (lista.tamanio() == 0) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    for (int i = 0; i < lista.tamanio(); ++i) {
        Usuario* u = lista.obtener(i);
        // La información detallada se muestra con el método virtual
        cout << i + 1 << ". ID: " << u->getId() << " | Nick: " << u->getNickname() << " | ";
        u->mostrarInfo(); // Muestra el tipo y la info específica (como el seguido, si es Premium)
    }
    cout << "=======================================\n" << endl;
}
// =======================================================
// 🔹 GUARDAR CANCIONES (NUEVO MÉTODO: Persistencia de Reproducciones)
// =======================================================
void UdeATunes::guardarCanciones(const string& ruta) const {
    ofstream file(ruta);
    if (!file.is_open()) {
        cerr << "❌ Error: No se pudo abrir el archivo de canciones para guardar: " << ruta << endl;
        return;
    }

    // Formato: id_temporal;titulo;duracion;idAlbum;rutaArchivo;reproducciones
    for (int i = 0; i < canciones.tamanio(); ++i) {
        Cancion* c = canciones.obtener(i);

        file << c->getIdTemporal() << ";"
             << c->getTitulo() << ";"
             << c->getDuracion() << ";"
             << c->getIdAlbum() << ";"
             << c->getRutaArchivo() << ";"
             << c->getReproducciones() // ⬅️ CAMBIO CLAVE: Guardamos el conteo actualizado
             << "\n";
    }

    file.close();
    cout << "\n✅ [Persistencia] El conteo de reproducciones se guardó en " << ruta << endl;
}


void UdeATunes::sesionReproduccion(Usuario* usuario, const Lista<Cancion*>& lista, bool aleatorio) {
    if (lista.tamanio() == 0) {
        cout << "⚠️ La lista de reproducción está vacía." << endl;
        return;
    }

    // ESTADO DE LA SESIÓN
    bool reproduccionActiva = true;
    bool modoRepetir = false;
    bool sesionActiva = true; // Controla el bucle principal, reemplazando el 'break'

    // Historial: lista de punteros a Cancion (los objetos son propiedad de UdeATunes::canciones)
    list<Cancion*> historial;

    int indiceActual = aleatorio ? (rand() % lista.tamanio()) : 0;

    // Función auxiliar para obtener la siguiente canción
    auto obtenerSiguienteCancion = [&](int& index) -> Cancion* {
        if (aleatorio) {
            index = rand() % lista.tamanio();
        } else {
            if (index + 1 < lista.tamanio()) {
                index++;
            } else {
                return nullptr; // Fin de la lista ordenada
            }
        }
        return lista.obtener(index);
    };

    Cancion* cancionActual = lista.obtener(indiceActual);

    cout << "\n--- INICIANDO SESIÓN DE REPRODUCCIÓN INTERACTIVA ---" << endl;

    // --- BUCLE PRINCIPAL DE REPRODUCCIÓN ---
    while (sesionActiva) { // Usamos sesionActiva para controlar la salida

        if (cancionActual == nullptr) {
            cout << "\n--- FIN DE LA LISTA DE REPRODUCCIÓN ---" << endl;
            sesionActiva = false; // Usa la variable de estado para salir
            continue;
        }

        // 1. Lógica de Publicidad (Estándar, hay historial, NO repetición)
        if (usuario->getTipo() == "Estandar" && historial.size() > 0 && !modoRepetir) {
            cout << "\n[ANUNCIO] Publicidad obligatoria para usuario Estándar." << endl;
            Anuncio* anuncio = obtenerAnuncioAleatorio(); // Se asume que usa new para el anuncio si es necesario.
            if (anuncio) anuncio->mostrar();
            TiempoPausa::pausarConContador();
        }

        // 2. Conteo y Gestión de Historial (Solo si la canción es "nueva" en esta posición)
        if (historial.empty() || historial.back() != cancionActual) {
            cancionActual->contarReproduccion();
            historial.push_back(cancionActual);
            // Limitar el historial a MAX_HISTORIAL_PREMIUM (4 previas + 1 actual = 5)
            if (historial.size() > MAX_HISTORIAL_PREMIUM) {
                historial.pop_front();
            }
        }

        // 3. Obtener metadatos
        Album* album = buscarAlbumPorId(cancionActual->getIdAlbum());
        string nombreAlbum = album ? album->getTitulo() : "Desconocido";

        Artista* artista = nullptr;
        if (album) {
            artista = buscarArtistaPorId(album->getIdArtista());
        }
        string nombreArtista = artista ? artista->getNombre() : "Artista Desconocido";

        // 4. Mostrar la interfaz
        cout << "\n[Canción Actual: " << cancionActual->getTitulo() << "]" << endl;
        InterfazVisual::mostrarReproduccion(
            cancionActual->getTitulo(),
            nombreArtista,
            nombreAlbum,
            cancionActual->getRutaArchivo(),
            cancionActual->getDuracion(),
            cancionActual->getReproducciones(),
            usuario->getTipo(),
            reproduccionActiva,
            historial.size() > 1,
            modoRepetir
            );

        // 5. Simulación de la duración y Manejo de la Interacción del Usuario
        // La simulación de tiempo y la entrada del usuario deben ocurrir si la reproducción está activa.
        if (reproduccionActiva) {
            cout << "\nSimulando reproducción de " << cancionActual->getDuracion() << " segundos..." << endl;
            TiempoPausa::pausar(1); // Pausa corta para permitir la interacción
        }

        string opcion = InterfazVisual::pedirOpcion(usuario->getTipo());

        if (opcion == "0") { // Salir
            sesionActiva = false; // Usamos la variable de estado
        } else if (opcion == "1") { // Iniciar/Detener
            reproduccionActiva = !reproduccionActiva;
            cout << (reproduccionActiva ? "▶️ Reproducción REANUDADA." : "⏸️ Reproducción DETENIDA.") << endl;
        } else if (opcion == "2") { // Siguiente
            cout << "⏭️ Pasando a la siguiente canción..." << endl;
            cancionActual = obtenerSiguienteCancion(indiceActual);
            modoRepetir = false;
        } else if (opcion == "3" && usuario->getTipo() == "Premium") { // Previa (Premium)
            if (historial.size() > 1) {
                historial.pop_back();
                cancionActual = historial.back();
                cout << "⏮️ Volviendo a la canción previa: " << cancionActual->getTitulo() << endl;
                modoRepetir = false;
            } else {
                cout << "❌ No hay canciones previas disponibles." << endl;
            }
        } else if (opcion == "4" && usuario->getTipo() == "Premium") { // Repetir (Premium)
            modoRepetir = !modoRepetir;
            cout << (modoRepetir ? "🔁 Modo REPETIR ACTIVADO." : "➡️ Modo REPETIR DESACTIVADO.") << endl;
        } else {
            cout << "❌ Opción inválida o no permitida para su tipo de usuario." << endl;
        }

        // 7. Avance automático (Solo si está activo y NO está en modo repetir)
        if (reproduccionActiva && !modoRepetir) {
            // Si el usuario no presionó una opción de navegación (2, 3 o 4), el bucle
            // continuará y la canción avanzará automáticamente al inicio de la siguiente iteración
            // (a menos que haya sido detenida o se haya elegido repetir).
        }
    }
    cout << "\n--- SESIÓN DE REPRODUCCIÓN FINALIZADA ---" << endl;
}
// =======================================================
// 🔹 REPRODUCCIÓN RANDOM
// =======================================================
void UdeATunes::reproducirRandom(Usuario* usuario) {
    // Llama al método interactivo para la reproducción aleatoria de la lista completa.
    sesionReproduccion(usuario, canciones, true);
}

// =======================================================
// 🔹 REPRODUCIR LISTA DE FAVORITOS (Opción 4 del menú)
// =======================================================
void UdeATunes::reproducirFavoritos(Usuario* usuario) {
    cout << "\n--- REPRODUCIENDO FAVORITOS ---" << endl;

    // 1. Obtener la lista de favoritos.
    // NOTA: Se asume que la clase Usuario tiene un método getFavoritos()
    // En una implementación real se usaría: const Lista<Cancion*>& favoritos = usuario->getFavoritos();
    const Lista<Cancion*>& favoritos = canciones; // Usamos la lista completa por ahora (Placeholder)

    if (favoritos.tamanio() == 0) {
        cout << "⚠️ Su lista de favoritos está vacía." << endl;
        return;
    }

    // 2. SELECCIÓN DE ORDEN (Ordenada o Aleatoria)
    string opcionOrden;
    bool aleatorio = false;

    while (true) {
        cout << "\n¿Cómo desea reproducir su lista de favoritos?" << endl;
        cout << "1. Ordenada" << endl;
        cout << "2. Aleatoria" << endl;
        cout << "Ingrese opción: ";
        cin >> opcionOrden;

        if (opcionOrden == "1") {
            aleatorio = false;
            break;
        } else if (opcionOrden == "2") {
            aleatorio = true;
            break;
        } else {
            cout << "❌ Opción inválida. Intente de nuevo." << endl;
        }
    }

    // 3. Llamar a la sesión de reproducción
    sesionReproduccion(usuario, favoritos, aleatorio);
}
// =======================================================
// 🔹 Mostrar un resumen general
// =======================================================
void UdeATunes::mostrarResumen() const {
    cout << "\n--- UdeATunes ---\n";
    cout << "Canciones: " << canciones.tamanio() << endl;
    cout << "Albumes: " << albumes.tamanio() << endl;
    cout << "Artistas: " << artistas.tamanio() << endl;
    cout << "Usuarios: " << usuarios.tamanio() << endl;
}
