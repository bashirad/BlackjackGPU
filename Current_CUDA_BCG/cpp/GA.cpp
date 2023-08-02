#include <stdio.h>
#include "time.h" 
#include "GA.h" 
#include "Strategy.h"
#include "Population.h"
#include "Helpers.h"


Strategy cross(Strategy* parent1, Strategy* parent2) {
	// Initialize the child with "NO PLAY" rules.
	Strategy child = Strategy_();

	// Randomly alternate genes from parent 1 and parent 2. 
	for (int index = 0; index < NUMBER_RULES; index++) {
		// choose a random number between 0 and 1
		int lottery = random(0,1);

		if (lottery == 0)
			child.rules[index] = parent1->rules[index];
		else
			child.rules[index] = parent2->rules[index];
	}

	return child;
}

void mutate(Population* mutatedPopulation) {

	for (int index = 0; index < POPULATION_SIZE; index++) {
		Strategy result = mutate(&mutatedPopulation->individuals[index], MUTATION_RATE);

	}
}

Strategy mutate(Strategy* strategy) {
	Strategy result = mutate(strategy, MUTATION_RATE);
	return result;
}

Strategy mutate(Strategy* individual, float rate) {
	Strategy child = *individual;

	// We'll draw from this array randomly
	Play plays[] = { STAY, HIT, DOUBLE_DOWN, SPLIT };

	int numPlays = sizeof(plays) / sizeof(int);

	// Randomly mutate the play if probability is below mutation rate
	for (int index = 0; index < NUMBER_RULES; index++) {
		float lottery = random();

		if (lottery > rate)
			continue;

		int ran = random(0, numPlays - 1);

		Play allele = plays[ran];

		child.rules[index] = allele;
	}

	return child;
}

Strategy* tournamentSelect(Population* population) {
	// This array holds pointers to strategies from the population
	Strategy* tournament[TOURNAMENT_SIZE];

	// Select at random n individuals to be in the tournament
	for (int index = 0; index < TOURNAMENT_SIZE; index++) {
		// Get the individual index as a lottery
		int lottery = random(0, POPULATION_SIZE-1);

		// Include a pointer to this individual in the tournament.
		tournament[index] = &population->individuals[lottery];
	}

	// Play the tournament
	Strategy* winner = getFittest(tournament);

	return winner;
}

Strategy* getFittest(Strategy** individuals) {
	Strategy* fittest = individuals[0];

	for (int index = 1; index < TOURNAMENT_SIZE; index++) {
		if (individuals[index]->pl > fittest->pl)
			fittest = individuals[index];
	}

	return fittest;
}

Strategy* getFittest(Population* population) {
	Strategy* fittest = &population->individuals[0];

	for (int index = 1; index < population->size; index++)
		if (population->individuals[index].pl > fittest->pl)
			fittest = &population->individuals[index];

	return fittest;
}

Population evolve(Population* oldPopulation) {
	// Initialize the new population -- all individuals have "NO PLAY" strategies. 
	Population newPopulation = Population_();

	// If elitist, always include the fittest individual in the population.
	if (ELITIST)
		newPopulation.individuals[0] = *getFittest(oldPopulation);

	// Run 2X population size tournaments to build the next generation.
	for (int index = ELITIST ? 1 : 0; index < POPULATION_SIZE; index++) {
		// Find two parents through a pair of tournaments
		Strategy* parent1 = tournamentSelect(oldPopulation);

		Strategy* parent2 = tournamentSelect(oldPopulation);

		// Get a child from these parents
		Strategy child = cross(parent1, parent2);

		// Add this child to the new population
		newPopulation.individuals[index] = child;
	}

	mutate(&newPopulation);

	return newPopulation;
}