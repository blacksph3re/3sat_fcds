build:
	${CXX} main.cpp -o 3sat -O3 -fopenmp -std=c++11
	
sequential:
	${CC} 3sat.c -o 3sat_seq -lm -O3
	
run:
	time ./3sat < input/medium.in
	
scalingtest:
	sh ./scalingtest.sh

inputmed:
	python inputer.py -n 30 -l 30 > input/medium.in 

inputlarge:
	python inputer_unsolvable.py -n 250 -l 30 > input/large_unsolvable.in
	
