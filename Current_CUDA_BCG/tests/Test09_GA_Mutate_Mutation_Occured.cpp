/*
Copyright (c) Ron Coleman and Bashir Dahir
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
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "Strategy.h"
#include "Helpers.h"
#include "GA.h"

#define NUM_THREADS_PER_BLOCK 5
#define NUM_THREADS_TOTAL (NUM_THREADS_PER_BLOCK * 1)
#define NUM_STRATEGIES NUM_THREADS_TOTAL
#define NUM_GAMES 1000


/*!
 \ 3. Test for Randomness: Create two parent strategies with different rules.
 \    Use the cross function to generate multiple child strategies.
 \    Print the rules of each child strategy and observe if there is a random alternation of
 \	  genes from both parents.
 \    Analyze the distribution of inherited rules across the child strategies.
*/

void Test09_GA_Mutate_Mutation_Occured(void) {

	Strategy strategy1 = BasicStrategy_();
	Strategy strategy2 = BasicStrategy_();

	srand(0);
	
	mutate(&strategy1);

	bool result = isIdentical(&strategy1, &strategy2);

	
	
	if (result) {		// mutation occured when the two strategies have one or more different rules
		printf("TEST PASSED! Test09_GA_Mutate. Pass = %s\n", result ? "TRUE" : "FALSE");
	}
	else {
		printf("TEST FAILED! Test09_GA_Mutate. Pass = %s\n", result ? "TRUE" : "FALSE");
	}


}