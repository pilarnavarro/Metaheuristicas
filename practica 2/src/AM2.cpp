#include <iostream>
#include <vector>
#include <queue>
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
void readInput (vector<vector<double> > &matrix){
    unsigned i, j;
    double dist, index1, index2;
    for (i=0; i<matrix.size(); i++){
        for (j=i+1; j<matrix.size(); j++){
            cin >> index1 >> index2 >> dist;
            matrix[i][j] = matrix[j][i] = dist;
        }
    }
}

//-------------------------ESTRUCTURA DE LA SOLUCION-------------------------

struct solution_bin{
    vector<bool> elements;
    double fitness;
    bool evaluated;

    //Operador de asignación
    void operator = (const solution_bin &sol) { 
            elements = sol.elements;
            fitness = sol.fitness;
            evaluated = sol.evaluated;
    } 
};

struct population{
    vector<solution_bin> solutions;
    double best_fitness;
    int best_sol;

    //Operador de asignación
    void operator = (const population &pop) { 
        solutions=pop.solutions;
        solutions = pop.solutions;
        best_fitness = pop.best_fitness;
        best_sol=pop.best_sol;
    }
};

//------------------- OUTPUT ---------------------

//Imprime la matriz que se le pasa como parámetro
void printMatrix(const vector<vector<double> > &matrix){
    cout << "Matriz de distancias:" << endl;
    for(unsigned i=0; i<matrix.size(); i++){
        for(unsigned j=0; j<matrix.size(); j++){
            cout << matrix[i][j] << " ";
        }
    cout << endl;
    }
}

//Imprime el vector de elementos que se le pasa como parámetro, correspondiente a una solución
void printSol(const vector<bool> &elements){
    for(unsigned i = 0; i < elements.size(); i++){
        cout<< elements[i]<< " " ;
    }
    cout << endl;
}

//Imprime la población de soluciones que se le pasa como parámetro
void printPop(const population &pop){
    for(unsigned i = 0; i < pop.solutions.size(); i++){
        for(unsigned j = 0; j < pop.solutions[0].elements.size(); j++)
            cout<< pop.solutions[i].elements[j] << " " ;
        cout << endl;
    }
}

//-------------------------- FUNCIONES AUXILIARES ---------------------------

/* Calcula el fitness de la solución pasada como parámetro, es decir, 
    suma las distancias entre todos los elementos presentes en la misma */
double fitness(const vector<bool> &sol, const vector<vector<double> > &matrix){
    double sum = 0;
    for(unsigned i = 0; i<sol.size();i++){
        for(unsigned j = i+1; j<sol.size();j++){ 
            if(sol[i] && sol[j]) sum += matrix[i][j];
        }
    }
    return sum;
}

/* Calcula la contribución del elemento 'element', es decir,
    suma las distancias de ese elemento a todos los demás 
    presentes en la solución pasada como parámetro */
double contribution(const vector<bool> &sol, const vector<vector<double> > &matrix, const int &element){
    double sum=0;
    for(unsigned i=0; i<sol.size();i++){
        if(sol[i]) sum+=matrix[element][i];
    }
    return sum;
}

/*Asigna a cada solución de la población 'pop' su correspondiente fitness y
determina la solución dentro de la población que tiene el valor de fitness más alto*/
void evaluatePopulation(population & pop, const vector<vector<double> > & matrix, int &evaluations){
    int pos=pop.best_sol;    //Posicion de la mejor solución de la población
    double best_fit = pop.best_fitness;    //Fitnes de la mejor solución 

    for(unsigned i = 0; i < pop.solutions.size(); i++){
        if(!pop.solutions[i].evaluated){
            evaluations++;
            pop.solutions[i].fitness = fitness(pop.solutions[i].elements, matrix);
            pop.solutions[i].evaluated=true;
            if(best_fit < pop.solutions[i].fitness){
                best_fit = pop.solutions[i].fitness;
                pos = i;
            }
        }
    }
    pop.best_sol=pos;
    pop.best_fitness=best_fit;
}

// Genera una solución aleatoria válida, que se almacena en el parámetro 'sol'
void randomSolution(solution_bin &sol, const unsigned int &num_sel, const vector<vector<double> > &matrix){
    int size=matrix.size();
    int randt,chosen=0;
    sol.elements=vector<bool>(size,false); //Inicializamos a 0 todos los elementos de la solución

    while(chosen<num_sel){
        randt=rand()% size; //Número entero aleatorio en el intervalo [0,size)
        if(!sol.elements[randt]){
            sol.elements[randt]=true;
            chosen++;
        } 
    }
    sol.evaluated=false;
}

