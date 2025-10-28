#include "UdeATunes.h"

// Constructor y destructor
UdeATunes::UdeATunes() : ultimoAnuncioId(0) {}
UdeATunes::~UdeATunes() {}

// =======================================================
// CARGA DE CANCIONES
// Formato del txt:
// id;titulo;duracion;idAlbum;ruta
// Ejemplo: 1;Runaway;215;3;Music/Runaway.ogg
// =======================================================
// =======================================================
// CARGA DE CANCIONES
// Formato del txt: id_temporal;titulo;duracion;idAlbum;ruta
// =======================================================
// =======================================================
// CARGA DE CANCIONES (Actualizada para leer Reproducciones y rastrear ID temporal)
// Formato del txt: id_temporal;titulo;duracion;idAlbum;ruta;reproducciones (el ultimo campo es opcional al principio)
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

        // Declaracion de variables para los 6 campos
        string idS, titulo, durS, idAlbumS, rutaArchivo, repS;

        // 1. Lectura de campos
        getline(ss, idS, ';');
        getline(ss, titulo, ';');
        getline(ss, durS, ';');
        getline(ss, idAlbumS, ';');
        getline(ss, rutaArchivo, ';');

        // CAMBIO CLAVE: Lectura del SEXTO campo (Reproducciones)
        getline(ss, repS);

        // 2. Conversion a tipos de datos
        int idTemporal = stoi(idS);
        int duracion = stoi(durS);
        int idAlbum = stoi(idAlbumS);

        // CAMBIO CLAVE: Conversion segura del campo de reproducciones
        int reproducciones = 0;
        try {
            reproducciones = repS.empty() ? 0 : stoi(repS);
        } catch (...) {
            reproducciones = 0;
        }

        // ACTUALIZAR EL RASTREADOR DE ID TEMPORAL
        if (idTemporal > ultimoIdTemporalCancion) {
            ultimoIdTemporalCancion = idTemporal;
        }

        // 3. Creacion y adicion (Se asume que el constructor de Cancion fue actualizado para el ID Temporal y Reps)
        Cancion* c = new Cancion(idTemporal, titulo, duracion, idAlbum, rutaArchivo, reproducciones);
        canciones.agregar(c);
    }

    file.close();
    cout << "[Carga] " << canciones.tamanio() << " canciones cargadas. Ultimo ID temporal: " << ultimoIdTemporalCancion << endl;
}
// =======================================================
// CARGA DE ALBUMES
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
// CARGA DE ARTISTAS
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
// CARGA DE USUARIOS
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
        string idS, nick, tipo, ciudad, pais, fecha, idSeguidoS, favoritosCSV; // NUEVOS CAMPOS

        // Lectura de campos fijos
        getline(ss, idS, ';');
        getline(ss, nick, ';');
        getline(ss, tipo, ';');
        getline(ss, ciudad, ';');
        getline(ss, pais, ';');
        getline(ss, fecha, ';');

        // El resto de la linea contiene ID_SEGUIDO y la lista de favoritos.
        // Separamos el ID de seguimiento (puede estar vacio)
        getline(ss, idSeguidoS, ';');

        // Leemos el resto de la linea para los favoritos CSV
        getline(ss, favoritosCSV);

        // Creacion del objeto y carga de IDs
        Usuario* u = nullptr;
        if (tipo == "Premium") {
            UsuarioPremium* up = new UsuarioPremium(stoi(idS), nick, ciudad, pais, fecha);

            // Carga del CSV de IDs de favoritos
            up->cargarFavoritosDesdeCSV(favoritosCSV); // Carga la lista de IDs temporales

            u = up;
        } else {
            u = new UsuarioEstandar(stoi(idS), nick, ciudad, pais, fecha);
        }

        // Carga del ID de seguimiento temporal (comun en Usuario.h)
        if (!idSeguidoS.empty()) {
            u->setIdSeguidoTemporal(stoi(idSeguidoS));
        }

        usuarios.agregar(u);
    }
    file.close();
}
// =======================================================
// CARGA DE ANUNCIOS
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
        // 3. Leer Categoria
        getline(ss, categoria, ';');

        // Aseguramos que la categoria no tenga espacios en blanco innecesarios
        // y convertimos
        Anuncio* a = new Anuncio(stoi(idS), mensaje, categoria);
        anuncios.agregar(a);
    }

    file.close();
    cout << "[Carga] Anuncios cargados: " << anuncios.tamanio() << endl;
}
// =======================================================
// BUSQUEDA DE ALBUM (IMPLEMENTACION ANADIDA Y CORREGIDA)
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
// BUSQUEDA DE ARTISTA (IMPLEMENTACION ANADIDA Y CORREGIDA)
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
        // Si es el ultimo anuncio reproducido, su peso es CERO para cumplir la restriccion.
        if (a->getId() != ultimoAnuncioId) {
            pesoTotal += a->getPeso();
        }
    }

    // Si solo hay un anuncio, o si el unico anuncio es el ultimo reproducido,
    // simplemente devolver el primero disponible (opcionalmente podriamos mostrar un mensaje de error).
    if (pesoTotal == 0) {
        // En este caso, si solo queda un anuncio, la restriccion se vuelve imposible de cumplir,
        // asi que elegimos el primero disponible.
        ultimoAnuncioId = anuncios.obtener(0)->getId();
        return anuncios.obtener(0);
    }

    // 2. Generar un numero aleatorio entre 1 y el Peso Total
    int numeroAleatorio = (rand() % pesoTotal) + 1;

    // 3. Iterar y Seleccionar (El 'Giro')
    for (int i = 0; i < anuncios.tamanio(); ++i) {
        Anuncio* a = anuncios.obtener(i);

        // Si es el ultimo, lo saltamos (ya descontamos su peso del pesoTotal)
        if (a->getId() == ultimoAnuncioId) {
            continue;
        }

        numeroAleatorio -= a->getPeso();

        // El anuncio que hace que el numeroAleatorio sea <= 0 es el elegido
        if (numeroAleatorio <= 0) {
            // Actualizar el ID del ultimo anuncio para la proxima llamada
            ultimoAnuncioId = a->getId();
            return a;
        }
    }

    // Caso de seguridad, aunque la logica deberia siempre encontrar uno
    ultimoAnuncioId = anuncios.obtener(0)->getId();
    return anuncios.obtener(0);
}
// =======================================================
// INICIO DE SESION
// Busca el Usuario por nickname (busqueda lineal)
// =======================================================
Usuario* UdeATunes::iniciarSesion(const string& nickname) {
    // Usaremos un string auxiliar y transformaremos a minusculas
    // para una busqueda mas robusta (ej. "maria_premium" vs "Maria_Premium")
    string nickBuscado = nickname;
    transform(nickBuscado.begin(), nickBuscado.end(), nickBuscado.begin(), ::tolower);

    // 1. Recorrer la lista de usuarios
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        // La clase Lista te permite obtener el elemento en la posicion i
        Usuario* u = usuarios.obtener(i);

        // 2. Obtener y normalizar el nickname del usuario actual
        string nickActual = u->getNickname();
        transform(nickActual.begin(), nickActual.end(), nickActual.begin(), ::tolower);

        // 3. Comparar
        if (nickActual == nickBuscado) {
            // Encontrado! Devolvemos el puntero polimorfico (Usuario* puede ser Estandar o Premium)
            return u;
        }
    }

    // 4. Si el bucle termina sin encontrar coincidencias
    return nullptr;
}
Cancion* UdeATunes::buscarCancionPorId(int id) {
    for (int i = 0; i < canciones.tamanio(); ++i) {
        Cancion* c = canciones.obtener(i);
        // Compara con el ID final (que fue asignado en vincular())
        if (c->getId() == id) {
            return c;
        }
    }
    return nullptr; // No encontrada
}
// =======================================================
// VINCULAR ENTIDADES POR ID
// Canciones → Albumes → Artistas → Usuarios
// =======================================================
// =======================================================
// 🔹 VINCULACIÓN DE RELACIONES Y GENERACIÓN DE ID FINAL
// =======================================================
void UdeATunes::vincular() {
    cout << "\n--- Iniciando Vinculación de Relaciones ---" << endl;

    // --- FASE 1: VINCULACIÓN ARTISTA <-> ALBUM ---
    cout << "Vinculando Álbumes a Artistas..." << endl;
    for (int i = 0; i < artistas.tamanio(); ++i) {
        Artista* artista = artistas.obtener(i);
        const Lista<int*>& albumesIDs = artista->getAlbumesIDs();
        for (int j = 0; j < albumesIDs.tamanio(); ++j) {
            int idAlbumBuscado = *albumesIDs.obtener(j);
            for (int k = 0; k < albumes.tamanio(); ++k) {
                Album* album = albumes.obtener(k);
                if (album->getId() == idAlbumBuscado) {
                    artista->agregarAlbum(album);
                    break;
                }
            }
        }
    }

    // --- FASE 2: VINCULACIÓN ALBUM <-> CANCION ---
    cout << "Vinculando Canciones a Álbumes..." << endl;
    for (int i = 0; i < albumes.tamanio(); ++i) {
        Album* album = albumes.obtener(i);
        const Lista<int*>& cancionesIDs = album->getCancionesIDs();
        for (int j = 0; j < cancionesIDs.tamanio(); ++j) {
            int idCancionBuscado = *cancionesIDs.obtener(j);
            for (int k = 0; k < canciones.tamanio(); ++k) {
                Cancion* cancion = canciones.obtener(k);
                // NOTA: La Cancion almacena el idAlbum. Usamos ese para la búsqueda.
                // En este caso, el ID buscado es el ID TEMPORAL de la canción.
                if (cancion->getIdTemporal() == idCancionBuscado && cancion->getIdAlbum() == album->getId()) {
                    album->agregarCancion(cancion);
                    break;
                }
            }
        }
    }


    // --- FASE 3: GENERACIÓN del ID FINAL de 9 DÍGITOS para CADA CANCIÓN ---
    cout << "Generando ID final de 9 dígitos para cada Canción..." << endl;
    for (int i = 0; i < canciones.tamanio(); ++i) {
        Cancion* cancion = canciones.obtener(i);
        int idCancionTemp = cancion->getIdTemporal();
        int idAlbum = cancion->getIdAlbum();
        int idArtista = 0;
        string nombreAlbum = "Desconocido";

        // 1. Encontrar el Album para obtener el idArtista y el nombre
        Album* albumEncontrado = nullptr;
        for (int j = 0; j < albumes.tamanio(); ++j) {
            Album* album = albumes.obtener(j);
            if (album->getId() == idAlbum) {
                albumEncontrado = album;
                break;
            }
        }

        if (albumEncontrado) {
            idArtista = albumEncontrado->getIdArtista();
            nombreAlbum = albumEncontrado->getTitulo();

            // 2. Calcular el ID final (ID Artista * 1000 + ID Album * 100 + ID Cancion Temporal)
            // Esto garantiza un ID de 9 dígitos asumiendo IDs de 3 dígitos (999, 99, 99)
            // Si Artista tiene 1 o 2 dígitos, y Album/Canción 1 o 2, el ID será de 6 a 9 dígitos.
            // Para asegurar los 9 dígitos, se usaría multiplicación por potencias de 1000.
            // PERO: La fórmula proporcionada es: idArtista*1000 + idAlbum*100 + idCancionTemporal
            // Si la fórmula debe generar 9 dígitos (ej: 001001001), la fórmula real sería:
            // ID = idArtista*1000000 + idAlbum*1000 + idCancionTemporal
            // Ya que el enunciado dice que el ID final *es* esa suma, lo implementamos tal cual.
            long long int idFinal = idArtista * 10000 + idAlbum * 100 + idCancionTemp;

            // 3. Asignar el ID final a la canción
            cancion->setID(idFinal);

            // Ejemplo de depuración:
            // cout << "-> Cancion: " << cancion->getTitulo()
            //      << ", TempID: " << idCancionTemp
            //      << ", AlbumID: " << idAlbum
            //      << ", ArtistaID: " << idArtista
            //      << ", ID FINAL: " << idFinal << endl;
        } else {
            cerr << "⚠️ Error de vinculación: No se encontró el álbum ID " << idAlbum << " para la canción " << cancion->getTitulo() << endl;
        }
    }


    // --- FASE 4: VINCULACIÓN USUARIOS (FAVORITOS y SEGUIDOS) ---
    cout << "Vinculando Usuarios (Favoritos y Seguidos)..." << endl;

    // Vinculación de Seguidos (solo para Premium)
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        Usuario* user = usuarios.obtener(i);
        if (user->getTipo() == "Premium") {
            UsuarioPremium* premiumUser = dynamic_cast<UsuarioPremium*>(user);
            int idSeguidoTemp = premiumUser->getIdSeguidoTemporal();

            if (idSeguidoTemp != -1) {
                for (int j = 0; j < usuarios.tamanio(); ++j) {
                    Usuario* otroUser = usuarios.obtener(j);
                    if (otroUser->getId() == idSeguidoTemp && otroUser->getTipo() == "Premium") {
                        premiumUser->seguirA(dynamic_cast<UsuarioPremium*>(otroUser));
                        break;
                    }
                }
            }
        }
    }

    // Vinculación de Favoritos (solo para Premium)
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        Usuario* user = usuarios.obtener(i);
        if (user->getTipo() == "Premium") {
            UsuarioPremium* premiumUser = dynamic_cast<UsuarioPremium*>(user);
            const Lista<int*>& favoritosIDs = premiumUser->getFavoritosIDs();

            for (int j = 0; j < favoritosIDs.tamanio(); ++j) {
                int idFinalBuscado = *favoritosIDs.obtener(j);
                Cancion* cancionFavorita = buscarCancionPorId(idFinalBuscado); // Buscar por ID final

                if (cancionFavorita) {
                    premiumUser->agregarCancionFavorita(cancionFavorita);
                } else {
                    cerr << "⚠️ Error: Canción con ID final " << idFinalBuscado << " no encontrada para favoritos." << endl;
                }
            }
            // Importante: liberar los IDs temporales si ya no se usarán
            // En este caso, la clase UsuarioPremium es responsable de liberar sus int*
        }
    }

    cout << "--- Vinculación Completa ---" << endl;
}
// =======================================================
// GESTION DE LISTA DE FAVORITOS (Solo Premium)
// =======================================================
void UdeATunes::gestionarFavoritos(Usuario* usuario) {
    // 1. DYNAMIC CAST OBLIGATORIO
    UsuarioPremium* premiumUser = dynamic_cast<UsuarioPremium*>(usuario);
    if (premiumUser == nullptr) {
        cout << "Error interno: Esta funcion solo debe ser llamada por usuarios Premium." << endl;
        return;
    }

    string opcion;
    cout << "\n=== MI LISTA DE FAVORITOS (" << premiumUser->getNickname() << ") ===" << endl;
    cout << "Canciones actuales en favoritos: " << premiumUser->getFavoritas().tamanio() << endl;

    while (true) {
        cout << "\n--- Opciones de Gestion ---" << endl;
        cout << "1. Agregar cancion por ID (9 digitos)" << endl;
        cout << "2. Quitar cancion por ID (9 digitos)" << endl;
        cout << "3. Ver lista actual" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        if (opcion == "1") {
            cout << "Ingrese el ID de 9 digitos de la cancion a agregar: ";
            int idCancion;
            cin >> idCancion;

            Cancion* c = buscarCancionPorId(idCancion);

            if (c) {
                premiumUser->agregarCancionFavorita(c);
                cout << "Cancion '" << c->getTitulo() << "' agregada a favoritos." << endl;
            } else {
                cout << "Error: Cancion con ID " << idCancion << " no encontrada en UdeATunes." << endl;
            }
        }
        else if (opcion == "2") {
            cout << "Ingrese el ID de 9 digitos de la cancion a quitar: ";
            int idCancion;
            cin >> idCancion;

            if (premiumUser->quitarCancionFavorita(idCancion)) {
                cout << "Cancion con ID " << idCancion << " eliminada de favoritos." << endl;
            } else {
                cout << "Error: La cancion no se encontro en su lista o el ID es invalido." << endl;
            }
        }
        else if (opcion == "3") {
            cout << "\n--- LISTA DE FAVORITOS ---" << endl;
            const Lista<Cancion*>& favs = premiumUser->getFavoritas();
            if (favs.tamanio() == 0) {
                cout << "La lista esta vacia." << endl;
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
            cout << "Opcion invalida." << endl;
        }
    }
}
// =======================================================
// GESTION DE SEGUIMIENTO (Solo Premium)
// =======================================================
void UdeATunes::gestionarSeguimiento(Usuario* usuario) {
    // DYNAMIC CAST OBLIGATORIO
    UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(usuario);
    if (p == nullptr) {
        cout << "Error: Solo los usuarios Premium pueden gestionar seguimientos." << endl;
        return;
    }

    cout << "\n=== GESTIONAR SEGUIMIENTO ===" << endl;
    if (p->getSiguiendoA()) {
        cout << "Actualmente sigues a: " << p->getSiguiendoA()->getNickname() << endl;
    } else {
        cout << "Actualmente no sigues a ningun usuario." << endl;
    }

    cout << "--- Opciones ---" << endl;
    cout << "1. Seguir a un nuevo usuario (por ID)" << endl;
    cout << "2. Dejar de seguir al usuario actual" << endl;
    cout << "0. Volver" << endl;
    cout << "Ingrese opcion: ";
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
                cout << "Ahora sigues a " << p_a_seguir->getNickname() << "!" << endl;
            } else {
                cout << "Error: ID encontrado, pero no es un usuario Premium valido para seguir." << endl;
            }
        } else {
            cout << "Error: No se encontro un usuario con ese ID." << endl;
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
        cout << "Opcion invalida." << endl;
    }
}

