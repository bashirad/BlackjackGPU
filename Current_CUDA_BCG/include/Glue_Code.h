#pragma once
#include <Strategy.h>
#include <Population.h>
#include <Game.h>

/// @brief strategize converts a population into an array of strategies.
/// @param populuation that contains individuals/strategies.
/// @return an array of strategies.
void strategize(Population* population, Strategy* strategies);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
void popularize(Population* population, Strategy* strategies);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
double getReturn(Game* statistics);

double getMean(int n, Strategy* strategies);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
Strategy randomizeStrategy(Strategy strategy);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
void merge(Strategy* arr, int l, int m, int r);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
void mergeSort(Strategy* arr, int l, int r);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
void printSortedStrategies(Strategy* arr, int size);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
Strategy combineStrategies(Strategy* strategies, int numStrategies);