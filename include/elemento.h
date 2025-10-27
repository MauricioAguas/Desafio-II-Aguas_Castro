#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <string>
#include <sstream>
using namespace std;

class Elemento {
protected:
    int id;

public:
    // Constructor y destructor
    Elemento(int id) : id(id) {}
    virtual ~Elemento() {}

    // Obtener ID
    int getId() const { return id; }

    // Representación textual
    virtual string toString() const = 0;  // método abstracto puro
};

#endif
