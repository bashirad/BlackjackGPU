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

/// @brief getReturn calculates the P&L using Game statistics array.
/// @param an array of statistics.
/// @return a P&L value.
double getReturn(Game* statistics);

/// @brief getMean calculates mean P&L of all strategies.
/// @param an array of strategies.
/// @return the mean P&L.
double getMean(int n, Strategy* strategies);

/// @brief randomizeStrategy forms a semi-random Strategy by randomizing the strategy rules.
/// @param a Strategy.
/// @return Strategy with randomized rules.
Strategy randomizeStrategy(Strategy strategy);

/// @brief merge combines the two sorted arrays of strategies based on P&L value.
/// @param an array of strategies, most left index, medium index and most right index.
/// @return No return.
void merge(Strategy* arr, int l, int m, int r);

/// @brief mergeSort sorts an array of strategies based on the P&L value.
/// @param an array of strategies, most left index and most right index.
/// @return No return.
void mergeSort(Strategy* arr, int l, int r);

/// @brief combineStrategies forms a composite Strategy from an array of strategies by voting on each rule.
/// @param an array of strategies.
/// @return a composite Strategy.
Strategy combineStrategies(Strategy* strategies, int numStrategies);