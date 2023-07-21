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

#define NUM_BLOCKS 32
#define NUM_THREADS_PER_BLOCK 32
#define NUM_THREADS_TOTAL (NUM_BLOCKS * NUM_THREADS_PER_BLOCK)
#define NUM_STRATEGIES NUM_THREADS_TOTAL
#define NUM_GAMES 10

void Engine(void) {
    Strategy strategies[NUM_STRATEGIES];

    for (int index = 0; index < NUM_STRATEGIES; index++) {
        strategies[index] = BasicStrategy_();
    }

    // Declare a Population
    Population oldPopulation;
    Population newPopulation;

    Game statistics[NUM_STRATEGIES];
    for (int index = 0; index < NUM_STRATEGIES; index++) {
        statistics[index] = Game_();
    }

    // loop to implement cycles using the GPU and the Genetic Algorithm
    int status; 

    for (int index = 0; index < 1; index++) {


        int status = evaluate(NUM_BLOCKS, NUM_STRATEGIES, strategies, NUM_GAMES, statistics);

        popularize(&oldPopulation, strategies);

        newPopulation = 
            evolve(&oldPopulation);
      
        strategize(&newPopulation, strategies);


        // report at the end of each cycle
        if (status == 0) {
            printf("Play10000_On_1024\n");
            report(strategies, statistics, NUM_STRATEGIES);
        }
        else
            fprintf(stderr, "evaluate returned code = %d\n", status);
    }


}