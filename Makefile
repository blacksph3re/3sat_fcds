build:
	${CXX} main.cpp -o 3sat -O3 -fopenmp
	
sequential:
	${CC} 3sat.c -o 3sat_seq -lm
	
run:
	time (cat input/medium.in | ./3sat)
	
scalingtest:
	sh ./scalingtest.sh
