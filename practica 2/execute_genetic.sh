#!/bin/bash
input="data"
bin="bin"
out_agg1="salida/AGGPos.csv"
out_agg2="salida/AGGUnif.csv"
out_age1="salida/AGEPos.csv"
out_age2="salida/AGEUnif.csv"
semilla=7413

touch ${out_agg1}
rm ${out_agg1}
touch ${out_agg1}

touch ${out_agg2}
rm ${out_agg2}
touch ${out_agg2}

touch ${out_age1}
rm ${out_age1}
touch ${out_age1}

touch ${out_age2}
rm ${out_age2}
touch ${out_age2}


for i in {1..10}
do
  echo "Ejecutando AGG_Posicion para MDG-a_$i"
  ${bin}/AGGPos ${semilla} < ${input}/MDG-a_${i}_* >> ${out_agg1}
  echo "Ejecutando AGG_Uniforme para MDG-a_$i"
  ${bin}/AGGUnif ${semilla} < ${input}/MDG-a_${i}_* >> ${out_agg2}
  echo "Ejecutando AGE_Posicion para MDG-a_$i"
  ${bin}/AGEPos ${semilla} < ${input}/MDG-a_${i}_* >> ${out_age1}
  echo "Ejecutando AGE_Uniforme para MDG-a_$i"
  ${bin}/AGEUnif ${semilla} < ${input}/MDG-a_${i}_* >> ${out_age2}
done

for i in {21..30}
do
  echo "Ejecutando AGG_Posicion para MDG-b_$i"
  ${bin}/AGGPos ${semilla} < ${input}/MDG-b_${i}_* >> ${out_agg1}
  echo "Ejecutando AGG_Uniforme para MDG-b_$i"
  ${bin}/AGGUnif ${semilla} < ${input}/MDG-b_${i}_* >> ${out_agg2}
  echo "Ejecutando AGE_Posicion para MDG-b_$i"
  ${bin}/AGEPos ${semilla} < ${input}/MDG-b_${i}_* >> ${out_age1}
  echo "Ejecutando AGE_Uniforme para MDG-b_$i"
  ${bin}/AGEUnif ${semilla} < ${input}/MDG-b_${i}_* >> ${out_age2}
done

for i in {1,2,8,9,10,13,14,15,19,20}
do
  echo "Ejecutando AGG_Posicion para MDG-c_$i"
  ${bin}/AGGPos ${semilla} < ${input}/MDG-c_${i}_* >> ${out_agg1}
  echo "Ejecutando AGG_Uniforme para MDG-c_$i"
  ${bin}/AGGUnif ${semilla} < ${input}/MDG-c_${i}_* >> ${out_agg2}
  echo "Ejecutando AGE_Posicion para MDG-c_$i"
  ${bin}/AGEPos ${semilla} < ${input}/MDG-c_${i}_* >> ${out_age1}
  echo "Ejecutando AGE_Uniforme para MDG-c_$i"
  ${bin}/AGEUnif ${semilla} < ${input}/MDG-c_${i}_* >> ${out_age2}
done


exit 0