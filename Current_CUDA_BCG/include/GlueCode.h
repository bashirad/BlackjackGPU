#pragma once

/// @brief strategize converts a population into a strategy.
/// @param populuation that contains individuals of strategies.
/// @return a strategy individual of the population one at a time.
Strategy strategize(Population populuation);

/// @brief popularize converts a strategy into a population.
/// @param strategy that will be combined into a group of individuals or population.
/// @return a population that contains the strategies.
Population popularize (Strategy strategy);

// Testing