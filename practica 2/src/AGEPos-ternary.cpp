#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>      // setprecision
#include <limits>       // numeric_limits<double>::infinity()


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

struct solution{
    vector<bool> elements;
    double fitness;
    bool evaluated;

    //Operador de asignación
    void operator = (const solution &sol) { 
            elements = sol.elements;
            fitness = sol.fitness;
            evaluated = sol.evaluated;
    } 
};

struct population{
    vector<solution> solutions;
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
void randomSolution(solution &sol, const unsigned int &num_sel, const vector<vector<double> > &matrix){
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
    solution sol;

    for(unsigned i = 0; i < size_pop; i++){
        randomSolution(sol,num_sel,matrix);
        pop.solutions.push_back(sol);
    }

    pop.best_sol=-1;
    pop.best_fitness=0;
    evaluatePopulation(pop,matrix,evaluations);
}

/*Determina las posiciones de las dos soluciones en la población 'pop' 
que presentan los valores de fitness más bajo, o sea, 
las dos peores soluciones de la población*/
pair<int,int> worstSolutions(const population &pop){
    pair<int,int> positions;
    int pos = -1;
    double min_fitness = std::numeric_limits<double>::infinity();

    for(unsigned i = 0; i < pop.solutions.size(); i++){
        if(min_fitness > pop.solutions[i].fitness){
            pos = i ;
            min_fitness = pop.solutions[i].fitness;
        }
    }
    positions.first=pos; //Peor solución
    
    pos = -1;
    min_fitness = std::numeric_limits<double>::infinity();

    for(unsigned i = 0; i < pop.solutions.size(); i++){
        if((min_fitness > pop.solutions[i].fitness) && i!=positions.first){
            pos = i ;
            min_fitness = pop.solutions[i].fitness;
        }
    }
    positions.second=pos;  //Segunda peor solución
    
    return positions;
}

//--------------------------------ALGORITMO GENÉTICO-------------------------------------

/*Función que implementa el torneo con tamaño 3, esto es, 
selecciona tres soluciones aleatorias de la población 'pop'
y devuelve la posición de la que tiene un fitness mayor
de entre las seleccionadas */
int ternaryCompetition(const population &pop){
    int size=pop.solutions.size();
    vector<int> rands;
    double best_fitness=0, best_pos=-1;

    for(unsigned i=0;i<3;i++){
        rands.push_back(rand()%size);
        if(pop.solutions[rands[i]].fitness>best_fitness){
            best_fitness=pop.solutions[rands[i]].fitness;
            best_pos=rands[i];
        }
    }    
    return best_pos;
}


/*Operador de selección. 
Selecciona dos soluciones aleatorias que se almacenan en 's1' y 's2' respectivamente,
de entre las presentes en la población 'pop', usando la estrategia de torneo con tamaño 3*/
void pairSelection(const population &pop,solution &s1,solution &s2){
    int pos1,pos2;

    pos1 = ternaryCompetition(pop);  
    pos2 = ternaryCompetition(pop);  

    s1=pop.solutions[pos1];
    s2=pop.solutions[pos2];
}

/*Intercambia los valores de dos posiciones aleatorias de la solución 
'sol' que tengan distinto valor*/
void mutateSolution(solution &sol, const vector<vector<double> > &matrix) {
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
    Muta una solución de entre 's1' y 's2',
    con probabilidad 'mut_prob'*/
void pairMutation(solution &s1,solution &s2, const double &mut_prob,const vector<vector<double> > &matrix){
    int pos;
    //Generamos un número aleatorio en [0,1]
    if((float) rand()/RAND_MAX < 2*mut_prob){
        pos=rand()%2;  //0 ó 1 aleatorio
        if(pos==0) mutateSolution(s1,matrix);
        else  mutateSolution(s2,matrix);
    }  
}

/*Operador de cruce basado en posición.
Genera una nueva solucion válida 'son' a partir de otras dos
soluciones dadas 'father' y 'mother'*/
void positionalCross(const solution &father, const solution &mother, solution &son, const int & seed){
    int size_sol = father.elements.size();
    son.elements.resize(size_sol);    
    vector<int> to_shuffle, to_change;  //Posiciones de las soluciones que no son comunes en father y mother

    //Determinamos las posiciones que tienen valores iguales en father y mother y las que no
    for(unsigned i = 0; i < size_sol; i++){
        if(father.elements[i] == mother.elements[i]){
            son.elements[i] = mother.elements[i];
        }else{
            to_shuffle.push_back(i),
            to_change.push_back(i);
        }
    }

    shuffle(to_shuffle.begin(),to_shuffle.end(),default_random_engine(seed));  //Barajamos las posiciones que no tienen elementos comunes
    for(unsigned j = 0 ; j < to_change.size() ; j++){
        //Metemos en las posiciones vacías del hijo el elemento aleatorio de un padre
        son.elements[to_change[j]] = mother.elements[to_shuffle[j]];
    }

    son.evaluated=false;
}

/*Implementa el cruce, donde se generan dos nuevas soluciones hijas,
's1' y 's2', a partir de dos soluciones padre, 'p1' y 'p2', 
haciendo uso del operador de cruce basado en posición.*/
void pairCross(const solution &p1, const solution &p2, solution &s1, solution &s2 , const int &seed){
    positionalCross(p1, p2, s1,seed);
    positionalCross(p1, p2, s2,seed);
}


/* Se introducen las soluciones 's1' y 's2' en las posiciones
de la población 'pop' que tienen las dos peores soluciones de la misma,
en caso de que sean mejores que estas.
*/
void replace(population &pop, const solution &s1, const solution &s2){
    pair<int,int> worst_pos=worstSolutions(pop);  //Determinamos las posiciones de las dos peores soluciones de la población
    solution worst_sol, best_sol;

    if(s1.fitness<s2.fitness){  //Vemos qué solución tiene mejor fitness y cúal peor de entre s1 y s2
        worst_sol=s1;
        best_sol=s2;
    }else{
        worst_sol=s2;
        best_sol=s1;
    } 

    //Si las soluciones s1 y s2 son mejores que las peores de la población 'pop', las intercambiamos
    if(pop.solutions[worst_pos.first].fitness<worst_sol.fitness && pop.solutions[worst_pos.second].fitness<best_sol.fitness){
            pop.solutions[worst_pos.first]=worst_sol;
            pop.solutions[worst_pos.second]=best_sol;
            if(best_sol.fitness>pop.best_fitness){  //Si el fitness de la mejor solución introducida supera al mejor fitness de la poblacion,
                pop.best_fitness=best_sol.fitness;   //actualizamos la mejor solución de la población
                pop.best_sol=worst_pos.second;
            }
    }else if(pop.solutions[worst_pos.first].fitness<best_sol.fitness){  //La mejor solución es mejor que la peor de la población 'pop'
            pop.solutions[worst_pos.first]=best_sol;
            if(best_sol.fitness>pop.best_fitness){   //actualizamos la mejor solución de la población
                pop.best_fitness=best_sol.fitness;
                pop.best_sol=worst_pos.first;
            }
    }
}


/*  Implementa el algoritmo genético estacionario usando operador de cruce basado en posición.
    Imprime por pantalla el fitness de la mejor solución de la población encontrada,
    así como el tiempo de ejecución del algorimo en segundos. */
void PositionalAGE(const vector<vector<double> > &matrix, const unsigned int &num_sel, const int &seed){
    clock_t start, total;
    int evaluations=0, size_pop=50;
    double mut_prob=0.1;  //Probabilidad de mutación por cromosoma
    population pop;
    solution p1,p2,s1,s2;

    srand(seed);    //Fijamos la semilla

    start=clock();

    randomPopulation(pop,size_pop,num_sel,matrix,evaluations); //Empezamos con una población aleatoria

    while(evaluations<100000){
        pairSelection(pop,p1,p2);
        pairCross(p1,p2,s1,s2,seed);
        pairMutation(s1,s2,mut_prob,matrix);
        s1.fitness=fitness(s1.elements,matrix);
        s1.evaluated=true;
        s2.fitness=fitness(s2.elements,matrix);
        s2.evaluated=true;
        evaluations+=2;
        replace(pop,s1,s2);
    }


    total=clock()-start;
    // Imprime el resultado en el formato: Fitness, Tiempo
    cout << setprecision(2) << fixed << pop.best_fitness  << ", " << setprecision(6)<< (double) total/CLOCKS_PER_SEC <<endl;
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
    PositionalAGE(matrix,num_sel,seed);
}
