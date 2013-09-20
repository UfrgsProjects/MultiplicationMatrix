#!/bin/bash

for ((k=1; $k < 5; k++)) do
for (( i=1; $i < 21; i++ )) ; do 
		./matrix_thread $k
		cat tempo.txt >> $(echo "$k.txt")
done
done
