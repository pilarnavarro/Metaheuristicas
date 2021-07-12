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

execute: $(BIN)/greedy $(BIN)/localSearch $(BIN)/ES $(BIN)/ES2 $(BIN)/ES3 $(BIN)/ES-Prop $(BIN)/BMB $(BIN)/ILS $(BIN)/ILS2 $(BIN)/ILS-ES $(BIN)/ILS-ES-Prop
	./execute.sh

# Compilamos
$(BIN)/greedy :
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

$(BIN)/localSearch :
	g++ $(OPT) $(SRC)/localSearch.cpp -o $(BIN)/localSearch

$(BIN)/ES :
	g++ $(OPT) $(SRC)/ES.cpp -o $(BIN)/ES

$(BIN)/ES2 :
	g++ $(OPT) $(SRC)/ES2.cpp -o $(BIN)/ES2

$(BIN)/ES3 :
	g++ $(OPT) $(SRC)/ES3.cpp -o $(BIN)/ES3

$(BIN)/ES-Prop :
	g++ $(OPT) $(SRC)/ES-prop.cpp -o $(BIN)/ES-Prop

$(BIN)/BMB:
	g++ $(OPT) $(SRC)/BMB.cpp -o $(BIN)/BMB

$(BIN)/ILS:
	g++ $(OPT) $(SRC)/ILS.cpp -o $(BIN)/ILS

$(BIN)/ILS2:
	g++ $(OPT) $(SRC)/ILS2.cpp -o $(BIN)/ILS2
	
$(BIN)/ILS-ES:
	g++ $(OPT) $(SRC)/ILS-ES.cpp -o $(BIN)/ILS-ES

$(BIN)/ILS-ES-Prop:
	g++ $(OPT) $(SRC)/ILS-ES-Prop.cpp -o $(BIN)/ILS-ES-Prop

# Limpieza
clean:
	rm -f $(BIN)/*
