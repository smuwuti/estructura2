#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <unordered_set>
#include <string>

class StopWords {
private:
    std::unordered_set<std::string> stopwords;

public:
    StopWords();  // Constructor

    void cargarDesdeArchivo(const std::string& archivo);
    bool esStopWord(const std::string& palabra) const;
};

#endif
////