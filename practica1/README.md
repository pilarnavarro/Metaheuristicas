Se explica en este archivo la estructura del proyecto. 

En la carpeta **src** se encuentra el código fuente. Contiene los siguientes archivos:

		- greedy.cpp -> implementación del algoritmo greedy
		
		- localSearch.cpp -> implementación del algoritmo de búsqueda local del primer mejor
		
		- localSearchMejor.cpp -> implementación del algoritmo de búsqueda local del mejor 
		
		- localSearchGreedy.cpp -> implementación del algoritmo de búsqueda local con greedy

La carpeta **data** contine los datos de los distintos casos de estudio para los que se ejecutan los algoritmos.

En **salida** encontramos varios ficheros .csv con los resultados de los algoritmos en el formato: Fitness, Tiempo de ejecución (en segundos).

La capeta **bin** tiene los ejecutables de cada uno de los algoritmos como se indica a continuación: 

		- greedy -> algoritmo greedy
		
		- localSearch ->  algoritmo de búsqueda local del primer mejor
		
		- localSearchMejor -> algoritmo de búsqueda local del mejor 
		
		- localSearchGreedy ->  algoritmo de búsqueda local con greedy
	
Por otra parte tenemos el fichero *makefile* para la compilación y el fichero *execute.sh*. Este último es un script que se encarga de ejecutar los distintos algoritmos para cada uno de los ficheros de los casos de estudio. La semilla para los algoritmos de búsqueda local se fija dentro de este archivo, y se puede cambiar de una ejecución a otra. Al ejecutar la orden *make* se compilan todos los ficheros de código fuente y se ejecuta el script *execute.sh*. 
