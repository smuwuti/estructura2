#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <map>
#include <iostream>

class Grafo {
private:
    std::map<int, std::map<int, int>> adyacencia;

public:
    Grafo();
    void agregarCoRelevancia(const std::vector<int>& docs);
    const std::map<int, std::map<int, int>>& getAdyacencia() const;
    int getNumNodos() const;
    // Nuevo método para obtener el número de aristas
    int getNumAristas() const; // <-- Nuevo
    void imprimir() const;
};

#endif // GRAFO_H
