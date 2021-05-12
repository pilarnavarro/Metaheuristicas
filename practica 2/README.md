### Práctica 2

Se explica en este archivo la estructura del proyecto. 

En la carpeta **src** se encuentra el código fuente. Contiene los siguientes archivos:

		- greedy.cpp -> implementación del algoritmo greedy
		
		- localSearch.cpp -> implementación del algoritmo de búsqueda local del primer mejor
		
		- AGGPos -> implementación del algoritmo genético generacional con operador de cruce basado en posición
		
		- AGGPos-ternary ->  implementación del algoritmo genético generacional con operador de cruce basado en posición y selección por torneo de tamaño 3
		
		- AGGPos-bestcross ->  implementación del algoritmo genético generacional con operador de cruce basado en posición modificado, donde siempre se cruza la mejor solución
		
		- AGEPos ->  implementación del algoritmo genético estacionario con operador de cruce basado en posición
		
		- AGEPos-ternary ->  implementación del algoritmo genético estacionario con operador de cruce basado en posición y selección por torneo de tamaño 3
		
		- AGEUnif ->  implementación del algoritmo genético estacionario con operador de cruce uniforme
		
		- AGGUnif ->  implementación del algoritmo genético generacional con operador de cruce uniforme
		
		- AGGUnif-2 ->  implementación del algoritmo genético estacionario con operador de cruce uniforme modificado
		
		- AM1 -> implementación de la primera versión de los algoritmos meméticos AM-(10,1)
		
		- AM2 ->  implementación de la segunda versión de los algoritmos meméticos AM-(10,0.1)
		
		- AM2-2 ->  implementación de la segunda versión de los algoritmos meméticos modificada AM-(1,0.1)
		
		- AM3 ->  implementación de la tercera versión de los algoritmos meméticos AM-(10,0.1mejores)
		
		- AM3-peores ->  implementación de la tercera versión de los algoritmos meméticos modificada AM-(10,0.1peores)

La carpeta **data** contine los datos de los distintos casos de estudio para los que se ejecutan los algoritmos.

En **salida** encontramos varios ficheros .csv con los resultados de los algoritmos en el formato: Fitness, Tiempo de ejecución (en segundos). Para algunos algoritmos el formato será Fitness, Tiempo de ejecución (s), Generaciones, Evaluaciones.

La capeta **bin** tiene los ejecutables de cada uno de los algoritmos como se indica a continuación: 

		- greedy -> algoritmo greedy
		
		- localSearch -> algoritmo de búsqueda local del primer mejor
		
		- AGGPos -> algoritmo genético generacional con operador de cruce basado en posición
		
		- AGGPos-ternary -> algoritmo genético generacional con operador de cruce basado en posición y selección por torneo de tamaño 3
		
		- AGGPos-bestcross -> algoritmo genético generacional con operador de cruce basado en posición modificado, donde siempre se cruza la mejor solución
		
		- AGEPos ->  algoritmo genético estacionario con operador de cruce basado en posición
		
		- AGEPos-ternary -> algoritmo genético estacionario con operador de cruce basado en posición y selección por torneo de tamaño 3
		
		- AGEUnif -> algoritmo genético estacionario con operador de cruce uniforme
		
		- AGGUnif -> algoritmo genético generacional con operador de cruce uniforme
		
		- AGGUnif-2 -> algoritmo genético estacionario con operador de cruce uniforme modificado
		
		- AM1 -> primera versión de los algoritmos meméticos AM-(10,1)
		
		- AM2 -> segunda versión de los algoritmos meméticos AM-(10,0.1)
		
		- AM2-2 -> segunda versión de los algoritmos meméticos modificada AM-(1,0.1)
		
		- AM3 -> tercera versión de los algoritmos meméticos AM-(10,0.1mejores)
		
		- AM3-peores -> tercera versión de los algoritmos meméticos modificada AM-(10,0.1peores)
	
Por otra parte tenemos el fichero *makefile* para la compilación y los ficheros *execute_p1.sh*, *execute_genetic.sh*, *execute_memetic.sh*,  *execute_extras.sh*. Estos son scripts que se encarga de ejecutar los  algoritmos de la práctica 1, los algoritmos genéticos, los algoritmos meméticos y los algoritmos extra, respectivamente, para cada uno de los ficheros de los casos de estudio. La semilla para los algoritmos de búsqueda local se fija dentro de estos archivos, y se puede cambiar de una ejecución a otra. Al ejecutar la orden *make all* se compilan todos los ficheros de código fuente. Con las órdenes *make execute_p1*, *make execute_genetic*, *make execute_memetic* y *make execute_extras* se compilan los ficheros necesarios y se ejecuta el script del mismo nombre. 