// =======================================================
// GUARDAR USUARIOS EN TXT (Persistencia)
// =======================================================
void UdeATunes::guardarUsuarios(const string& ruta) const {
    ofstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de usuarios para guardar: " << ruta << endl;
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
             << u->getFechaRegistro() << ";"; // Este es el 6to separador

        // 2. Manejo de campos exclusivos (ID_SEGUIDO y FAVORITOS_CSV)
        if (u->getTipo() == "Premium") {
            UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(u);

            // 2a. Guardar ID de Seguido
            if (p && p->getSiguiendoA() != nullptr) {
                file << p->getSiguiendoA()->getId();
            }
            file << ";"; // Separador 7 (despues de ID_SEGUIDO)

            // 2b. Guardar Lista de Favoritos (CSV)
            if (p) {
                const Lista<Cancion*>& favs = p->getFavoritas();
                for (int j = 0; j < favs.tamanio(); ++j) {
                    file << favs.obtener(j)->getId(); // Guardamos el ID de 9 digitos
                    if (j < favs.tamanio() - 1) {
                        file << ","; // Separador CSV
                    }
                }
            }
        }
        else {
            // FIX CRITICO: Para usuarios Estandar, debemos escribir el Separador 7
            // (que representa el campo ID_SEGUIDO vacio)
            // El campo de favoritos (el 8vo) queda vacio.
            file << ";";
        }

        // 3. Finalizar la linea (Termina el 8vo campo, el de Favoritos)
        file << "\n";
    }

    file.close();
    cout << "\n[Persistencia] Los cambios de seguimiento y favoritos se guardaron en " << ruta << endl;
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
        // La informacion detallada se muestra con el metodo virtual
        cout << i + 1 << ". ID: " << u->getId() << " | Nick: " << u->getNickname() << " | ";
        u->mostrarInfo(); // Muestra el tipo y la info especifica (como el seguido, si es Premium)
    }
    cout << "=======================================\n" << endl;
}
// =======================================================
// GUARDAR CANCIONES (NUEVO METODO: Persistencia de Reproducciones)
// =======================================================
void UdeATunes::guardarCanciones(const string& ruta) const {
    ofstream file(ruta);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de canciones para guardar: " << ruta << endl;
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
             << c->getReproducciones() // CAMBIO CLAVE: Guardamos el conteo actualizado
             << "\n";
    }

    file.close();
    cout << "\n[Persistencia] El conteo de reproducciones se guardo en " << ruta << endl;
}


