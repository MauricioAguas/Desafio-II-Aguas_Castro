#include <iostream>
#include <string>
#include "UdeATunes.h"


            using namespace std;

            int main() {
                cout << "=== INICIANDO UDEATUNES ===" << endl;

                UdeATunes app;
                app.cargarCanciones("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio2_Aguas_Castro/data/canciones.txt");
                app.cargarAlbumes("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio2_Aguas_Castro/data/albumes.txt");
                app.cargarArtistas("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio2_Aguas_Castro/data/artistas.txt");
                app.cargarUsuarios("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio2_Aguas_Castro/data/usuarios.txt");

                app.vincular();

                cout << "\n=== DATOS CARGADOS CORRECTAMENTE ===" << endl;
                app.mostrarResumen();

                cout << "\nPuedes consultar usuarios o artistas del sistema." << endl;
                cout << "Escribe 'u' para buscar un usuario, 'a' para listar artistas, o 'salir' para terminar." << endl;

                string opcion;
                while (true) {
                    cout << "\n> ";
                    getline(cin, opcion);

                    if (opcion == "u" || opcion == "U") {
                        string nick;
                        cout << "\nIngrese el nickname del usuario: ";
                        getline(cin, nick);

                        bool encontrado = false;
                        for (int i = 0; i < app.getUsuarios().tamanio(); ++i) {
                            Usuario* u = app.getUsuarios().obtener(i);
                            if (u->getNickname() == nick) {
                                encontrado = true;
                                cout << "\n--- INFORMACION DE USUARIO ---" << endl;
                                cout << "Nickname: " << u->getNickname() << endl;
                                cout << "Tipo: " << u->getTipo() << endl;
                                cout << "Ciudad: " << u->getCiudad() << " (" << u->getPais() << ")" << endl;
                                cout << "Fecha de registro: " << u->getFechaRegistro() << endl;

                                UsuarioPremium* p = dynamic_cast<UsuarioPremium*>(u);
                                if (p) {
                                    if (p->getSiguiendoA())
                                        cout << "Siguiendo a: " << p->getSiguiendoA()->getNickname() << endl;
                                    else
                                        cout << "No sigue a ningun usuario." << endl;

                                    if (p->getFavoritas().tamanio() == 0)
                                        cout << "No tiene canciones favoritas aun." << endl;
                                    else {
                                        cout << "\nCanciones favoritas:" << endl;
                                        for (int j = 0; j < p->getFavoritas().tamanio(); ++j) {
                                            Cancion* c = p->getFavoritas().obtener(j);
                                            cout << "  ♪ " << c->getTitulo() << endl;
                                        }
                                    }
                                } else {
                                    cout << "Este usuario es estandar y no posee lista de favoritos." << endl;
                                }
                                break;
                            }
                        }

                        if (!encontrado)
                            cout << "Usuario no encontrado." << endl;
                    }

                    else if (opcion == "a" || opcion == "A") {
                        cout << "\n--- ARTISTAS Y SU MUSICA ---" << endl;
                        for (int i = 0; i < app.getArtistas().tamanio(); ++i) {
                            Artista* art = app.getArtistas().obtener(i);
                            cout << "\n " << art->getNombre()
                                 << " (" << art->getGenero() << ", " << art->getPais() << ")" << endl;

                            if (art->getAlbumes().tamanio() == 0) {
                                cout << "  (Sin albumes asociados)" << endl;
                                continue;
                            }

                            for (int j = 0; j < art->getAlbumes().tamanio(); ++j) {
                                Album* alb = art->getAlbumes().obtener(j);
                                cout << "  " << alb->getTitulo() << " (" << alb->getAnio() << ")" << endl;

                                if (alb->getCanciones().tamanio() == 0) {
                                    cout << " (Sin canciones registradas)" << endl;
                                    continue;
                                }

                                for (int k = 0; k < alb->getCanciones().tamanio(); ++k) {
                                    Cancion* c = alb->getCanciones().obtener(k);
                                    cout << " " << c->getTitulo()
                                         << " (" << c->getDuracion() << "s)" << endl;
                                }
                            }
                        }
                    }

                    else if (opcion == "salir" || opcion == "SALIR") {
                        cout << "\nCerrando sesión de UdeATunes... ¡Hasta pronto! 🎧" << endl;
                        break;
                    }

                    else {
                        cout << "Comando no reconocido. Usa 'u', 'a' o 'salir'." << endl;
                    }
                }

                return 0;
            }
