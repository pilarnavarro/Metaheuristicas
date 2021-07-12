### Práctica 3

Se explica en este archivo la estructura del proyecto. 

En la carpeta **src** se encuentra el código fuente. Contiene los siguientes archivos:

		- greedy.cpp -> implementación del algoritmo greedy
		
		- localSearch.cpp -> implementación del algoritmo de búsqueda local del primer mejor
						
		- ES -> implementación del algoritmo de enfriamiento simulado
		
		- ES-Prop -> implementación del algoritmo de enfriamiento simulado con esquema proporcional
		
		- ES2 -> implementación del algoritmo de enfriamiento simulado segunda versión
		
		- ES3 -> implementación del algoritmo de enfriamiento simulado tercera versión
		
		- BMB -> implementación del algoritmo de la búsqueda multiarranque básica
		
		- ILS -> implementación del algoritmo de la búsqueda local iterativa
		
		- ILS2 -> implementación del algoritmo de la búsqueda local iterativa segunda versión
		
		- ILS-ES -> implementación del algoritmo de la búsqueda local iterativa con enfriamiento simulado
		
		- ILS-ES-Prop -> implementación del algoritmo de la búsqueda local iterativa con enfriamiento simulado y ºesquema proporcional

La carpeta **data** contine los datos de los distintos casos de estudio para los que se ejecutan los algoritmos.

En **salida** encontramos varios ficheros .csv con los resultados de los algoritmos en el formato: Fitness, Tiempo de ejecución (en segundos).

La capeta **bin** tiene los ejecutables de cada uno de los algoritmos como se indica a continuación: 

		- greedy -> algoritmo greedy
		
		- localSearch -> algoritmo de búsqueda local del primer mejor
		
		- ES -> algoritmo de enfriamiento simulado
		
		- ES-Prop -> algoritmo de enfriamiento simulado con esquema proporcional
		
		- ES2 -> algoritmo de enfriamiento simulado segunda versión
		
		- ES3 -> algoritmo de enfriamiento simulado tercera versión
		
		- BMB -> algoritmo de la búsqueda multiarranque básica
		
		- ILS -> algoritmo de la búsqueda local iterativa
		
		- ILS2 -> algoritmo de la búsqueda local iterativa segunda versión
		
		- ILS-ES -> algoritmo de la búsqueda local iterativa con enfriamiento simulado
		
		- ILS-ES-Prop -> algoritmo de la búsqueda local iterativa con enfriamiento simulado y ºesquema proporcional
		
Por otra parte tenemos el fichero *makefile* para la compilación y el fichero *execute.sh*. Este último es un script que se encarga de ejecutar los distintos algoritmos para cada uno de los ficheros de los casos de estudio. La semilla para los algoritmos de búsqueda local se fija dentro de este archivo, y se puede cambiar de una ejecución a otra. Al ejecutar la orden *make* se compilan todos los ficheros de código fuente y se ejecuta el script *execute.sh*. 
