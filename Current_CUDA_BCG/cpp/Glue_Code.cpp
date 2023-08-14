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

Strategy randomizeStrategy(Strategy randomized) {
    Play plays[] = { S, H, D, P };

    Strategy basicStrategy = BasicStrategy_();

    int numOfRules = sizeof(basicStrategy.rules);
    int splitBoundary = -1;
    for (int index = 0; index < numOfRules; index++) {
        Play play = basicStrategy.rules[index];
        if (play == P) {
            splitBoundary = index;
            break;
        }
    }

    // Randomly alternate genes from parent 1 and parent 2. 
    for (int index = 0; index < NUMBER_RULES; index++) {

        int lottery = -1;

        /*if (index < 10) {
            lottery = 0;
        } */
        if (index < splitBoundary) {
            // choose a random number between 0 and 1
            lottery = random(0, 2);
        } else {
            lottery = random(0, 3);
        }

        Play randomPlay = plays[lottery];

        randomized.rules[index] = randomPlay;
    }

    return randomized;
}

void merge(Strategy* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create dynamic memory for temp arrays
    Strategy* L = (Strategy*)malloc(n1 * sizeof(Strategy));
    Strategy* R = (Strategy*)malloc(n2 * sizeof(Strategy));

    // Check if memory allocation was successful
    if (L == NULL || R == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].pl >= R[j].pl) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Strategy* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Function to combine strategies into a composite strategy
Strategy combineStrategies(Strategy* strategies, int numStrategies) {
    Strategy compositeStrategy;

    // Initialize with NO_PLAY 
    compositeStrategy = Strategy_();

    for (int ruleNo = 0; ruleNo < NUMBER_RULES; ruleNo++) {
        // Count votes for each choice
        int voteCount[4] = { 0,0,0,0 }; 

        // Count the votes for each choice
        for (int strategyNo = 0; strategyNo < numStrategies; strategyNo++) {
            Play ruleChoice = strategies[strategyNo].rules[ruleNo];
            switch (ruleChoice) {
            case S:
                voteCount[0]++;
                break;
            case H:
                voteCount[1]++;
                break;
            case D:
                voteCount[2]++;
                break;
            case P:
                voteCount[3]++;
                break;
            }
        }

        // default winner is STAY
        Play winningChoice = S;
        int maxVotes = voteCount[0];

        // Determine the most voted choice
        for (int choiceNo = 1; choiceNo < 4; choiceNo++) {
            if (voteCount[choiceNo] > maxVotes) {
                maxVotes = voteCount[choiceNo];
                switch (choiceNo) {
                case 1:
                    winningChoice = H;
                    break;
                case 2:
                    winningChoice = D;
                    break;
                case 3:
                    winningChoice = P;
                    break;
                }
            }
        }

        // Set the winning choice for the composite strategy
        compositeStrategy.rules[ruleNo] = winningChoice;
    }

    return compositeStrategy;
}



