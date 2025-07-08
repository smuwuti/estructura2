#include "indice.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

IndiceInvertido::IndiceInvertido(StopWords* sw) : stopwords(sw) {}

void IndiceInvertido::procesarLinea(const std::string& linea, int docID) {
    size_t pos = linea.find("||");
    if (pos == std::string::npos) return;

    std::string contenido = linea.substr(pos + 2);
    std::istringstream iss(contenido);
    std::string palabra;

    while (iss >> palabra) {
        for (auto& c : palabra) c = tolower(c);
        if (!stopwords->esStopWord(palabra)) {
            listaPalabras.insertarPalabra(palabra, docID);
        }
    }
}

void IndiceInvertido::procesarDocumentos(const std::string& archivo_docs) {
    std::ifstream file(archivo_docs);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de documentos: " << archivo_docs << std::endl;
        return;
    }

    std::string linea;
    int docID = 1;
    while (std::getline(file, linea)) {
        procesarLinea(linea, docID);
        if (docID % 10000 == 0) {
            std::cout << "Procesados " << docID << " documentos..." << std::endl;
        }
        docID++;
    }
    file.close();
    std::cout << "Índice construido con " << (docID - 1) << " documentos." << std::endl;
}

std::vector<int> IndiceInvertido::buscarYObtenerResultados(const std::string& consulta) {
    std::istringstream iss(consulta);
    std::string palabra;
    std::vector<NodoDoc*> listasDocs;

    while (iss >> palabra) {
        for (auto& c : palabra) c = tolower(c);
        if (stopwords->esStopWord(palabra)) continue;

        NodoPalabra* nodo = listaPalabras.buscarPalabra(palabra);
        if (nodo) {
            listasDocs.push_back(nodo->listaDocs);
        } else {
            return {};
        }
    }

    if (listasDocs.empty()) return {};

    std::vector<int> resultado;
    for (NodoDoc* nd = listasDocs[0]; nd != nullptr; nd = nd->siguiente) {
        resultado.push_back(nd->docID);
    }

    for (size_t i = 1; i < listasDocs.size(); ++i) {
        std::vector<int> temp;
        std::vector<int> lista_actual_ids;
        for (NodoDoc* nd = listasDocs[i]; nd != nullptr; nd = nd->siguiente) {
            lista_actual_ids.push_back(nd->docID);
        }

        for (int id : resultado) {
            if (std::find(lista_actual_ids.begin(), lista_actual_ids.end(), id) != lista_actual_ids.end()) {
                temp.push_back(id);
            }
        }
        resultado = temp;
        if (resultado.empty()) break;
    }
    return resultado;
}

void IndiceInvertido::buscar(const std::string& consulta) {
    std::vector<int> resultado = buscarYObtenerResultados(consulta);

    if (resultado.empty()) {
        std::cout << "No hay documentos que contengan todas las palabras." << std::endl;
        return;
    }
    
    std::sort(resultado.begin(), resultado.end(), [&](int a, int b) {
        double scoreA = pageRankScores.count(a) ? pageRankScores.at(a) : 0.0;
        double scoreB = pageRankScores.count(b) ? pageRankScores.at(b) : 0.0;
        return scoreA > scoreB;
    });

    std::cout << "Los documentos que contienen todas las palabras son (ordenados por PageRank): " << std::endl;
    for (size_t i = 0; i < resultado.size(); ++i) {
        double score = pageRankScores.count(resultado[i]) ? pageRankScores.at(resultado[i]) : 0.0;
        std::cout << "  - Doc " << resultado[i] << " (Score: " << score << ")";
        std::cout << std::endl;
    }
}

void IndiceInvertido::setPageRankScores(const std::map<int, double>& scores) {
    this->pageRankScores = scores;
}