/*
Prabhleen Kaur, Nicholas Tamburri
MSCS588 Intro to GPU Programming
15 November 2018
Assignment 2 - Evolver GPU alpha
*/

/*
tid        pl     hands      wins       bjs  charlies     loses    breaks      dbjs    pushes
0    0.035437      1030       408        49         0       285       156        34        98
1   -0.006737      1039       400        50         0       279       177        45        88
2    0.014947      1037       424        47         0       287       174        32        73
3   -0.008252      1030       406        43         0       270       187        32        92
4    0.004873      1026       410        48         0       282       162        28        96
5   -0.004892      1022       392        56         0       290       177        29        78
6    0.100681      1028       433        57         0       282       141        30        85
7    0.001934      1034       404        44         0       294       180        28        84
8   -0.020039      1023       387        53         0       298       168        22        95
9   -0.030732      1025       396        39         0       277       198        40        75

tid   total     nones     stays      hits   doubles    splits
0      1462         0       760       570       102        30
1      1476         0       749       585       103        39
2      1485         0       744       601       103        37
3      1504         0       735       643        96        30
4      1454         0       751       574       103        26
5      1450         0       716       593       119        22
6      1451         0       758       548       117        28
7      1477         0       752       595        96        34
8      1500         0       752       626        99        23
9      1452         0       717       612        98        25

*/
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "Strategy.h"
#include "GA.h"
#include "Game.h"
#include "Kpax.h"
#include "Helpers.h"
#include "Population.h"

void randomize(Population* pop);
void zero(Population* pop);
void average(Population* pop, Game* statistics);
void mutate(Population* pop);
double getDiversity(Population* pop);

#define NUM_BLOCKS 2
#define NUM_THREADS_PER_BLOCK 5
#define NUM_THREADS_TOTAL (NUM_BLOCKS * NUM_THREADS_PER_BLOCK)
#define NUM_STRATEGIES NUM_THREADS_TOTAL 
#define NUM_GAMES 3700  // See https://docs.microsoft.com/en-us/windows-hardware/drivers/display/tdr-registry-keys
#define MAX_GENERATIONS 1 //100

void Evolver10_3700(void) {
	void evolver(int maxGenerations);
	evolver(MAX_GENERATIONS);
}

void evolver(int maxGenerations) {
	const float delta = 0.25;
	const double DIVERSITY_THRESHOLD = delta * NUMBER_RULES;

	Population curPop = Population_();

	// This randomize function is closer to the one in the assignment
	// description in that it takes a Strategy* as an argument,
	// but this way all the individuals have the same rules.
	//void randomize(Strategy* strategy);
	//for (int i = 0; i < POPULATION_SIZE; i++)
	//  randomize(&curPop.individuals[i]);

	// This randomize function is different from the one in the assignment
	// description in that it takes a Population* as an argument,
	// but allows all individuals to have different rules.
	randomize(&curPop);


	// Print header for per-generation output
	printf("\ngeneration   diversity  fittest individual #  fittest individual P&L\n");

	int gen = 0;
	Game statistics[POPULATION_SIZE];
	while (true) {
		zero(&curPop);

		int status = evaluate(NUM_BLOCKS, POPULATION_SIZE, curPop.individuals, NUM_GAMES, statistics);
		// Print to stderr if evaluate gives a non-zero return value
		if (status != 0)
			fprintf(stderr, "evaluate returned code = %d\n", status);

		average(&curPop, statistics);

		Population newPop = evolve(&curPop);

		mutate(&newPop);

		double diversity = getDiversity(&curPop);

		gen++;

		Strategy fittest = *getFittest(&curPop);

		// Find index of the fittest individual
		int index = 0;
		for (; index < POPULATION_SIZE && curPop.individuals[index].pl < fittest.pl; index++)
			;
		curPop.fittest = index;

		// Print generation's output row
		printf("%10d  %10f  %20d  %22f\n", gen, diversity, curPop.fittest, fittest.pl);

		if (diversity <= DIVERSITY_THRESHOLD || gen >= maxGenerations)
			break;

		curPop = newPop;
	}

	Strategy fittest = curPop.individuals[curPop.fittest];

	// Print current population's fittest individual
	printf("\ncurrent population%6c", ' ');
	printf("fittest individual #  fittest individual P&L\n");
	printf("%24c%20d  %22f\n\n", ' ', curPop.fittest, fittest.pl);

	// Output fittest strategy of curPop
	void outputStrategy(Strategy* strategy);
	outputStrategy(&fittest);

	printf("\n");

	printf("Evolver10_3700 \n");

	report(curPop.individuals, statistics, POPULATION_SIZE);
}

void mutate(Population* pop) {
	for (int i = 0; i < POPULATION_SIZE; i++)
		mutate(&pop->individuals[i]);
}

void randomize(Population* pop) {
	srand(0 /*time(NULL)*/);

	Play plays[] = { STAY, HIT, DOUBLE_DOWN, SPLIT };

	for (int i = 0; i < POPULATION_SIZE; i++)
		for (int j = 0; j < NUMBER_RULES; j++)
			pop->individuals[i].rules[j] = plays[random(0, 3)];
}

void zero(Population* pop) {
	for (int i = 0; i < POPULATION_SIZE; i++)
		pop->individuals[i].pl = 0.0;
}

void average(Population* pop, Game* statistics) {
	for (int i = 0; i < POPULATION_SIZE; i++)
		pop->individuals[i].pl = statistics[i].pl / statistics[i].nohands;
}

double getDiversity(Population* pop) {
	double sum = 0.0;
	for (int i = 0; i < POPULATION_SIZE; i++)
		for (int j = i + 1; j < POPULATION_SIZE; j++)
			for (int k = 0; k < NUMBER_RULES; k++)
				if (pop->individuals[i].rules[k] != pop->individuals[j].rules[k])
					sum += 1.0;
	double diversity = sum * 2 / POPULATION_SIZE / (POPULATION_SIZE - 1);

	return diversity;
}

void outputStrategy(Strategy* strategy) {
	// Print a title
	printf("fittest strategy\n\n");

	// Print the header
	printf("%6c23456789TA", ' ');

	for (int i = 0; i < NUMBER_RULES; i++) {
		// Print new line and row number at beginning and every 10 plays
		if (i % 10 == 0)
			printf("\n%5d ", i / 10);

		// Determine which letter to print
		char play = 'X';
		switch (strategy->rules[i]) {
		case HIT:
			play = 'H';
			break;
		case STAY:
			play = 'S';
			break;
		case DOUBLE_DOWN:
			play = 'D';
			break;
		case SPLIT:
			play = 'P';
			break;
		default:
			play = 'X';
			break;
		}

		printf("%c", play);
	}

	printf("\n");
}

// Alternative randomize function
//void randomize(Strategy* strategy) {
//	  srand(time(NULL));
//
//	  Play plays[] = { STAY, HIT, DOUBLE_DOWN, SPLIT };
//
//	  for (int i = 0; i < NUMBER_RULES; i++) {
//		  strategy->rules[i] = plays[random(0, 3)];
//	  }
//}
