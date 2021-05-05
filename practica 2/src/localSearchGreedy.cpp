#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <algorithm>    // shuffle and find
#include <time.h>
#include <stdlib.h>     // rand and srand
#include <iomanip>      // setprecision
#include <limits>       // numeric_limits<double>::infinity()
#include <assert.h>

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

//Imprime el vector de elementos que se le pasa como parámetro
void printSet(vector<int> &conjunto){
    cout << "Conjunto de elementos:" << endl;
    vector<int>::const_iterator it;
    for( it = conjunto.begin(); it!= conjunto.end() ; ++it){
        cout << *it << " ";
    }
    cout << endl;
}

//-------------------------ESTRUCTURA DE LA SOLUCION-------------------------

struct solucion{
    vector<int> elements;
    double fitness;

    //Operador de asignación
    void operator = (const solucion &sol) { 
            elements = sol.elements;
            fitness = sol.fitness;
    } 
};

//-------------- FUNCIONES AUXILIARES --------------------

/* Calcula el fitness de la solución dada en 'sol', es decir, 
    suma las distancias entre todos los elementos de la solución */
double fitness(const vector<int> &sol, const vector<vector<double> > &matriz){
    double sum = 0;
    vector<int>::const_iterator it1,it2;

    for(it1=sol.begin(); it1!= sol.end(); ++it1){
        for(it2 = it1 ; it2!= sol.end(); ++it2){ 
            sum += matriz[*it1][*it2];
        }
    }
    return sum;
}

/* Calcula la contribución del elemento 'element', es decir,
    suma las distancias de ese elemento a todos los demás 
    del conjunto pasado como parámetro */
