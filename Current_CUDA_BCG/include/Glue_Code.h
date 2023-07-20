#pragma once
#include <Strategy.h>
#include <Population.h>

/// @brief strategize converts a population into an array of strategies.
/// @param populuation that contains individuals/strategies.
/// @return an array of strategies.
Strategy* strategize(Population population);

/// @brief popularize converts an array of strategies into a population.
/// @param an array of strategies.
/// @return a population.
Population popularize(Strategy strategies[]);

// Testing