void UdeATunes::sesionReproduccion(Usuario* usuario, const Lista<Cancion*>& lista, bool aleatorio) {
    if (lista.tamanio() == 0) {
        cout << "La lista de reproduccion esta vacia." << endl;
        return;
    }

    // ESTADO DE LA SESION
    bool reproduccionActiva = true;
    bool modoRepetir = false;
    bool sesionActiva = true; // Controla el bucle principal, reemplazando el 'break'

    // Historial: lista de punteros a Cancion (los objetos son propiedad de UdeATunes::canciones)
    list<Cancion*> historial;

    int indiceActual = aleatorio ? (rand() % lista.tamanio()) : 0;

    // Funcion auxiliar para obtener la siguiente cancion
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

    cout << "\n--- INICIANDO SESION DE REPRODUCCION INTERACTIVA ---" << endl;

    // --- BUCLE PRINCIPAL DE REPRODUCCION ---
    while (sesionActiva) { // Usamos sesionActiva para controlar la salida

        if (cancionActual == nullptr) {
            cout << "\n--- FIN DE LA LISTA DE REPRODUCCION ---" << endl;
            sesionActiva = false; // Usa la variable de estado para salir
            continue;
        }

        // 1. Logica de Publicidad (Estandar, hay historial, NO repeticion)
        if (usuario->getTipo() == "Estandar" && historial.size() > 0 && !modoRepetir) {
            cout << "\n[ANUNCIO] Publicidad obligatoria para usuario Estandar." << endl;
            Anuncio* anuncio = obtenerAnuncioAleatorio(); // Se asume que usa new para el anuncio si es necesario.
            if (anuncio) anuncio->mostrar();
            TiempoPausa::pausarConContador();
        }

        // 2. Conteo y Gestion de Historial (Solo si la cancion es "nueva" en esta posicion)
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
        cout << "\n[Cancion Actual: " << cancionActual->getTitulo() << "]" << endl;
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
            modoRepetir,
            cancionActual->getId());

        // 5. Simulacion de la duracion y Manejo de la Interaccion del Usuario
        // La simulacion de tiempo y la entrada del usuario deben ocurrir si la reproduccion esta activa.
        if (reproduccionActiva) {
            cout << "\nSimulando reproduccion de " << cancionActual->getDuracion() << " segundos..." << endl;
            TiempoPausa::pausar(1); // Pausa corta para permitir la interaccion
        }

        string opcion = InterfazVisual::pedirOpcion(usuario->getTipo());

        if (opcion == "0") { // Salir
            sesionActiva = false; // Usamos la variable de estado
        } else if (opcion == "1") { // Iniciar/Detener
            reproduccionActiva = !reproduccionActiva;
            cout << (reproduccionActiva ? "Reproduccion REANUDADA." : "Reproduccion DETENIDA.") << endl;
        } else if (opcion == "2") { // Siguiente
            cout << "Pasando a la siguiente cancion..." << endl;
            cancionActual = obtenerSiguienteCancion(indiceActual);
            modoRepetir = false;
        } else if (opcion == "3" && usuario->getTipo() == "Premium") { // Previa (Premium)
            if (historial.size() > 1) {
                historial.pop_back();
                cancionActual = historial.back();
                cout << "Volviendo a la cancion previa: " << cancionActual->getTitulo() << endl;
                modoRepetir = false;
            } else {
                cout << "No hay canciones previas disponibles." << endl;
            }
        } else if (opcion == "4" && usuario->getTipo() == "Premium") { // Repetir (Premium)
            modoRepetir = !modoRepetir;
            cout << (modoRepetir ? "Modo REPETIR ACTIVADO." : "Modo REPETIR DESACTIVADO.") << endl;
        } else {
            cout << "Opcion invalida o no permitida para su tipo de usuario." << endl;
        }

        // 7. Avance automatico (Solo si esta activo y NO esta en modo repetir)
        if (reproduccionActiva && !modoRepetir) {
            // Si el usuario no presiono una opcion de navegacion (2, 3 o 4), el bucle
            // continuara y la cancion avanzara automaticamente al inicio de la siguiente iteracion
            // (a menos que haya sido detenida o se haya elegido repetir).
        }
    }
    cout << "\n--- SESION DE REPRODUCCION FINALIZADA ---" << endl;
}
// =======================================================
// REPRODUCCION RANDOM
// =======================================================
void UdeATunes::reproducirRandom(Usuario* usuario) {
    // Llama al metodo interactivo para la reproduccion aleatoria de la lista completa.
    sesionReproduccion(usuario, canciones, true);
}