double contribution(const vector<int> &conjunto, const vector<vector<double> > &matriz, const int &element){
    double sum=0;
    vector<int>::const_iterator it;

    for( it = conjunto.begin(); it!= conjunto.end() ; ++it){
        sum+=matriz[element][*it];
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


// Genera una solución aleatoria válida, que se almacena en el parámetro 'sol'
void randomSolution(solucion &sol, const unsigned int &num_sel, const vector<vector<double> > &matriz){
  unsigned int total_elements = matriz.size();
  int random = 0;
  vector<int> aux;

  assert(num_sel <= total_elements);

  while (aux.size() < num_sel ){
    random = rand()%total_elements;                                                           
    if(find(aux.begin(),aux.end(), random) == aux.end()){     //Para evitar elementos repetidos
      aux.push_back(random);
    }
  }
  if(!sol.elements.empty()) sol.elements.clear();
  sol.elements=aux;
  sol.fitness = fitness(sol.elements, matriz);
}



/* Determina los elementos que no están aún seleccionados (no se encuentran en el vector 'sel') 
    y los almacena en el vector 'elements' pasado como parámetro */
void validElements(vector<int> &elements, const vector<int> &sel, const unsigned int &total_elements){
  unsigned int size = total_elements - sel.size();  
  unsigned int elem = 0;
  
  if(!elements.empty())  elements.clear();

  while(elements.size() < size){
    if(find(sel.begin(), sel.end(), elem) == sel.end()){
      elements.push_back(elem);
    }
    elem++;
  }
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
    Determina el conjunto de num_sel elementos que proporciona el valor de fitness más alto
    y almacena la solución en 'sol'
*/
void greedy(solucion &sol,const vector<vector<double> > &matriz, const unsigned int &num_sel){
    set<int> Sel, NoSel;
    set<int>::const_iterator it;
    int furthest;

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

    for(it=Sel.begin();it!=Sel.end();++it){
        sol.elements.push_back(*it);
    }

    sol.fitness = fitness(sol.elements,matriz);
}

//------------------------------------------------BÚSQUEDA LOCAL---------------------------------

/* Determina si la solución 'sol' mejora al cambiar el elemento en la posición 'pos' de la solución por 
  el elemento 'elem'. En caso afirmativo la función devuelve True y la solución 'sol' se actualiza, cambiando 
  el elemento en la posición 'pos' por 'elem'. En otro caso se devuelve False y la solución permanece inaletrada */
bool improvement(solucion &sol, const unsigned int &pos, const double &old_cont, const unsigned int &elem, const vector<vector<double> > &matriz){
  solucion nueva; 
  bool mejora = false;
  double new_cont;
  unsigned int old_elem;

  nueva=sol;
  old_elem=sol.elements[pos];
  
  if(old_elem!=elem){
    nueva.elements[pos] = elem;
    new_cont = contribution(nueva.elements, matriz, elem);
    if(new_cont > old_cont) {
      nueva.fitness = sol.fitness - old_cont + new_cont; 
      sol = nueva;
      mejora = true;
    }
  }
  return mejora;
}

/* Devuelve la posición en la solución 'sol', pasada como parámetro, del elemento
    que menos contribuye al fitness de la solución, así como su contribución */
pair<int,double> lowestContribution(const vector<int> &sol, const vector<vector<double> > &matriz){
    pair<int,double> min_contrib;
    min_contrib.first=-1; //Posición que menos contribuye
    min_contrib.second=std::numeric_limits<double>::infinity();  //Contribución más pequeña
    double cont;

    for(unsigned i=0;i<sol.size();i++){
        cont=contribution(sol,matriz,sol[i]);
        if (cont<min_contrib.second){
            min_contrib.first=i;
            min_contrib.second=cont;
        }
    }
    return min_contrib;
}

/*  Implementa el algorimto de la búsqueda local del primer mejor para el problema MDP.
    Determina el conjunto de num_sel elementos que proporciona el valor de fitness más alto.
    Imprime por pantalla el fitness de la solución encontrada así como el tiempo de
    ejecución en segundos.
*/
void localSearchGreedy(const vector<vector<double> > &matriz, const unsigned int &num_sel, const int &seed){
    clock_t start, total;
    solucion sol;
    bool mejora;
    unsigned int old_elem, new_elem;
    unsigned int num_eval = 0;
    vector<int> valid_elements; 
    pair<int,double> min_contrib;

    start=clock();

    greedy(sol,matriz,num_sel);  //Empezamos con la solución proporcionada por el algoritmo greedy
    
    validElements(valid_elements,sol.elements,matriz.size());   //Seleccionamos los elementos por los que podemos intercambiar 

    // Determinamos el elemento que menos contribuye y su contribución
    min_contrib=lowestContribution(sol.elements,matriz);

    mejora=true;
    while(mejora and num_eval < 100000){  //Iteramos mientras la solución mejore y no se haya superado el número máximo de evaluaciones
        mejora = false;
        old_elem=sol.elements[min_contrib.first];  //Guardamos el elemento antiguo que vamos a intercambiar

        //Mezclamos los posibles elementos por los que podemos intercambiar un elemento de la solución
        shuffle(valid_elements.begin(),valid_elements.end(),default_random_engine(seed));

        unsigned k;
        //Intercambiamos el elemento que menos contribuye por todos los posibles hasta que se poroduzca una mejora
        for(k = 0 ; k < valid_elements.size() and mejora == false ; k++){
            new_elem=valid_elements[k];  
            mejora = improvement(sol,min_contrib.first,min_contrib.second,new_elem,matriz);                                                                                        
            num_eval++;
        }

        if (mejora){   //Si ha habido mejora, se ha cambiado la solución
            valid_elements[k-1]=old_elem;  //Actualizamos los elementos válidos, cambiando el elemento nuevo por el antiguo
            //Volvemos a determinar el elemento que menos contribuye en la nueva solución
            min_contrib=lowestContribution(sol.elements,matriz);
        }
    }

    total=clock()-start;
    // Imprime el resultado en el formato: Fitness, Tiempo
    cout << setprecision(2) << fixed << sol.fitness  << ", " << setprecision(6)<< (double) total/CLOCKS_PER_SEC << endl;
}


//-----------------------------MAIN---------------------------


int main(int argc, char *argv[]){
    //Leemos el fichero de datos e inicializamos la matriz de distancias
    int num_elements, num_sel;
    const int seed=atoi(argv[1]);
    cin >> num_elements >> num_sel;
    vector<double> aux(num_elements, 0);
    vector<vector<double> > matriz(num_elements, aux);
    readInput(matriz);   
    //printMatriz(matriz);

    //Ejecutamos el algoritmo de búsqueda local
    localSearchGreedy(matriz,num_sel,seed);
}