// Genera una población de soluciones válidas, de tamaño size_pop, que se almacena en el parámetro 'pop'
void randomPopulation(population &pop, const unsigned int &size_pop, const unsigned int &num_sel, const vector<vector<double> > &matrix, int &evaluations){
    solution_bin sol;

    for(unsigned i = 0; i < size_pop; i++){
        randomSolution(sol,num_sel,matrix);
        pop.solutions.push_back(sol);
    }

    pop.best_sol=-1;
    pop.best_fitness=0;
    //evaluatePopulation(pop,matrix,evaluations);
}

/*Determina la posición de la solución en la población 'pop' que presenta
el valor de fitness más bajo, o sea, la peor solución de la población*/
int worstSolution(const population &pop){
    int pos = -1;
    double min_fitness = std::numeric_limits<double>::infinity();

    for(unsigned i = 0; i < pop.solutions.size(); i++){
        if(min_fitness > pop.solutions[i].fitness){
            pos = i ;
            min_fitness = pop.solutions[i].fitness;
        }
    }
    return pos;
}

//Actualiza la mejor solución de la población 'pop'
void updateBest(population &pop){
    double max_fitness=pop.best_fitness;
    int pos;
    for(unsigned i=0;i<pop.solutions.size();i++){
        if(pop.solutions[i].fitness>max_fitness){
            max_fitness=pop.solutions[i].fitness;
            pos=i;
        }
    }
    pop.best_fitness=max_fitness;
    pop.best_sol=pos;
}

//--------------------------------ALGORITMO GENÉTICO-------------------------------------

/*Función que implementa el torneo binario, esto es, 
selecciona dos soluciones aleatorias de la población 'pop'
y devuelve la posición de la que tiene un fitness mayor
de entre las dos seleccionadas */
int binaryCompetition(const population &pop){
    int size=pop.solutions.size();
    int rand1 = rand()%size;
    int rand2 = rand()%size;
    return pop.solutions[rand1].fitness > pop.solutions[rand2].fitness ? rand1 : rand2;
}

/*Operador de selección. 
Selecciona una nueva población de soluciones que se almacena en 'new_pop'
de entre las presentes en 'old_pop' usando la estrategia de torneo binario
*/
void selection(population &new_pop, const population &old_pop){
    int pos = 0;
    new_pop.best_fitness=0;
    new_pop.best_sol=-1;
    new_pop.solutions.resize(old_pop.solutions.size());

    for(unsigned i = 0 ; i < old_pop.solutions.size(); i++){
        pos = binaryCompetition(old_pop);  
        new_pop.solutions[i]=old_pop.solutions[pos];
    }
}

/*Intercambia los valores de dos posiciones aleatorias de la solución 
'sol' que tengan distinto valor*/
void mutateSolution(solution_bin &sol, const vector<vector<double> > &matrix) {
    int pos1, pos2;
    int size=sol.elements.size();

    //Posición aleatoria de la solución que tenga el valor 1 (true)
    do{
        pos1 = rand()%size;
    }while(!sol.elements[pos1] );

    //Posición aleatoria de la solución que tenga el valor 0 (false)
    do{
        pos2 = rand()%size;
    }while(sol.elements[pos2]);

    //Intercambiamos los valores de las posiciones seleccionadas
    sol.elements[pos1] = false;
    sol.elements[pos2] = true;
    
    sol.evaluated=false;
}

/*  Operador de mutación.
    Muta una solución aleatoria de la población 'pop',
    con probabilidad 'mut_prob'*/
void mutation(population &pop,const double &mut_prob,const vector<vector<double> > &matrix){
    int pos=0;
    int num_mut = mut_prob*pop.solutions.size();

    for(unsigned i=0;i<num_mut;i++){
        pos=rand()%pop.solutions.size();
        mutateSolution(pop.solutions[pos],matrix);
    }
}

/* Operador de reparación.
Comprueba si la solución 'sol' es factible, y en caso de 
no serlo, elimina los elementos sobrantes que contribuyen más a la solución 
o añade elementos que faltan que contribuyan más a dicha solución.
*/
void repair(solution_bin &sol, const int &num_sel, const vector<vector<double> > &matrix){
    int selected=0;
    int max_contrib=0, max_pos=-1, contrib;
    for(unsigned i=0;i<sol.elements.size();i++){
        if(sol.elements[i]) selected++;
    }

    while(selected>num_sel){
        for(unsigned i=0;i<sol.elements.size();i++){
            if(sol.elements[i]){
                contrib=contribution(sol.elements,matrix,i);
                if(contrib>max_contrib){
                    max_contrib=contrib;
                    max_pos=i;
                }
            }
        }
        sol.elements[max_pos]=false;
        selected--;
        max_contrib=0;
        max_pos=-1;
    }

    while(selected<num_sel){
        for(unsigned i=0;i<sol.elements.size();i++){
            if(!sol.elements[i]){
                contrib=contribution(sol.elements,matrix,i);
                if(contrib>max_contrib){
                    max_contrib=contrib;
                    max_pos=i;
                }
            }
        }
        sol.elements[max_pos]=true;
        selected++;
        max_contrib=0;
        max_pos=-1;
    }
}

