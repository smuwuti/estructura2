#include "stopwords.h"
#include <fstream>
#include <algorithm>  // std::transform

StopWords::StopWords() {
    // Constructor vacío, no carga stop words por defecto
}

void StopWords::cargarDesdeArchivo(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        // No lanza error, simplemente no carga ninguna stop word
        return;
    }

    std::string palabra;
    while (std::getline(file, palabra)) {
        // Convertir palabra a minúsculas para evitar inconsistencias
        std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        if (!palabra.empty()) {
            stopwords.insert(palabra);
        }
    }
    file.close();
}

bool StopWords::esStopWord(const std::string& palabra) const {
    return stopwords.find(palabra) != stopwords.end();
}
