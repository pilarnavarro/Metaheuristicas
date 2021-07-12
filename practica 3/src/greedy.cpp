#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include <limits>       // std::numeric_limits<double>::infinity()
#include <iomanip>      // std::setprecision

using namespace std;

//------------------- INPUT ----------------------
/*  Función para leer los ficheros de datos.
    Almacena las distancias en la matriz que se le pasa como parámetro */
void readInput (vector<vector<double> > &matriz){
    unsigned i, j;
    double dist, index1, index2;
    for (i=0; i<matriz.size(); i++){
        for (j=i+1; j<matriz.size(); j++){
            cin >> index1 >> index2 >> dist;
            matriz[i][j] = matriz[j][i] = dist;
        }
    }
}

//------------------- OUTPUT ---------------------

//Imprime la matriz que se le pasa como parámetro
void printMatriz(const vector<vector<double> > &matriz){
    cout << "Matriz de distancias:" << endl;
    for(unsigned i=0; i<matriz.size(); i++){
        for(unsigned j=0; j<matriz.size(); j++){
            cout << matriz[i][j] << " ";
        }
    cout << endl;
    }
}

//Imprime el conjunto de datos que se le pasa como parámetro
void printSet(set<int> &conjunto){
    cout << "Conjunto de elementos:" << endl;
    set<int>::iterator it;
    for( it = conjunto.begin(); it!= conjunto.end() ; ++it){
        cout << *it << " ";
    }
    cout << endl;
}

//-------------- FUNCIONES AUXILIARES ------------------

/* Calcula el fitness de la solución dada en 'conjunto', es decir, 
    suma las distancias entre todos los elementos del conjunto */
double fitness(const set<int> &conjunto, const vector<vector<double> > &matriz){
    double sum = 0;
    set<int>::iterator it1,it2;

    for(it1 = conjunto.begin(); it1!= conjunto.end(); ++it1){
        for( it2 = it1 ; it2!= conjunto.end(); ++it2){ 
            sum += matriz[*it1][*it2];
        }
    }
    return sum;
}

/* Calcula la contribución del elemento 'element', es decir,
    suma las distancias de ese elemento a todos los demás 
    del conjunto pasado como parámetro */
double contribution(const set<int> &conjunto, const vector<vector<double> > &matriz, const int &element){
    double sum=0;
    set<int>::const_iterator it;

    for( it = conjunto.begin(); it!= conjunto.end() ; ++it){
        sum+=matriz[element][*it];
    }
    return sum;
}

//---------------------------ALGORITMO GREEDY----------------------

/* Determina el elemento más prometedor, es decir, aquel cuya suma de 
    las distancias a todos los elementos es mayor */
int furthestElement(const vector<vector<double> > &matriz){
    set<int> aux;
    double max = -1, cont;
    int furthest = -1;

    for (unsigned i=0; i<matriz.size(); i++) {
        aux.insert(i);
    }

    for(unsigned i = 0; i < matriz.size(); i++){
        cont=contribution(aux,matriz,i);
        if(cont > max){
            max = cont;
            furthest = i;
        }
    }
    return furthest;
}

// Determina la distancia del elemento 'element' al conjunto que se pasa como parámetro
double distanceToSet(const set<int> &conjunto, const vector<vector<double> > &matriz, const int &element){
    set<int>::iterator it;
    double dist, min = std::numeric_limits<double>::infinity();
    
    for(it=conjunto.begin(); it!=conjunto.end(); ++it){
        dist= matriz[element][*it];
        if(dist < min) min= dist;
    }
    return min;
}

// Devuelve el elemento del conjunto NoSel que está más alejado del cojunto Sel
int furthestToSel(const set<int> &Sel, const set<int> & NoSel, const vector<vector<double> > &matriz){
    set<int>::iterator it;
    double max= -1, dist;
    int furthest=-1;

    for(it=NoSel.begin(); it!=NoSel.end(); ++it){
        dist = distanceToSet(Sel, matriz,*it);
        if(dist > max){
            max = dist;
            furthest = *it;
        }
    }  
    return furthest;
}

/*  Implementa el algorimto Greedy para el problema MDP.
    Determina el conjunto de num_sel elementos que proporciona el valor de fitness más alto.
    Imprime por pantalla el fitness de la solución encontrada así como el tiempo de
    ejecución en segundos.
*/
void greedy(const vector<vector<double> > &matriz, const unsigned int &num_sel){
    set<int> Sel, NoSel;
    int furthest;   
    double valor;   
    clock_t start, total;

    start=clock();

    for(unsigned i = 0 ; i < matriz.size(); i++)
        NoSel.insert(i);
    
    furthest= furthestElement(matriz);
    Sel.insert(furthest);
    NoSel.erase(furthest);

    while(num_sel > Sel.size()){
        furthest = furthestToSel(Sel,NoSel,matriz);
        Sel.insert(furthest);
        NoSel.erase(furthest);
    }

    total=clock()-start;

    valor = fitness(Sel,matriz);
    // Imprime el resultado en el formato: Fitness, Tiempo
    cout << setprecision(2) << fixed << valor  << ", " << setprecision(6)<< (double) total/CLOCKS_PER_SEC << endl;
    //printSet(Sel);
    //printSet(NoSel);
}

//-----------------MAIN-------------------

int main(int argc, char *argv[]){
    //Leemos el fichero de datos e inicializamos la matriz de distancias
    int num_elements, num_sel;
    cin >> num_elements >> num_sel;
    vector<double> aux(num_elements, 0);
    vector<vector<double> > matriz(num_elements, aux);
    readInput(matriz);   
    //printMatriz(matriz);

    //Ejecutamos el algoritmo greedy
    greedy(matriz,num_sel);

}
