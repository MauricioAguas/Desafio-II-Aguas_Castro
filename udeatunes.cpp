#include "UdeATunes.h"

// 🔹 Constructor y destructor
UdeATunes::UdeATunes() {}
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
// 🔹 Mostrar un resumen general
// =======================================================
void UdeATunes::mostrarResumen() const {
    cout << "\n--- UdeATunes ---\n";
    cout << "Canciones: " << canciones.tamanio() << endl;
    cout << "Albumes: " << albumes.tamanio() << endl;
    cout << "Artistas: " << artistas.tamanio() << endl;
    cout << "Usuarios: " << usuarios.tamanio() << endl;
}
