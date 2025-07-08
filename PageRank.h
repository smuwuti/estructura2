#ifndef PAGERANK_H
#define PAGERANK_H

#include "Grafo.h"
#include <map>
#include <vector>

class PageRank {
private:
    const Grafo& grafo;
    std::map<int, double> scores;

public:
    PageRank(const Grafo& g);
    void calcular(int iteraciones, double damping_factor);
    const std::map<int, double>& getScores() const;
};

#endif // PAGERANK_H