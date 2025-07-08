#!/bin/bash

# Compilar todos los archivos .cpp necesarios, INCLUYENDO Grafo.cpp y PageRank.cpp
g++ -std=c++17 -O2 main.cpp indice.cpp lista_enlazada.cpp stopwords.cpp Grafo.cpp PageRank.cpp -o buscador

if [ $? -eq 0 ]; then
    echo "Compilación exitosa."
else
    echo "Error en compilación."
    exit 1
fi

# Ejecutar (recibe TRES parámetros)
if [ $# -ne 3 ]; then
    echo "Uso: $0 <archivo_docs> <archivo_stopwords> <archivo_queries>"
    exit 1
fi

./buscador "$1" "$2" "$3"