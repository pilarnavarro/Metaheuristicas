#!/bin/bash
input="data"
bin="bin"
out_am1="salida/AM1.csv"
out_am2="salida/AM2.csv"
out_am3="salida/AM3.csv"
semilla=7413

touch ${out_am1}
rm ${out_am1}
touch ${out_am1}

touch ${out_am2}
rm ${out_am2}
touch ${out_am2}

touch ${out_am3}
rm ${out_am3}
touch ${out_am3}

for i in {1..10}
do
  echo "Ejecutando AM_1 para MDG-a_$i"
  ${bin}/AM1 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_am1}
  echo "Ejecutando AM_01 para MDG-a_$i"
  ${bin}/AM2 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_am2}
  echo "Ejecutando AM_01_mejores para MDG-a_$i"
  ${bin}/AM3 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_am3}
done

for i in {21..30}
do
  echo "Ejecutando AM_1 para MDG-b_$i"
  ${bin}/AM1 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_am1}
  echo "Ejecutando AM_01 para MDG-b_$i"
  ${bin}/AM2 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_am2}
  echo "Ejecutando AM_01_mejores para MDG-b_$i"
  ${bin}/AM3 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_am3}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
  echo "Ejecutando AM_1 para MDG-c_$i"
  ${bin}/AM1 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_am1}
  echo "Ejecutando AM_01 para MDG-c_$i"
  ${bin}/AM2 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_am2}
  echo "Ejecutando AM_01_mejores para MDG-c_$i"
  ${bin}/AM3 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_am3}
done


exit 0