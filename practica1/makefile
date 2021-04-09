# Definición de macros para definir las carpetas de trabajo
BIN=./bin
SRC=./src
ZIP=./zip
IN=./data
#OUT=./salida

# Opciones de compilación
# -Wall muestra todas las advertencias
# -O2 para optimizacion
OPT=-Wall -O2

# Nombre de la práctica
PRJ=p1

execute: $(BIN)/greedy $(BIN)/localSearch $(BIN)/localSearchMejor $(BIN)/localSearchGreedy
	./execute.sh

# Compilamos
$(BIN)/greedy :
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

$(BIN)/localSearch :
	g++ $(OPT) $(SRC)/localSearch.cpp -o $(BIN)/localSearch

$(BIN)/localSearchMejor :
	g++ $(OPT) $(SRC)/localSearchMejor.cpp -o $(BIN)/localSearchMejor

$(BIN)/localSearchGreedy :
	g++ $(OPT) $(SRC)/localSearchGreedy.cpp -o $(BIN)/localSearchGreedy
	
# Limpieza
clean:
	rm -f $(BIN)/*
