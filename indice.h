#ifndef INDICE_H
#define INDICE_H

#include "lista_enlazada.h"
#include "stopwords.h"
#include <string>
#include <vector>
#include <map>

class IndiceInvertido {
private:
    ListaEnlazada listaPalabras;
    StopWords* stopwords;
    std::map<int, double> pageRankScores;

    void procesarLinea(const std::string& linea, int docID);

public:
    IndiceInvertido(StopWords* sw);
    void procesarDocumentos(const std::string& archivo_docs);
    void buscar(const std::string& consulta);
    std::vector<int> buscarYObtenerResultados(const std::string& consulta);
    void setPageRankScores(const std::map<int, double>& scores);
};

#endif