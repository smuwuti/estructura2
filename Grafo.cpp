#include "Grafo.h"

Grafo::Grafo() {}

void Grafo::agregarCoRelevancia(const std::vector<int>& docs) {
    for (size_t i = 0; i < docs.size(); ++i) {
        for (size_t j = i + 1; j < docs.size(); ++j) {
            int docId1 = docs[i];
            int docId2 = docs[j];
            adyacencia[docId1][docId2]++;
            adyacencia[docId2][docId1]++;
        }
    }
}

const std::map<int, std::map<int, int>>& Grafo::getAdyacencia() const {
    return adyacencia;
}

int Grafo::getNumNodos() const {
    return adyacencia.size();
}

// Implementación del nuevo método para contar aristas
int Grafo::getNumAristas() const {
    int count = 0;
    // Itera sobre cada nodo en el mapa de adyacencia
    for (const auto& par_nodo : adyacencia) {
        // Suma el número de vecinos (aristas salientes) para cada nodo
        // Como el grafo es no dirigido y se almacena bidireccionalmente,
        // cada arista se cuenta dos veces, por eso se dividirá por 2 al final.
        count += par_nodo.second.size();
    }
    // Divide por 2 para obtener el número de aristas únicas
    return count / 2;
}

void Grafo::imprimir() const {
    std::cout << "--- Grafo de Co-relevancia ---" << std::endl;
    for (const auto& par_nodo : adyacencia) {
        std::cout << "Doc " << par_nodo.first << " -> ";
        for (const auto& par_vecino : par_nodo.second) {
            std::cout << "[Doc " << par_vecino.first << ", peso " << par_vecino.second << "] ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}
