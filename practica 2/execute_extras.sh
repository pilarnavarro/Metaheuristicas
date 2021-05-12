#!/bin/bash
input="data"
bin="bin"
out_agg1="salida/AGGPos-bestcross.csv"
out_agg2="salida/AGGUnif-2.csv"
out_agg3="salida/AGGPos-ternary.csv"
out_age2="salida/AGEPos-ternary.csv"
out_am2="salida/AM2-2.csv"
out_am3="salida/AM3-peores.csv"
semilla=7413

touch ${out_agg1}
rm ${out_agg1}
touch ${out_agg1}

touch ${out_agg2}
rm ${out_agg2}
touch ${out_agg2}

touch ${out_agg3}
rm ${out_agg3}
touch ${out_agg3}

touch ${out_age2}
rm ${out_age2}
touch ${out_age2}

touch ${out_am3}
rm ${out_am3}
touch ${out_am3}

touch ${out_am2}
rm ${out_am2}
touch ${out_am2}


for i in {1..10}
do
  echo "Ejecutando AGG_Posicion_bestcross para MDG-a_$i"
  ${bin}/AGGPos-bestcross ${semilla} < ${input}/MDG-a_${i}_* >> ${out_agg1}
  echo "Ejecutando AGG_Uniforme para MDG-a_$i"
  ${bin}/AGGUnif-2 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_agg2}
  echo "Ejecutando AGG_Posicion Competición ternaria para MDG-a_$i"
  ${bin}/AGGPos-ternary ${semilla} < ${input}/MDG-a_${i}_* >> ${out_agg3}
  echo "Ejecutando AGE_Posicion Competición ternaria para MDG-a_$i"
  ${bin}/AGEPos-ternary ${semilla} < ${input}/MDG-a_${i}_* >> ${out_age2}
  echo "Ejecutando AM_0.1 para MDG-a_$i"
  ${bin}/AM2-2 ${semilla} < ${input}/MDG-a_${i}_* >> ${out_am2}
  echo "Ejecutando AM_0.1_peores para MDG-a_$i"
  ${bin}/AM3-peores ${semilla} < ${input}/MDG-a_${i}_* >> ${out_am3}
done

for i in {21..30}
do
  echo "Ejecutando AGG_Posicion_bestcross para MDG-b_$i"
  ${bin}/AGGPos-bestcross ${semilla} < ${input}/MDG-b_${i}_* >> ${out_agg1}
  echo "Ejecutando AGG_Uniforme para MDG-b_$i"
  ${bin}/AGGUnif-2 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_agg2}
  echo "Ejecutando AGG_Posicion Competición ternaria para MDG-b_$i"
  ${bin}/AGGPos-ternary ${semilla} < ${input}/MDG-b_${i}_* >> ${out_agg3}
  echo "Ejecutando AGE_Posicion Competición ternaria para MDG-b_$i"
  ${bin}/AGEPos-ternary ${semilla} < ${input}/MDG-b_${i}_* >> ${out_age2}
  echo "Ejecutando AM_0.1 para MDG-b_$i"
  ${bin}/AM2-2 ${semilla} < ${input}/MDG-b_${i}_* >> ${out_am2}
  echo "Ejecutando AM_0.1_peores para MDG-b_$i"
  ${bin}/AM3-peores ${semilla} < ${input}/MDG-b_${i}_* >> ${out_am3}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
  echo "Ejecutando AGG_Posicion_bestcross para MDG-c_$i"
  ${bin}/AGGPos-bestcross ${semilla} < ${input}/MDG-c_${i}_* >> ${out_agg1}
  echo "Ejecutando AGG_Uniforme para MDG-c_$i"
  ${bin}/AGGUnif-2 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_agg2}
  echo "Ejecutando AGG_Posicion Competición ternaria para MDG-c_$i"
  ${bin}/AGGPos-ternary ${semilla} < ${input}/MDG-c_${i}_* >> ${out_agg3}
  echo "Ejecutando AGE_Posicion Competición ternaria para MDG-c_$i"
  ${bin}/AGEPos-ternary ${semilla} < ${input}/MDG-c_${i}_* >> ${out_age2}
  echo "Ejecutando AM_0.1 para MDG-c_$i"
  ${bin}/AM2-2 ${semilla} < ${input}/MDG-c_${i}_* >> ${out_am2}
  echo "Ejecutando AM_0.1_peores para MDG-c_$i"
  ${bin}/AM3-peores ${semilla} < ${input}/MDG-c_${i}_* >> ${out_am3}
done


exit 0