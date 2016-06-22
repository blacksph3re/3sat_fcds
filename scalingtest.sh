#!/bin/sh

for i in 1 2 3 4 5 6 7 8 
do
	echo "------------"
	echo "Number of threads = $i"
	export OMP_NUM_THREADS=$i
	time (cat input/large_unsolvable.in | ./3sat)
done
