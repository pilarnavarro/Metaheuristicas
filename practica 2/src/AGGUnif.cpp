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

/**/
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


void mutation(population &pop,const double &mut_prob,const vector<vector<double> > &matrix){
    int pos=0;
    int num_mut = mut_prob*pop.solutions.size();

    for(unsigned i=0;i<num_mut;i++){
        pos=rand()%pop.solutions.size();
        mutateSolution(pop.solutions[pos],matrix);
    }
}

//Operador de reparación
void repair(solution &sol, const int &num_sel, const vector<vector<double> > &matrix){
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
void UniformCross(const solution &father, const solution &mother, solution &son, const int &num_sel, const vector<vector<double> > &matrix){
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

void cross(population &pop, const double &cross_prob, const int &num_sel,const vector<vector<double> > &matrix){
    solution sol1,sol2;
    int num_cross=cross_prob*pop.solutions.size()/2;
    for(unsigned i = 0; i < num_cross ; i++){
        UniformCross(pop.solutions[2*i], pop.solutions[2*i+1], sol1, num_sel,matrix);
        UniformCross(pop.solutions[2*i], pop.solutions[2*i+1], sol2, num_sel,matrix);
        pop.solutions[2*i] = sol1;
        pop.solutions[2*i+1] = sol2;
    }
}


void replace(population &old_pop, population &new_pop, const vector<vector<double> > &matrix){
    int pos=-1;

    //Si la mejor solución de la población antigua es mejor que la de la nueva,
    //la guardamos en la posición de la población nueva que contine a la peor solución
    if(old_pop.best_fitness > new_pop.best_fitness){
        new_pop.best_fitness = old_pop.best_fitness;
        pos= worstSolution(new_pop); //new_pop.solutions.size()-1;
        new_pop.solutions[pos]=old_pop.solutions[old_pop.best_sol];
        new_pop.best_sol=pos;
    }

    old_pop=new_pop;  //Reemplazamos las poblaciones
}

void UniformAGG(const vector<vector<double> > &matrix, const unsigned int &num_sel, const int &seed){
    clock_t start, total;
    int evaluations=0, size_pop=50;
    double mut_prob=0.1, cross_prob=0.7;
    int generations=0;
    population new_pop, old_pop;
    solution best_sol;

    srand(seed);    //Fijamos la semilla

    start=clock();

    randomPopulation(old_pop,size_pop,num_sel,matrix,evaluations); //Empezamos con una población aleatoria

    while(evaluations<100000){
        selection(new_pop,old_pop);
        cross(new_pop,cross_prob,num_sel,matrix);
        mutation(new_pop,mut_prob,matrix);
        evaluatePopulation(new_pop,matrix,evaluations);
        replace(old_pop,new_pop,matrix);
        generations++;
        //cout << "Iterations: " << evaluations << " <-> Fitnes: " << old_pop.best_fitness <<endl;
    }

    //best_sol=old_pop.solutions[old_pop.best_sol];

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
    UniformAGG(matrix,num_sel,seed);
}