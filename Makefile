# Define el compilador de C++
CXX = g++
# Define las banderas de compilación (estándar C++17, advertencias, etc.)
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Define la lista de archivos objeto (.o) que se crearán y se enlazarán
# ESTA ES LA LÍNEA CRÍTICA QUE DEBE INCLUIR Grafo.o y PageRank.o
OBJ = main.o indice.o lista_enlazada.o stopwords.o Grafo.o PageRank.o
# Define el nombre del ejecutable final
EXEC = buscador

# Regla 'all': Es la regla por defecto, construye el ejecutable
all: $(EXEC)

# Regla para construir el ejecutable a partir de los archivos objeto
# Enlaza todos los archivos .o en el ejecutable final
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas para compilar cada archivo .cpp en su correspondiente archivo .o
# Cada regla especifica las dependencias (.h) para que se recompilen si cambian las cabeceras
main.o: main.cpp indice.h stopwords.h Grafo.h PageRank.h
	$(CXX) $(CXXFLAGS) -c main.cpp

indice.o: indice.cpp indice.h lista_enlazada.h stopwords.h
	$(CXX) $(CXXFLAGS) -c indice.cpp

lista_enlazada.o: lista_enlazada.cpp lista_enlazada.h
	$(CXX) $(CXXFLAGS) -c lista_enlazada.cpp

stopwords.o: stopwords.cpp stopwords.h
	$(CXX) $(CXXFLAGS) -c stopwords.cpp

# NUEVAS REGLAS: Para compilar Grafo.cpp a Grafo.o
Grafo.o: Grafo.cpp Grafo.h
	$(CXX) $(CXXFLAGS) -c Grafo.cpp

# NUEVAS REGLAS: Para compilar PageRank.cpp a PageRank.o
PageRank.o: PageRank.cpp PageRank.h Grafo.h
	$(CXX) $(CXXFLAGS) -c PageRank.cpp

# Regla 'clean': Elimina los archivos objeto y el ejecutable
clean:
	rm -f $(OBJ) $(EXEC)
