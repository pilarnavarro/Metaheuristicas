extern "C" {
#include "cec17.h"
}
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>    // shuffle and find
#include <random>       // rand
#include <limits>       // numeric_limits<double>::infinity()

using namespace std;
int dim = 30;
std::uniform_real_distribution<> dis(-100.0, 100.0);

//-------------------------ESTRUCTURA DE LA SOLUCION-------------------------

struct Antibody{
    vector<double> elements;
    double fitness;
    bool evaluated;

    //Operador de asignación
    void operator = (const Antibody& sol) { 
            elements = sol.elements;
            fitness = sol.fitness;
            evaluated = sol.evaluated;
    } 
};

struct population{
    vector<Antibody> solutions;
    double best_fitness;
    int best_sol;

    //Operador de asignación
    void operator = (const population &pop) { 
        solutions=pop.solutions;
        best_fitness = pop.best_fitness;
        best_sol=pop.best_sol;
    }
};

//-------------------------- FUNCIONES AUXILIARES ---------------------------

/*Asigna a cada solución de la población 'pop' su correspondiente fitness y
determina la solución dentro de la población que tiene el valor de fitness más bajo*/
void evaluatePopulation(population & pop,  int &evaluations){
    int pos=pop.best_sol;    //Posicion de la mejor solución de la población
    double best_fit = pop.best_fitness;    //Fitness de la mejor solución 

    for(unsigned i = 0; i < pop.solutions.size(); i++){
        if(!pop.solutions[i].evaluated && evaluations<10000*dim){
            evaluations++;
            pop.solutions[i].fitness = cec17_fitness(&pop.solutions[i].elements[0]);
            pop.solutions[i].evaluated=true;
            if(best_fit > pop.solutions[i].fitness){
                best_fit = pop.solutions[i].fitness;
                pos = i;
            }
        }
    }
    pop.best_sol=pos;
    pop.best_fitness=best_fit;
}

// Genera una solución aleatoria válida, que se almacena en el parámetro 'sol'
void randomSolution(Antibody &sol, mt19937 gen){
    sol.elements=vector<double>(dim,0.0); //Inicializamos a 0 todos los elementos de la solución

    for(int i = 0 ; i < dim ; i++){
        sol.elements[i]=dis(gen);
    }

    sol.evaluated=false;
}

// Genera una población de soluciones válidas, de tamaño size_pop, que se almacena en el parámetro 'pop'
void randomPopulation(population &pop, const unsigned int &size_pop, int &evaluations, mt19937 gen){

    for(unsigned i = 0; i < size_pop; i++){
        Antibody sol;
        randomSolution(sol,gen);
        pop.solutions.push_back(sol);
    }

    pop.best_sol=-1;
    pop.best_fitness= numeric_limits<double>::infinity();
    evaluatePopulation(pop,evaluations);
}

bool comp(Antibody &sol1,Antibody &sol2){
    return sol1.fitness<sol2.fitness;
}


//--------------------------------CLONALG-------------------------------------

/*Operador de selección. 
Selecciona una nueva población de soluciones que se almacena en 'new_pop', 
constituida por el 'perc_sel*100' porcentaje de las mejores soluciones de 'old_pop'
*/
void selection(population &new_pop, population &old_pop, const double perc_sel){
    int pos = 0;
    new_pop.solutions.resize(round(perc_sel*old_pop.solutions.size()));

    sort(old_pop.solutions.begin(), old_pop.solutions.end(),comp);
    for(unsigned i = 0 ; i < new_pop.solutions.size(); i++){  
        new_pop.solutions[i]=old_pop.solutions[i];
    }
    
    new_pop.best_fitness= new_pop.solutions[0].fitness;
    new_pop.best_sol=0;
}

//Operador de clonación. 
void clone(population & new_pop, population &C, const double perc_clone){
    int n_clones=new_pop.solutions.size()*perc_clone;
    C.solutions.resize(n_clones);

    for(unsigned i=0; i<n_clones; i++){
        C.solutions[i]=new_pop.solutions[i];
    }

    C.best_fitness=C.solutions[0].fitness;
    C.best_sol=0;
}


// Operador de mutación
void mutation(population &C, mt19937 gen){
    int pos;
    double value;

    for(int i=0;i<C.solutions.size();i++){  
        for(unsigned j=0; j<i; j++){
            pos=rand()%dim;
            C.solutions[i].elements[pos]=dis(gen);
            C.solutions[i].evaluated=false;
        }
    }
}

/* Se reemplazan los anticuerpos menos afines de la población 'old_pop' 
por todos los de 'new_pop' */
void replace(population &old_pop, population &new_pop){
    int size=old_pop.solutions.size();
    sort(old_pop.solutions.begin(),old_pop.solutions.end(),comp);
    //Reemplazamos por los últimos, que serán los menos afines
    for(unsigned i=0;i<new_pop.solutions.size();i++)
        old_pop.solutions[size-1-i]=new_pop.solutions[i];
    
    sort(old_pop.solutions.begin(),old_pop.solutions.end(),comp);

    old_pop.best_fitness=old_pop.solutions[0].fitness;
    old_pop.best_sol=0;
}

/* Se reemplazan el 'perc_worst*100' por ciento de los anticuerpos menos afines
de la población 'pop' por soluciones aleatorias*/
void replaceWorst(population & pop, double perc_worst, mt19937 gen){
    int size=pop.solutions.size();
    int num_replace=size*perc_worst;

    for(unsigned i=0;i<num_replace;i++){
        randomSolution(pop.solutions[size-1-i],gen);
    }

    sort(pop.solutions.begin(),pop.solutions.end(),comp);

    pop.best_fitness=pop.solutions[0].fitness;
    pop.best_sol=0;
}

//Algoritmo de la selección clonal (CLONALG)
void CLONALG(const char *algname, int func_id, mt19937 gen){

    cec17_init(algname,func_id,dim);
    int evaluations=0, size_pop=50;
    population new_pop, old_pop, C;
    double perc_sel=0.3, perc_clone=0.5, perc_worst=0.1;

    randomPopulation(old_pop,size_pop,evaluations,gen);
    while(evaluations<10000*dim){
        //cout<<evaluations<<endl;
        selection(new_pop,old_pop,perc_sel);
        clone(new_pop,C,perc_clone);
        mutation(C,gen);
        evaluatePopulation(C,evaluations);
        //sort(C.solutions.begin(),C.solutions.end(),comp);
        replace(new_pop,C);
        replace(old_pop,new_pop);
        replaceWorst(old_pop,0.1,gen);
        evaluatePopulation(old_pop,evaluations);
    }

    double best_fitness = old_pop.best_fitness;

    cout << "\nEvaluaciones: " << evaluations << endl;
    cout <<"\nBest Sol[F" <<func_id <<"]: " << scientific << cec17_error(best_fitness) <<endl;
    cout << endl;
}


int main(){
    for(int func_ID = 1 ; func_ID <=30 ; func_ID++){
        for(int i = 0 ; i < 10; i++){
            mt19937 gen(i);
            CLONALG("CLONALG",func_ID,gen);
        }
    }
}
