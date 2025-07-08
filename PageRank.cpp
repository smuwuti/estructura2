#include "PageRank.h"
#include <vector>
#include <numeric>
#include <cmath> // Para std::abs, necesario para la comprobación de convergencia

PageRank::PageRank(const Grafo& g) : grafo(g) {}

void PageRank::calcular(int iteraciones_max, double damping_factor) { // Cambiado a iteraciones_max
    const auto& adyacencia = grafo.getAdyacencia();
    int num_nodos = grafo.getNumNodos();
    if (num_nodos == 0) return;

    std::vector<int> nodos;
    for (const auto& par : adyacencia) {
        nodos.push_back(par.first);
        scores[par.first] = 1.0 / num_nodos;
    }

    double epsilon = 1e-6; // Umbral de convergencia: el algoritmo se detiene si la diferencia es menor que este valor
    int iteraciones_actuales = 0; // Contador de iteraciones reales ejecutadas
    double diff = 0.0; // Declarar 'diff' fuera del bucle para que sea accesible después

    for (int i = 0; i < iteraciones_max; ++i) { // Iterar hasta un número máximo de veces
        iteraciones_actuales++; // Incrementar el contador de iteraciones
        std::map<int, double> nuevos_scores; // Mapa para almacenar los scores de la iteración actual
        double suma_total_pr = 0.0; // Para la renormalización de los scores

        // Calcular el nuevo PageRank para cada nodo 'p'
        for (int p : nodos) {
            double suma_pagerank_entrante = 0.0;
            
            // Asegurarse de que el nodo 'p' existe en la adyacencia
            if (adyacencia.count(p)) {
                // Iterar sobre los vecinos de 'p' (que son también nodos que apuntan a 'p' en este grafo no dirigido)
                for (const auto& vecino_par_de_p : adyacencia.at(p)) {
                    int j = vecino_par_de_p.first; // 'j' es un nodo vecino de 'p'
                    
                    // Asegurarse de que el nodo 'j' existe en la adyacencia
                    if (adyacencia.count(j)) {
                        double Lj = 0.0; // Suma de pesos de las "aristas salientes" de 'j'
                        // Calcular Lj (la suma de los pesos de las aristas que conectan a 'j' con otros nodos)
                        for (const auto& arista_saliente_de_j : adyacencia.at(j)) {
                            Lj += arista_saliente_de_j.second;
                        }

                        if (Lj > 0) {
                            // Contribución de PageRank de 'j' a 'p'
                            // adyacencia.at(j).at(p) es el peso de la arista entre j y p
                            suma_pagerank_entrante += (adyacencia.at(j).at(p) / Lj) * scores[j];
                        }
                    }
                }
            }
            
            // Fórmula de PageRank: (1-d)/N + d * (suma de contribuciones entrantes)
            nuevos_scores[p] = (1.0 - damping_factor) / num_nodos + damping_factor * suma_pagerank_entrante;
            suma_total_pr += nuevos_scores[p]; // Acumular para la renormalización
        }

        // Renormalización de los scores: asegurar que la suma de todos los scores sea 1
        if(suma_total_pr > 0){
            for (int p : nodos) {
                nuevos_scores[p] /= suma_total_pr;
            }
        }
        
        // Comprobar convergencia: calcular la suma de las diferencias absolutas
        // entre los scores actuales y los nuevos
        
        diff = 0.0; // Reinicia diff en cada iteración
        for (int p : nodos) {
            diff += std::abs(nuevos_scores[p] - scores[p]); 
        }

        scores = nuevos_scores; // Actualiza los scores con los nuevos valores calculados
        
        // Si la diferencia es menor que epsilon, el algoritmo ha convergido
        if (diff < epsilon) {
            std::cout << "PageRank convergió en " << iteraciones_actuales << " iteraciones." << std::endl;
            break; 
        }
    }
    // Si el bucle termina por alcanzar iteraciones_max y no convergió completamente
    if (iteraciones_actuales == iteraciones_max && diff >= epsilon) {
        std::cout << "PageRank no convergió completamente en " << iteraciones_actuales << " iteraciones (diff: " << diff << ")." << std::endl;
    }
}

const std::map<int, double>& PageRank::getScores() const {
    return scores;
}
