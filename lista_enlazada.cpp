#include "lista_enlazada.h"
#include <iostream>

ListaEnlazada::ListaEnlazada() : cabeza(nullptr) {}

ListaEnlazada::~ListaEnlazada() {
    NodoPalabra* actual = cabeza;
    while (actual) {
        NodoDoc* docActual = actual->listaDocs;
        while (docActual) {
            NodoDoc* tempDoc = docActual;
            docActual = docActual->siguiente;
            delete tempDoc;
        }
        NodoPalabra* tempPal = actual;
        actual = actual->siguiente;
        delete tempPal;
    }
}

NodoPalabra* ListaEnlazada::buscarPalabra(const std::string& palabra) {
    NodoPalabra* actual = cabeza;
    while (actual) {
        if (actual->palabra == palabra)
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

void ListaEnlazada::insertarPalabra(const std::string& palabra, int docID) {
    NodoPalabra* nodoPal = buscarPalabra(palabra);
    if (!nodoPal) {
        nodoPal = new NodoPalabra(palabra);
        nodoPal->siguiente = cabeza;
        cabeza = nodoPal;
    }

    // Insertar docID sin repetir
    NodoDoc* actualDoc = nodoPal->listaDocs;
    NodoDoc* prevDoc = nullptr;
    while (actualDoc) {
        if (actualDoc->docID == docID)
            return; // ya existe docID
        prevDoc = actualDoc;
        actualDoc = actualDoc->siguiente;
    }

    NodoDoc* nuevoDoc = new NodoDoc(docID);
    if (prevDoc == nullptr) {
        nodoPal->listaDocs = nuevoDoc;
    } else {
        prevDoc->siguiente = nuevoDoc;
    }
}

void ListaEnlazada::imprimirIndice() {
    NodoPalabra* actual = cabeza;
    while (actual) {
        std::cout << actual->palabra << " -> ";
        NodoDoc* docActual = actual->listaDocs;
        while (docActual) {
            std::cout << docActual->docID;
            if (docActual->siguiente) std::cout << ", ";
            docActual = docActual->siguiente;
        }
        std::cout << std::endl;
        actual = actual->siguiente;
    }
}