/*Operador de cruce uniforme.
Genera una nueva solución válida 'son' a partir de otras dos
soluciones dadas 'father' y 'mother'*/
void UniformCross(const solution_bin &father, const solution_bin &mother, solution_bin &son, const int &num_sel, const vector<vector<double> > &matrix){
    int size_sol = father.elements.size();
    son.elements.resize(size_sol);
    
    vector<int> to_change;  //Posiciones de las soluciones que no son comunes en father y mother

    //Determinamos las posiciones que tienen valores iguales en father y mother y las que no
    for(unsigned i = 0; i < size_sol; i++){
        if(father.elements[i] == mother.elements[i]){
            son.elements[i] =  mother.elements[i];
        }else{
            to_change.push_back(i);
        }
    }

    for(unsigned j = 0 ; j < to_change.size() ; j++){
        //Metemos en las posiciones vacías del hijo un elemento aleatorio en [0,2)
        son.elements[to_change[j]] = rand()%2;
    }
    
    //Modificamos la solución obtenida para que sea factible
    repair(son,num_sel,matrix);
    
    son.evaluated=false;
}

/*Implementa el cruce, donde se generan dos nuevas soluciones hijas
a partir de dos soluciones padre de la población pop, 
haciendo uso del operador de cruce uniforme.
Las nuevas soluciones sustituyen a los padres y cada
pareja de soluciones se cruza con probabilidad 'cross_prob'*/
void cross(population &pop, const double &cross_prob, const int &num_sel,const vector<vector<double> > &matrix){
    solution_bin sol1,sol2;
    int num_cross=cross_prob*pop.solutions.size()/2;    //Número esperado de soluciones que cruzan
    for(unsigned i = 0; i < num_cross ; i++){
        UniformCross(pop.solutions[2*i], pop.solutions[2*i+1], sol1, num_sel,matrix);  //Se cruzan soluciones consecutivas en la población
        UniformCross(pop.solutions[2*i], pop.solutions[2*i+1], sol2, num_sel,matrix);
        pop.solutions[2*i] = sol1;      //Las nuevas soluciones generadas sustituyen a los padres
        pop.solutions[2*i+1] = sol2;
    }
}

/*Se reemplaza la población 'old_pop' por 'new_pop',
manteniendo la mejor solución de 'old_pop' en caso de 
ser mejor que la mejor solución de 'new_pop'*/
void replace(population &old_pop, population &new_pop, const vector<vector<double> > &matrix){
    int pos=-1;

    //Si la mejor solución de la población antigua es mejor que la de la nueva,
    //la guardamos en la posición de la población nueva que contine a la peor solución
    if(old_pop.best_fitness > new_pop.best_fitness){
        new_pop.best_fitness = old_pop.best_fitness;
        pos= worstSolution(new_pop); //new_pop.solutions.size()-1;
        new_pop.solutions[pos]=old_pop.solutions[old_pop.best_sol];
        new_pop.best_sol=pos;
        //new_pop.solutions[pos].evaluated=true;
    }

    old_pop=new_pop;  //Reemplazamos las poblaciones
}

//----------------------------------BÚSQUEDA LOCAL-------------------------------------

struct solution{
    vector<int> elements;
    double fitness;

