/*
Copyright (c) Bashir Dahir
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
#include "stdio.h"
#include "Glue_Code.h"
#include "Strategy.h"
#include "Population.h"
#include "GA.h"
#include "Helpers.h"
#include "Game.h"

void strategize(Population* population, Strategy* strategies) {
    for (int index = 0; index < POPULATION_SIZE; index++) {
        strategies[index] = population->individuals[index];
    }
}

void popularize(Population* population, Strategy* strategies) {

    // default index 0 for fittest individual in the population 
    population->fittest = 0;
    population->size = POPULATION_SIZE;
      
    int fittest = 0;

    int fittestPL = population->individuals[fittest].pl;

    for (int index = 0; index < POPULATION_SIZE; index++) {
        population->individuals[index] = strategies[index];

        // update fittest strategy if one is found
        if (strategies[index].pl >= strategies[fittest].pl)
            fittest = index;
    }

    population->fittest = fittest;
}

double getReturn(Game* statistics) {

    int n = sizeof(statistics->count) / sizeof(int);
    int nohands = 0;
    for (int index = 0; index < n; index++)
        nohands += statistics->count[index];
    double mean = statistics->pl / nohands;

    return mean;
}

double getMean(int n, Strategy* strategies) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += strategies[i].pl;
    }

    double mean = sum / n;

    return mean;
}

Strategy randomizeStrategy(Strategy strategy) {

    Strategy randomized = strategy;

    // Randomly alternate genes from parent 1 and parent 2. 
    for (int index = 0; index < NUMBER_RULES; index++) {
        // choose a random number between 0 and 1
        int lottery = random(1, 4);

        // lottery is working because of the line below
        //printf("lottery is %d\n", lottery);

        if (lottery == 1)
            randomized.rules[index] = S;
        else if (lottery == 2)
            randomized.rules[index] = H;
        else if (lottery == 3)
            randomized.rules[index] = D;
        else if (lottery == 4)
            randomized.rules[index] = P;
    }

    return randomized;
}