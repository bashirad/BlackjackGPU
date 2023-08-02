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

/*

Play1024_10000
run this and paste results here
*/
#include <stdio.h>
#include "Strategy.h"
#include "Game.h"
#include "Kpax.h"
#include "Helpers.h"
#include "Glue_Code.h"
#include "GA.h"
#include "Population.h"

#define NUM_BLOCKS 32
#define NUM_THREADS_PER_BLOCK 32
#define NUM_THREADS_TOTAL (NUM_BLOCKS * NUM_THREADS_PER_BLOCK)
#define NUM_STRATEGIES NUM_THREADS_TOTAL
#define NUM_GAMES 10000
#define MAX_SAME_COUNT 100
#define MAX_GENERATION_COUNT 1000



void engine(void) {

    // Declarations and initializations 
    Strategy strategies[NUM_STRATEGIES];
    for (int index = 0; index < NUM_STRATEGIES; index++) {
        strategies[index] = randomizeStrategy(Strategy_());
    }

    Population oldPopulation;
    Population newPopulation;

    Game statistics[NUM_STRATEGIES];

    int status = -1; 
    Strategy bestElite = Strategy_();
    bestElite.pl = -999;
    int count = 0;
    double meanPl = -1;

    for (int generation = 0; generation < MAX_GENERATION_COUNT; generation++) {

        for (int index = 0; index < NUM_STRATEGIES; index++) {
            statistics[index] = Game_();
        }

        int status = evaluate(NUM_BLOCKS, NUM_STRATEGIES, strategies, NUM_GAMES, statistics, generation);

        // report at the end of each cycle
        if (status != 0) 
            fprintf(stderr, "evaluate returned code = %d\n", status);

        // loop to copy pl from statistics to strategies 
        for (int individualIndex = 0; individualIndex < POPULATION_SIZE; individualIndex++) {
            strategies[individualIndex].pl = getReturn(&statistics[individualIndex]);
        }

        meanPl = getMean(NUM_STRATEGIES, strategies);
        printf("Running generation %d and the mean P&L is %f\n", generation, meanPl);


        popularize(&oldPopulation, strategies);
        int fittestIndex = oldPopulation.fittest;
        Strategy elite = oldPopulation.individuals[fittestIndex];

        if (elite.pl > bestElite.pl) {
            count = 0;
            bestElite = elite;
        }
        else
            count++;

        // Convergence criteria:
        // elitist's pl does not continually drop after 10 cycles and the elite
        if (count >= MAX_SAME_COUNT)
            break;

        // We know what the fittest is at this point
        newPopulation = evolve(&oldPopulation);     
        strategize(&newPopulation, strategies);
    }

    // how did the loop end : did coverge or cycles done?
    if (count < MAX_SAME_COUNT) {
        printf("Ran out of the %d generations!\n", MAX_GENERATION_COUNT);
    }
    else {
        printf("Converged after the elitist's pl did NOT change for %d cycles!\n", MAX_SAME_COUNT);
    }
    //report(strategies, statistics, NUM_STRATEGIES);
    //printStrategy(&bestElite);
    printf("meanPL is %f", meanPl);
}