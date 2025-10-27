
#pragma once
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

class TiempoPausa {
public:

    static void pausar3Segundos() {
        cout << "Pausando publicidad 3 segundos..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        cout << "Continuando reproduccion..." << endl;
    }


    static void pausarConContador() {
        cout << "Publicidad obligatoria: ";
        for (int i = 3; i > 0; i--) {
            cout << i << "..." << flush;
            this_thread::sleep_for(chrono::seconds(1));
        }
        cout << " Listo!" << endl;
    }

    static void pausar(int segundos) {
        this_thread::sleep_for(chrono::seconds(segundos));
    }
};
