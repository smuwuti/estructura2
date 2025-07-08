#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <string>

struct NodoDoc {
    int docID;
    NodoDoc* siguiente;
    NodoDoc(int id) : docID(id), siguiente(nullptr) {}
};

struct NodoPalabra {
    std::string palabra;
    NodoDoc* listaDocs;
    NodoPalabra* siguiente;

    NodoPalabra(const std::string& p) : palabra(p), listaDocs(nullptr), siguiente(nullptr) {}
};

class ListaEnlazada {
private:
    NodoPalabra* cabeza;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    NodoPalabra* buscarPalabra(const std::string& palabra);
    void insertarPalabra(const std::string& palabra, int docID);

    void imprimirIndice();
};

#endif
