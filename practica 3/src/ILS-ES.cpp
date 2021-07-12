#include <iostream>
#include <vector>
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

//Genera un número aleatorio en (0,1)
double randI(){
    double random=rand()/(double)RAND_MAX;
    return (double)random;
}

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


//------------------------------------------------ENFRIAMIENTO SIMULADO---------------------------------

/*Intercambia un elemento en una posición aleatoria de las solución pasada como parámetro, sol, 
por otro elemento aleatorio que no pertenece a la misma y actualiza su fitness*/
void changeSolution(solucion &sol,  const unsigned int &total_elements, const vector<vector<double> > &matriz){
    int pos;
    double new_cont, old_cont;
    unsigned int old_elem,new_elem;
    vector<int> valid;

    pos=rand()%sol.elements.size();
    old_elem=sol.elements[pos];
    old_cont=contribution(sol.elements, matriz, old_elem);
    validElements(valid,sol.elements,total_elements);
    new_elem=valid[rand()%valid.size()];
    
    if(old_elem!=new_elem){
        sol.elements[pos] = new_elem;
        new_cont = contribution(sol.elements, matriz, new_elem);
        sol.fitness = sol.fitness - old_cont + new_cont;  //Factorización de la función objetivo
    }
}


/* Implementa el algorimto de enfriamiento simulado para el problema MDP.
    Determina el conjunto de num_sel elementos que proporciona el valor de fitness más alto, 
    partiendo de la solución proporcionada como parámetro. Esta se actualiza con la mejor 
    solución encontrada*/
void ES(solucion &sol, const vector<vector<double> > &matriz, const unsigned int &num_sel, const unsigned int &num_elements){
    solucion best_sol,aux;
    unsigned int num_eval = 0;
    
    double mu=0.3,phi=0.3;
    unsigned int max_vecinos = 10*num_elements;
    unsigned int max_exitos = 0.1*max_vecinos;
    unsigned int M = 10000/max_vecinos;
    double Tf=0.0001;
    double T, delta_f;
    unsigned int neighbors, exitos=1;

    double T0=-mu*sol.fitness/log(phi);
    double beta=(T0-Tf)/(M*T0*Tf);
    T=T0;
    best_sol=sol;

    while(Tf>T0) Tf/=10;

    while(exitos>0 && num_eval<10000){
        neighbors=0, exitos=0;
        while(neighbors<max_vecinos && exitos<max_exitos && num_eval<10000){
            aux=sol;
            changeSolution(aux,num_elements,matriz);
            neighbors++;
            num_eval++;
            delta_f=aux.fitness-sol.fitness;
            if((delta_f)>0 || randI()<=exp(delta_f/T)){
                sol=aux;
                exitos++;
                if(sol.fitness>best_sol.fitness) best_sol=sol;
            }
        }
        T=T/(1+beta*T);
        //cout<<T<<endl;
    }
}


//---------------------------------Iterative Local Search-------------------------------

/*Intercambia num_mut elementos aleatorios de la solución pasada como parámetro, sol,
por elementos no seleccionados, también aleatorios, y actualiza el fitness de la nueva solución*/
void mutate(const unsigned int num_mut, solucion &sol,const vector<vector<double> > &matriz){
    int pos;
    vector<int> to_change;  //Posiciones de la solución cuyos elementos se van a cambiar
    vector<int> valid;
    vector<int> elems; //Nuevos elementos a introducir en la solución

    do{
        pos=rand()%sol.elements.size(); //Elegimos una posición aleatoria de la solución
        if(find(to_change.begin(), to_change.end(),pos) == to_change.end()){  //Si la posición no está ya seleccionada
            to_change.push_back(pos);                               //la añadimos al vector de posiciones a cambiar
        }
    }while(to_change.size()<num_mut);


    validElements(valid,sol.elements,matriz.size()); //Determinamos los elementos no seleccionados

    do{
        pos=rand()%valid.size(); //Elegimos una posición aleatoria del vector de elementos no seleccionados
        if(find(elems.begin(), elems.end(),valid[pos]) == elems.end()){  //Si el elemento no ha sido escogido ya
            elems.push_back(valid[pos]);                        //lo añadimos al vector de nuevos elementos
        }
    }while(elems.size()<num_mut);


    //Cambiamos los elementos de la solución
    for(unsigned i = 0 ; i < num_mut ; i++){
        sol.elements[to_change[i]] = elems[i];
    }
    //Actualizamos el fitnesss
    sol.fitness = fitness(sol.elements,matriz);
}


/* Implementa el algoritmo de ILS con enfriamiento simulado para el problema MDP.
Imprime por pantalla el fitness de la mejor solución encontrada así como el tiempo de
ejecución en segundos.*/
void ILS_ES(const vector<vector<double> > &matriz, const unsigned int &num_sel,  const unsigned int &num_elements, const int &seed){
    clock_t start, total;
    solucion sol, best_sol;
    unsigned int num_mut=0.1*num_sel;  //Número de elementos a mutar en cada solución   
    srand(seed);    //Fijamos la semilla

    start=clock();   

    randomSolution(best_sol,num_sel,matriz); //Partimos de una solución aleatoria
    ES(best_sol,matriz,num_sel,num_elements);

    for(unsigned i=0;i<9;i++){
        sol=best_sol;
        mutate(num_mut,sol,matriz);
        ES(sol,matriz,num_sel,num_elements);
        if(sol.fitness>best_sol.fitness) best_sol=sol;
    }

    total=clock()-start;
    // Imprime el resultado en el formato: Fitness, Tiempo
    cout << setprecision(2) << fixed << best_sol.fitness  << ", " << setprecision(6)<< (double) total/CLOCKS_PER_SEC << endl;
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

    //Ejecutamos el algoritmo
    ILS_ES(matriz,num_sel,num_elements,seed);
}