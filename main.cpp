#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <atomic>

// Solves the 3-SAT system using an exaustive search
// It finds all the possible values for the set of variables using
// a number. The binary representation of this number represents 
// the values of the variables. Since a long variable has 64 bits, 
// this implementations works with problems with up to 64 variables.
long solveClauses(const short* const* clauses, const int nClauses, const int nVar) {

	const long *iVar = [](int nVar){
		long* retval = (long *) malloc(nVar * sizeof(long));
		for (int i = 0; i < nVar; i++)
			retval[i] = exp2(i);
		return retval;
	}(nVar);

	const unsigned long maxNumber = exp2(nVar);
	long result = -1;
	std::atomic<bool> running(true);

	#pragma omp parallel for
	for (long number = 0; number < maxNumber; number++) {
		
		if(running) {
			int c;
			for (c = 0; c < nClauses; c++) {

				short var = clauses[0][c];
				if (var > 0 && (number & iVar[var - 1]) > 0)
					continue; // clause is true
				else if (var < 0 && (number & iVar[-var - 1]) == 0)
					continue; // clause is true

				var = clauses[1][c];
				if (var > 0 && (number & iVar[var - 1]) > 0)
					continue; // clause is true
				else if (var < 0 && (number & iVar[-var - 1]) == 0)
					continue; // clause is true

				var = clauses[2][c];
				if (var > 0 && (number & iVar[var - 1]) > 0)
					continue; // clause is true
				else if (var < 0 && (number & iVar[-var - 1]) == 0)
					continue; // clause is true

				break; // clause is false
			}

			if (c == nClauses) {
				// No synchronization needed
				// if another thread finds another solution simultaneously, it doesn't matter which one ends up in result
				result = number;
				running = false;
			}
		} else
			number = maxNumber;
	}
	return result;

}

// Read nClauses clauses of size 3. nVar represents the number of variables
// Clause[0][i], Clause[1][i] and Clause[2][i] contains the 3 elements of the i-esime clause.
// Each element of the caluse vector may contain values selected from:
// k = -nVar, ..., -2, -1, 1, 2, ..., nVar. The value of k represents the index of the variable.
// A negative value remains the negation of the variable.
short **readClauses(int nClauses, int nVar) {

	short **clauses = (short **) malloc(3 * sizeof(short *));
	clauses[0] = (short *) malloc(nClauses * sizeof(short));
	clauses[1] = (short *) malloc(nClauses * sizeof(short));
	clauses[2] = (short *) malloc(nClauses * sizeof(short));

	int i;
	for (i = 0; i < nClauses; i++) {
		scanf("%hd %hd %hd", &clauses[0][i], &clauses[1][i], &clauses[2][i]);
	}

	return clauses;
}

int main(int argc, char *argv[]) {

	int nClauses;
	int nVar;

	scanf("%d %d", &nClauses, &nVar);

	short **clauses = readClauses(nClauses, nVar);

	long solution = solveClauses(clauses, nClauses, nVar);

	int i;
	if (solution >= 0) {
		printf("Solution found [%ld]: ", solution);
		for (i = 0; i < nVar; i++)
			printf("%d ", (int) ((solution & (long) exp2(i)) / exp2(i)));
		printf("\n");
	} else
		printf("Solution not found.\n");

	return EXIT_SUCCESS;
}