    //Operador de asignación
    void operator = (const solution &sol) { 
            elements = sol.elements;
            fitness = sol.fitness;
    } 
};

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
void randomSolution (solution &sol, const unsigned int &num_sel, const vector<vector<double> > &matriz){
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

/* Determina si la solución 'sol' mejora al cambiar el elemento en la posición 'pos' de la solución por 
  el elemento 'elem'. En caso afirmativo la función devuelve True y la solución 'sol' se actualiza, cambiando 
  el elemento en la posición 'pos' por 'elem'. En otro caso se devuelve False y la solución permanece inaletrada */
bool improvement(solution &sol, const unsigned int &pos, const double &old_cont, const unsigned int &elem, const vector<vector<double> > &matriz){
  solution nueva; 
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
    Determina el conjunto de num_sel elementos que proporciona el valor de fitness más alto*/
void localSearch(const vector<vector<double> > &matriz, solution &sol, int &evaluations,const unsigned int &num_sel){
    bool mejora;
    unsigned int old_elem, new_elem;
    int num_eval=0;
    vector<int> valid_elements; 
    pair<int,double> min_contrib;

    
    validElements(valid_elements,sol.elements,matriz.size());   //Seleccionamos los elementos por los que podemos intercambiar 

    // Determinamos el elemento que menos contribuye y su contribución
    min_contrib=lowestContribution(sol.elements,matriz);

    mejora=true;
    while(mejora and num_eval < 400){  //Iteramos mientras la solución mejore y no se haya superado el número máximo de evaluaciones
        mejora = false;
        old_elem=sol.elements[min_contrib.first];  //Guardamos el elemento antiguo que vamos a intercambiar

        //Mezclamos los posibles elementos por los que podemos intercambiar un elemento de la solución
        shuffle(valid_elements.begin(),valid_elements.end(),default_random_engine(seed));

        unsigned k;
        //Intercambiamos el elemento que menos contribuye por todos los posibles hasta que se poroduzca una mejora
        for(k = 0 ; k < valid_elements.size() and mejora == false and num_eval<400 and evaluations<100000; k++){
            new_elem=valid_elements[k];  
            mejora = improvement(sol,min_contrib.first,min_contrib.second,new_elem,matriz);                                                                                        
            num_eval++;
            evaluations++;
        }

        if (mejora){   //Si ha habido mejora, se ha cambiado la solución
            valid_elements[k-1]=old_elem;  //Actualizamos los elementos válidos, cambiando el elemento nuevo por el antiguo
            //Volvemos a determinar el elemento que menos contribuye en la nueva solución
            min_contrib=lowestContribution(sol.elements,matriz);
        }
    }
}

//Transforma una solución del tipo binario 'solution_bin',
//a una solución de enteros 'solution'.
void BinToInt(const solution_bin &sol_bin, solution &sol){
    if(!sol.elements.empty())
        sol.elements.clear();
    for(unsigned i=0; i<sol_bin.elements.size(); i++) {
        if (sol_bin.elements[i]) sol.elements.push_back(i);
    }
    sol.fitness=sol_bin.fitness;
}

//Transforma una solución de enteros 'solution'
//a una solución del tipo binario 'solution_bin',
void IntToBin(const solution &sol, solution_bin &sol_bin, int size){
    sol_bin.elements = vector<bool> (size, false);
    for(unsigned i=0; i<sol.elements.size(); i++) 
        sol_bin.elements[sol.elements[i]] = true;
    sol_bin.fitness=sol.fitness;
    sol_bin.evaluated=true;
}


/*  Implementa un algoritmo memético usando el algoritmo genético generacional 
    con operador de cruce uniforme y aplicando búsqueda local a las soluciones de 
    la población obtenida cada 10 generaciones con una probabilidad de 0.1.
    Imprime por pantalla el fitness de la mejor solución de la población encontrada,
    así como el tiempo de ejecución del algorimo en segundos, el número de poblaciones generadas
    y el número de evaluaciones de la función fitness. */
void AM2(const vector<vector<double> > &matrix, const unsigned int &num_sel, const int &seed){
    clock_t start, total;
    int evaluations=0, size_pop=50;
    double mut_prob=0.1, cross_prob=0.7;
    int generations=1;
    int num_local=0.1*size_pop;
    population new_pop, old_pop;
    solution_bin best_sol;
    solution sol;
    int rand_pos;

    srand(seed);    //Fijamos la semilla

    start=clock();

    randomPopulation(old_pop,size_pop,num_sel,matrix,evaluations); //Empezamos con una población aleatoria

    while(evaluations<100000){
        selection(new_pop,old_pop);
        cross(new_pop,cross_prob,num_sel,matrix);
        mutation(new_pop,mut_prob,matrix);
        evaluatePopulation(new_pop,matrix,evaluations);
        if(generations%10==0){  //Se ejecuta cada 10 generaciones
            for(unsigned i=0;i<num_local and evaluations<100000;i++){
                rand_pos=rand()%new_pop.solutions.size();  //Posición aleatoria de una solución
                BinToInt(new_pop.solutions[rand_pos],sol);
                localSearch(matrix,sol,evaluations,num_sel);
                IntToBin(sol,new_pop.solutions[rand_pos],matrix.size());
            }
            updateBest(new_pop);
        }
        replace(old_pop,new_pop,matrix);
        generations++;
    }

    total=clock()-start;
    // Imprime el resultado en el formato: Fitness, Tiempo, Generaciones, Evaluaciones
    cout << setprecision(2) << fixed << old_pop.best_fitness  << ", " << setprecision(6)<< (double) total/CLOCKS_PER_SEC 
    << ", " << generations<< ", " <<evaluations<<endl;
}


int main(int argc, char *argv[]){
    //Leemos el fichero de datos e inicializamos la matriz de distancias
    int num_elements, num_sel;
    const int seed=atoi(argv[1]);
    cin >> num_elements >> num_sel;
    vector<double> aux(num_elements, 0);
    vector<vector<double> > matrix(num_elements, aux);
    readInput(matrix);

    //Ejecutamos el algoritmo
    AM2(matrix,num_sel,seed);
}
