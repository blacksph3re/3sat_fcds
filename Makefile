build:
	${CXX} main.cpp -o 3sat -O3 -fopenmp -std=c++11
	
sequential:
	${CC} 3sat.c -o 3sat_seq -lm
	
run:
	cat input/medium.in | time ./3sat
	
scalingtest:
	sh ./scalingtest.sh
