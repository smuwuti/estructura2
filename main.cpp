#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

#include "indice.h"
#include "stopwords.h"
#include "Grafo.h"
#include "PageRank.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cout << "Uso: " << argv[0] << " <archivo_docs> <archivo_stopwords> <archivo_queries>" << std::endl;
        return 1;
    }

    std::string archivo_docs = argv[1];
    std::string archivo_stopwords = argv[2];
    std::string archivo_queries = argv[3];

    StopWords sw;
    sw.cargarDesdeArchivo(archivo_stopwords);

    IndiceInvertido indice(&sw);
    indice.procesarDocumentos(archivo_docs);

    std::cout << "\n--- Iniciando Fase Offline ---" << std::endl;
    
    auto start_grafo = std::chrono::high_resolution_clock::now();
    Grafo grafo;

    std::ifstream queries_file(archivo_queries);
    if (!queries_file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de queries: " << archivo_queries << std::endl;
        return 1;
    }

    std::string linea_consulta;
    size_t k = 10; // Usar size_t para consistencia con .size()
    int num_consultas = 0;

    while (std::getline(queries_file, linea_consulta)) {
        std::vector<int> resultados = indice.buscarYObtenerResultados(linea_consulta);
        if (resultados.size() > k) {
            resultados.resize(k);
        }
        grafo.agregarCoRelevancia(resultados);
        num_consultas++;
    }

    queries_file.close();

    auto end_grafo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_grafo = end_grafo - start_grafo;

    std::cout << "Grafo construido a partir de " << num_consultas << " consultas." << std::endl;
    std::cout << "Nodos en el grafo: " << grafo.getNumNodos() << std::endl;
    std::cout << "Aristas en el grafo: " << grafo.getNumAristas() << std::endl; // Muestra aristas
    std::cout << "Tiempo de construcción del grafo: " << t_grafo.count() << " segundos." << std::endl;
    grafo.imprimir();

    auto start_pr = std::chrono::high_resolution_clock::now();

    PageRank pr(grafo);
    int iteraciones_max_pr = 20; // Renombrado para claridad, se usa como iteraciones_max en PageRank::calcular
    pr.calcular(iteraciones_max_pr, 0.85); // PageRank::calcular ahora imprime la convergencia real
    indice.setPageRankScores(pr.getScores());

    auto end_pr = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t_pr = end_pr - start_pr;

    // Esta línea es menos crítica si PageRank::calcular ya imprime la convergencia
    std::cout << "Tiempo de cálculo de PageRank: " << t_pr.count() << " segundos." << std::endl;
    std::cout << "--- Fin Fase Offline ---\n" << std::endl;

    // Fase interactiva de búsqueda de usuario (sin caché para Proyecto 2)
    std::string consulta_usuario;
    while (true) {
        std::cout << "Ingrese término(s) a buscar (o 'salir' para terminar): ";
        std::getline(std::cin, consulta_usuario);
        if (consulta_usuario == "salir") break;
        indice.buscar(consulta_usuario);
    }

    return 0;
}