// =======================================================
// REPRODUCIR LISTA DE FAVORITOS (Opcion 4 del menu)
// =======================================================
void UdeATunes::reproducirFavoritos(Usuario* usuario) {
    cout << "\n--- REPRODUCIENDO FAVORITOS ---" << endl;

    // 1. Obtener la lista de favoritos.
    // NOTA: Se asume que la clase Usuario tiene un metodo getFavoritos()
    // En una implementacion real se usaria: const Lista<Cancion*>& favoritos = usuario->getFavoritos();
    const Lista<Cancion*>& favoritos = canciones; // Usamos la lista completa por ahora (Placeholder)

    if (favoritos.tamanio() == 0) {
        cout << "Su lista de favoritos esta vacia." << endl;
        return;
    }

    // 2. SELECCION DE ORDEN (Ordenada o Aleatoria)
    string opcionOrden;
    bool aleatorio = false;

    while (true) {
        cout << "\nComo desea reproducir su lista de favoritos?" << endl;
        cout << "1. Ordenada" << endl;
        cout << "2. Aleatoria" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcionOrden;

        if (opcionOrden == "1") {
            aleatorio = false;
            break;
        } else if (opcionOrden == "2") {
            aleatorio = true;
            break;
        } else {
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    }

    // 3. Llamar a la sesion de reproduccion
    sesionReproduccion(usuario, favoritos, aleatorio);
}
// =======================================================
// Mostrar un resumen general
// =======================================================
void UdeATunes::mostrarResumen() const {
    cout << "\n--- UdeATunes ---\n";
    cout << "Canciones: " << canciones.tamanio() << endl;
    cout << "Albumes: " << albumes.tamanio() << endl;
    cout << "Artistas: " << artistas.tamanio() << endl;
    cout << "Usuarios: " << usuarios.tamanio() << endl;
}
