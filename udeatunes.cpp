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
        string idS, titulo, durS, idAlbumS, rutaArchivo;

        getline(ss, idS, ';');
        getline(ss, titulo, ';');
        getline(ss, durS, ';');
        getline(ss, idAlbumS, ';');
        getline(ss, rutaArchivo, ';');

        Cancion* c = new Cancion(stoi(idS), titulo, stoi(durS), stoi(idAlbumS), rutaArchivo);
        canciones.agregar(c);
    }

    file.close();
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
        string idS, nick, tipo, ciudad, pais, fecha, seguidoS;

        getline(ss, idS, ';');
        getline(ss, nick, ';');
        getline(ss, tipo, ';');
        getline(ss, ciudad, ';');
        getline(ss, pais, ';');
        getline(ss, fecha, ';');
        getline(ss, seguidoS, ';');

        Usuario* u = nullptr;

        if (tipo == "Premium")
            u = new UsuarioPremium(stoi(idS), nick, ciudad, pais, fecha);
        else
            u = new UsuarioEstandar(stoi(idS), nick, ciudad, pais, fecha);

        // Guardamos ID seguido temporalmente en "extra"
        if (!seguidoS.empty() && tipo == "Premium") {
            // aprovechamos el campo tipo para guardar temporalmente el ID seguido
            if (!seguidoS.empty())
                u->setIdSeguidoTemporal(stoi(seguidoS));
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
// =======================================================
// 🔹 VINCULAR ENTIDADES POR ID
// Canciones → Álbumes → Artistas → Usuarios
// =======================================================
void UdeATunes::vincular() {
    // 1️⃣ Canciones → Álbumes
    for (int i = 0; i < albumes.tamanio(); ++i) {
        Album* a = albumes.obtener(i);
        for (int j = 0; j < a->getCancionesIDs().tamanio(); ++j) {
            int idC = *(a->getCancionesIDs().obtener(j)); // usar * porque es Lista<int*>
            int posC = canciones.buscarPorId(idC);
            if (posC != -1)
                a->agregarCancion(canciones.obtener(posC));
        }
    }

    // 2️⃣ Álbumes → Artistas
    for (int i = 0; i < artistas.tamanio(); ++i) {
        Artista* art = artistas.obtener(i);
        for (int j = 0; j < art->getAlbumesIDs().tamanio(); ++j) {
            int idA = *(art->getAlbumesIDs().obtener(j)); // también Lista<int*>
            int posA = albumes.buscarPorId(idA);
            if (posA != -1)
                art->agregarAlbum(albumes.obtener(posA));
        }
    }

    // 3️⃣ Usuarios Premium seguidos
    for (int i = 0; i < usuarios.tamanio(); ++i) {
        Usuario* u = usuarios.obtener(i);
        UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(u);
        if (!p) continue;

        int idSeguido = u->getIdSeguidoTemporal();
        if (idSeguido == -1) continue;

        for (int j = 0; j < usuarios.tamanio(); ++j) {
            UsuarioPremium* seguido = dynamic_cast<UsuarioPremium*>(usuarios.obtener(j));
            if (seguido && seguido->getId() == idSeguido) {
                p->seguirA(seguido);
                break;
            }
        }
    }
}
// =======================================================
// 🔹 REPRODUCCIÓN ALEATORIA GLOBAL (Simulación)
// K=5 canciones. Publicidad cada 2 para Estandar.
// =======================================================
void UdeATunes::reproducirRandom(Usuario* usuario) {
    if (canciones.tamanio() == 0) {
        cout << "No hay canciones cargadas para reproducir." << endl;
        return;
    }

    // 1. Inicializar la medición de recursos
    int iteracionesIniciales = Lista<Cancion*>::getIteraciones();

    cout << "\n=== INICIANDO REPRODUCCIÓN ALEATORIA GLOBAL (K=5) ===" << endl;
    cout << "Usuario: " << usuario->getNickname() << " (" << usuario->getTipo() << ")" << endl;

    string calidadAudio = (usuario->getTipo() == "Premium") ? "320 kbps (Alta Calidad)" : "128 kbps (Calidad Estándar)";

    // 2. Bucle de reproducción de K=5 canciones
    for (int i = 1; i <= 5; ++i) {
        // --- 2.1. Lógica de Publicidad (Solo para Estandar) ---
        // Se ejecuta cada 2 canciones (i=2 y i=4)
        if (usuario->getTipo() == "Estandar" && i > 1 && (i - 1) % 2 == 0) {
            cout << "\n--- PAUSA COMERCIAL ---" << endl;
            Anuncio* ad = obtenerAnuncioAleatorio(); // Usa la función ponderada implementada
            if (ad) {
                ad->mostrar();
            }
            cout << "-----------------------" << endl;
        }

        // --- 2.2. Selección Aleatoria de Canción ---
        int max_canciones = canciones.tamanio();
        // Fórmula: rand() % N para obtener un número entre 0 y N-1
        int indice_aleatorio = rand() % max_canciones;
        Cancion* cancionActual = canciones.obtener(indice_aleatorio);

        // El método obtener() incrementa las iteraciones de Lista

        // --- 2.3. Simulación de Reproducción ---
        cout << "\n[" << i << "/5] Reproduciendo... " << cancionActual->getTitulo() << endl;
        cout << "  - Ruta del archivo: " << cancionActual->getRutaArchivo() << ".ogg" << endl;
        cout << "  - Calidad de Audio: " << calidadAudio << endl;
        cout << "  (Simulando 3 segundos de reproducción...)\n";

        // Simulación de pausa (simulando la librería chronos que no podemos usar aquí)
        // Por lo general, se usaría: this_thread::sleep_for(chrono::seconds(3));
    }

    // 3. Medición del consumo de recursos
    int iteracionesTotales = Lista<Cancion*>::getIteraciones();
    cout << "\n=== MEDICIÓN DE RECURSOS (Reproducción Aleatoria) ===" << endl;
    cout << "Cantidad de iteraciones requeridas: " << (iteracionesTotales - iteracionesIniciales) << endl;
    // La medición de la memoria consumida requiere librerías específicas (como malloc_trim, etc.)
    // que no están permitidas o no son estándar, por lo que nos enfocaremos en las iteraciones.
    cout << "Total de memoria consumida: (Requiere herramientas de sistema, solo mostrando iteraciones)" << endl;
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
