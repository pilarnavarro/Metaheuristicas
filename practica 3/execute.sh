#!/bin/bash
input="data"
bin="bin"
out_local="salida/localSearch.csv"
out_greedy="salida/greedy.csv"
out_ES="salida/ES.csv"
out_ES2="salida/ES2.csv"
out_ES3="salida/ES3.csv"
out_ES4="salida/ES-Prop.csv"
out_BMB="salida/BMB.csv"
out_ILS="salida/ILS.csv"
out_ILS2="salida/ILS_ES.csv"
out_ILS3="salida/ILS2.csv"
out_ILS4="salida/ILS_ES_Prop.csv"
semilla=7413

touch ${out_greedy}
rm ${out_greedy}
touch ${out_greedy}

touch ${out_local}
rm ${out_local}
touch ${out_local}

touch ${out_ES}
rm ${out_ES}
touch ${out_ES}

touch ${out_ES2}
rm ${out_ES2}
touch ${out_ES2}

touch ${out_ES3}
rm ${out_ES3}
touch ${out_ES3}

touch ${out_ES4}
rm ${out_ES4}
touch ${out_ES4}

touch ${out_BMB}
rm ${out_BMB}
touch ${out_BMB}

touch ${out_ILS}
rm ${out_ILS}
touch ${out_ILS}

touch ${out_ILS2}
rm ${out_ILS2}
touch ${out_ILS2}

touch ${out_ILS3}
rm ${out_ILS3}
touch ${out_ILS3}

touch ${out_ILS4}
rm ${out_ILS4}
touch ${out_ILS4}

for i in {1..10}
do
  echo "Ejecutando greedy para MDG-a_$i"
  ${bin}/greedy < ${input}/MDG-a_${i}_* >> ${out_greedy}
  echo "Ejecutando búsqueda local del primer mejor para MDG-a_$i"
  ${bin}/localSearch ${semilla} < ${input}/MDG-a_${i}_* >> ${out_local}
  echo "Ejecutando enfriamiento simulado para MDG-a_$i"
  ${bin}/ES ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ES}
  echo "Ejecutando enfriamiento simulado versión 2 para MDG-a_$i"
  ${bin}/ES2 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ES2}
  echo "Ejecutando enfriamiento simulado versión 3 para MDG-a_$i"
  ${bin}/ES3 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ES3}
  echo "Ejecutando enfriamiento simulado con enfriamiento proporcional para MDG-a_$i"
  ${bin}/ES-Prop ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ES4}
  echo "Ejecutando búsqueda multiarranque para MDG-a_$i"
  ${bin}/BMB ${semilla} < ${input}/MDG-a_${i}_* >> ${out_BMB}
  echo "Ejecutando búsqueda local iterativa para MDG-a_$i"
  ${bin}/ILS ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ILS}
  echo "Ejecutando búsqueda local iterativa versión 2 para MDG-a_$i"
  ${bin}/ILS2 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ILS3}
  echo "Ejecutando búsqueda local iterativa con ES para MDG-a_$i"
  ${bin}/ILS-ES ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ILS2}
  echo "Ejecutando búsqueda local iterativa con ES proporcional para MDG-a_$i"
  ${bin}/ILS-ES-Prop ${semilla} < ${input}/MDG-a_${i}_* >> ${out_ILS4}
done

for i in {21..30}
do
  echo "Ejecutando greedy para MDG-b_$i"
  ${bin}/greedy < ${input}/MDG-b_${i}_* >> ${out_greedy}
  echo "Ejecutando búsqueda local del primer mejor para MDG-b_$i"
  ${bin}/localSearch ${semilla} < ${input}/MDG-b_${i}_* >> ${out_local}
  echo "Ejecutando enfriamiento simulado para MDG-b_$i"
  ${bin}/ES ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ES}
  echo "Ejecutando enfriamiento simulado versión 2 para MDG-b_$i"
  ${bin}/ES2 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ES2}
  echo "Ejecutando enfriamiento simulado versión 3 para MDG-b_$i"
  ${bin}/ES3 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ES3}
  echo "Ejecutando enfriamiento simulado con enfriamiento proporcional para MDG-b_$i"
  ${bin}/ES-Prop ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ES4}
  echo "Ejecutando búsqueda multiarranque para MDG-b_$i"
  ${bin}/BMB ${semilla} < ${input}/MDG-b_${i}_* >> ${out_BMB}
  echo "Ejecutando búsqueda local iterativa para MDG-b_$i"
  ${bin}/ILS ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ILS}
  echo "Ejecutando búsqueda local iterativa versión 2 para MDG-b_$i"
  ${bin}/ILS2 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ILS3}
  echo "Ejecutando búsqueda local iterativa con ES para MDG-b_$i"
  ${bin}/ILS-ES ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ILS2}
  echo "Ejecutando búsqueda local iterativa con ES proporcional para MDG-b_$i"
  ${bin}/ILS-ES-Prop ${semilla} < ${input}/MDG-b_${i}_* >> ${out_ILS4}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
  echo "Ejecutando greedy para MDG-c_$i"
  ${bin}/greedy < ${input}/MDG-c_${i}_* >> ${out_greedy}
  echo "Ejecutando búsqueda local del primer mejor para MDG-c_$i"
  ${bin}/localSearch ${semilla} < ${input}/MDG-c_${i}_* >> ${out_local}
  echo "Ejecutando enfriamiento simulado para MDG-c_$i"
  ${bin}/ES ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ES}
  echo "Ejecutando enfriamiento simulado versión 2 para MDG-c_$i"
  ${bin}/ES2 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ES2}
  echo "Ejecutando enfriamiento simulado versión 3 para MDG-c_$i"
  ${bin}/ES3 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ES3}
  echo "Ejecutando enfriamiento simulado con enfriamiento proporcional para MDG-c_$i"
  ${bin}/ES-Prop ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ES4}
  echo "Ejecutando búsqueda multiarranque para MDG-c_$i"
  ${bin}/BMB ${semilla} < ${input}/MDG-c_${i}_* >> ${out_BMB}
  echo "Ejecutando búsqueda local iterativa para MDG-c_$i"
  ${bin}/ILS ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ILS}
  echo "Ejecutando búsqueda local iterativa versión 2 para MDG-c_$i"
  ${bin}/ILS2 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ILS3}
  echo "Ejecutando búsqueda local iterativa con ES para MDG-c_$i"
  ${bin}/ILS-ES ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ILS2}
  echo "Ejecutando búsqueda local iterativa con ES proporcional para MDG-c_$i"
  ${bin}/ILS-ES-Prop ${semilla} < ${input}/MDG-c_${i}_* >> ${out_ILS4}
done


exit 0
