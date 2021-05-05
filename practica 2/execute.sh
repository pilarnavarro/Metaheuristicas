#!/bin/bash
input="data"
bin="bin"
out_local="salida/localSearch.csv"
out_greedy="salida/greedy.csv"
out_local_mejor="salida/localSearchMejor.csv"
out_local_greedy="salida/localSearchGreedy.csv"
semilla=7413

touch ${out_local_greedy}
rm ${out_local_greedy}
touch ${out_local_greedy}

touch ${out_local_mejor}
rm ${out_local_mejor}
touch ${out_local_mejor}

touch ${out_greedy}
rm ${out_greedy}
touch ${out_greedy}

touch ${out_local}
rm ${out_local}
touch ${out_local}

for i in {1..10}
do
  echo "Ejecutando greedy para MDG-a_$i"
  ${bin}/greedy < ${input}/MDG-a_${i}_* >> ${out_greedy}
  echo "Ejecutando búsqueda local del primer mejor para MDG-a_$i"
  ${bin}/localSearch ${semilla} < ${input}/MDG-a_${i}_* >> ${out_local}
  echo "Ejecutando búsqueda local del mejor para MDG-a_$i"
  ${bin}/localSearchMejor ${semilla} < ${input}/MDG-a_${i}_* >> ${out_local_mejor}
  echo "Ejecutando búsqueda local con inicialización Greedy para MDG-a_$i"
  ${bin}/localSearchGreedy ${semilla} < ${input}/MDG-a_${i}_* >> ${out_local_greedy}
done

for i in {21..30}
do
  echo "Ejecutando greedy para MDG-b_$i"
  ${bin}/greedy < ${input}/MDG-b_${i}_* >> ${out_greedy}
  echo "Ejecutando búsqueda local del primer mejor para MDG-b_$i"
  ${bin}/localSearch ${semilla} < ${input}/MDG-b_${i}_* >> ${out_local}
  echo "Ejecutando búsqueda local del mejor para MDG-b_$i"
  ${bin}/localSearchMejor ${semilla} < ${input}/MDG-b_${i}_* >> ${out_local_mejor}
  echo "Ejecutando búsqueda local con inicialización Greedy para MDG-b_$i"
  ${bin}/localSearchGreedy ${semilla} < ${input}/MDG-b_${i}_* >> ${out_local_greedy}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
  echo "Ejecutando greedy para MDG-c_$i"
  ${bin}/greedy < ${input}/MDG-c_${i}_* >> ${out_greedy}
  echo "Ejecutando búsqueda local del primer mejor para MDG-c_$i"
  ${bin}/localSearch ${semilla} < ${input}/MDG-c_${i}_* >> ${out_local}
  echo "Ejecutando búsqueda local del mejor para MDG-c_$i"
  ${bin}/localSearchMejor ${semilla} < ${input}/MDG-c_${i}_* >> ${out_local_mejor}
  echo "Ejecutando búsqueda local con inicialización Greedy para MDG-c_$i"
  ${bin}/localSearchGreedy ${semilla} < ${input}/MDG-c_${i}_* >> ${out_local_greedy}
done


exit 0
