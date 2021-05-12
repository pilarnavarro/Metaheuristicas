# Definición de macros para definir las carpetas de trabajo
BIN=./bin
SRC=./src
IN=./data
#OUT=./salida

# Opciones de compilación
# -O3 para optimizacion
OPT= -O3

# Nombre de la práctica
PRJ=p2

all: $(BIN)/greedy $(BIN)/localSearch $(BIN)/AGGPos $(BIN)/AGGPos-bestcross $(BIN)/AGGPos-ternary $(BIN)/AGGUnif $(BIN)/AGGUnif-2 $(BIN)/AGEPos $(BIN)/AGEPos-ternary $(BIN)/AGEUnif $(BIN)/AM1 $(BIN)/AM2 $(BIN)/AM2-2 $(BIN)/AM3 $(BIN)/AM3-peores
	
execute_p1: $(BIN)/greedy $(BIN)/localSearch
	./execute_p1.sh 

execute_genetic: $(BIN)/AGGPos $(BIN)/AGGUnif $(BIN)/AGEPos $(BIN)/AGEUnif 
	./execute_genetic.sh 

execute_memetic: $(BIN)/AM1 $(BIN)/AM2 $(BIN)/AM3
	./execute_memetic.sh

execute_extras: $(BIN)/AGGPos-bestcross $(BIN)/AGGPos-ternary $(BIN)/AGGUnif-2 $(BIN)/AGEPos-ternary $(BIN)/AM2-2 $(BIN)/AM3-peores
	./execute_extras.sh

# Compilamos
$(BIN)/greedy :
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

$(BIN)/localSearch :
	g++ $(OPT) $(SRC)/localSearch.cpp -o $(BIN)/localSearch

$(BIN)/AGGPos :
	g++ $(OPT) $(SRC)/AGGPos.cpp -o $(BIN)/AGGPos

$(BIN)/AGGPos-ternary :
	g++ $(OPT) $(SRC)/AGGPos-ternary.cpp -o $(BIN)/AGGPos-ternary

$(BIN)/AGGPos-bestcross :
	g++ $(OPT) $(SRC)/AGGPos-bestcross.cpp -o $(BIN)/AGGPos-bestcross

$(BIN)/AGGUnif :
	g++ $(OPT) $(SRC)/AGGUnif.cpp -o $(BIN)/AGGUnif

$(BIN)/AGGUnif-2 :
	g++ $(OPT) $(SRC)/AGGUnif-2.cpp -o $(BIN)/AGGUnif-2

$(BIN)/AGEPos :
	g++ $(OPT) $(SRC)/AGEPos.cpp -o $(BIN)/AGEPos

$(BIN)/AGEPos-ternary :
	g++ $(OPT) $(SRC)/AGEPos-ternary.cpp -o $(BIN)/AGEPos-ternary

$(BIN)/AGEUnif :
	g++ $(OPT) $(SRC)/AGEUnif.cpp -o $(BIN)/AGEUnif

$(BIN)/AM1 :
	g++ $(OPT) $(SRC)/AM1.cpp -o $(BIN)/AM1

$(BIN)/AM2 :
	g++ $(OPT) $(SRC)/AM2.cpp -o $(BIN)/AM2

$(BIN)/AM2-2 :
	g++ $(OPT) $(SRC)/AM2-2.cpp -o $(BIN)/AM2-2

$(BIN)/AM3 :
	g++ $(OPT) $(SRC)/AM3.cpp -o $(BIN)/AM3

$(BIN)/AM3-peores :
	g++ $(OPT) $(SRC)/AM3-peores.cpp -o $(BIN)/AM3-peores

# Limpieza
clean:
	rm -f $(BIN)/*