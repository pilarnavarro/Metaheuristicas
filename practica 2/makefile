# Definición de macros para definir las carpetas de trabajo
BIN=./bin
SRC=./src
ZIP=./zip
IN=./data
#OUT=./salida

# Opciones de compilación
# -Wall muestra todas las advertencias
# -O2 para optimizacion
OPT=-Wall -O2 -g

# Nombre de la práctica
PRJ=p1

execute: $(BIN)/greedy $(BIN)/localSearch $(BIN)/localSearchMejor $(BIN)/localSearchGreedy $(BIN)/AGGPos $(BIN)/AGGUnif $(BIN)/AGEPos $(BIN)/AGEUnif 
	./execute_genetic.sh

# Compilamos
$(BIN)/greedy :
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

$(BIN)/localSearch :
	g++ $(OPT) $(SRC)/localSearch.cpp -o $(BIN)/localSearch

$(BIN)/localSearchMejor :
	g++ $(OPT) $(SRC)/localSearchMejor.cpp -o $(BIN)/localSearchMejor

$(BIN)/localSearchGreedy :
	g++ $(OPT) $(SRC)/localSearchGreedy.cpp -o $(BIN)/localSearchGreedy

$(BIN)/AGGPos :
	g++ $(OPT) $(SRC)/AGGPos.cpp -o $(BIN)/AGGPos

$(BIN)/AGGUnif :
	g++ $(OPT) $(SRC)/AGGUnif.cpp -o $(BIN)/AGGUnif

$(BIN)/AGEPos :
	g++ $(OPT) $(SRC)/AGEPos.cpp -o $(BIN)/AGEPos

$(BIN)/AGEUnif :
	g++ $(OPT) $(SRC)/AGEUnif.cpp -o $(BIN)/AGEUnif

# Limpieza
clean:
	rm -f $(BIN)/*
