/*
Copyright (c) Ron Coleman
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "Population.h"

/*! 
  \def Mutation rate as a probability 
*/
//#define MUTATION_RATE 2.000 -- FOR TESTING, YOU CAN INCREASE THE CHANCE OF MUTATION OR DECREASE 
#define MUTATION_RATE 0.015

/*! 
  \def Size of tournament 
*/
#define TOURNAMENT_SIZE 5


/*!
  \brief Mates two parent strategies.
  \param a Parent
  \param b Parent
  \return Child strategy
*/
Strategy cross(Strategy* a, Strategy* b);

/*!
  \brief Randomly mutates an individual strategy
  \param individual Strategy
*/
Strategy mutate(Strategy* individual);
Strategy mutate(Strategy* individual, float rate);
void mutate(Population* mutatedPopulation);

/*!
  \brief Plays tournament among the population.
  \param population Population
  \return Winning individual strategy pointer
*/
Strategy* tournamentSelect(Population* population);

/*!
  \brief Gets fittest strategy among individuals.
  \param individuals Strategies
  \return Fittest strategy pointer
*/
Strategy* getFittest(Strategy** individuals);

/*!
  \brief Gets fittest strategy among population.
  \param population Population
  \return Fittest strategy pointer
*/
Strategy* getFittest(Population* population);

/*!
  \brief Evolves a population using natural selection.
  \todo Function needs to apply the mutate operation.
  \param population Old population from prior generation
  \return New population of next generation
*/
Population evolve(Population* population);

