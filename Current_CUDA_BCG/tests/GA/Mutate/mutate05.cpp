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
 \ 3. Test mutation at non-default rate of 0.05.
 \    Use the mutate() to generate a mutated version of the basic strategy and set rate to 0.05.
 \    Go through the rules of the mutated version and count the changes made bu mutate().
 \    Expect 0.05*430*0.75 +- (16.125+-) or between 12 and 20 changes.
*/

void mutate05(void) {

	Strategy basicStrategy = BasicStrategy_();

	Strategy mutatedStrategy = mutate(&basicStrategy, 0.05);

	int count = 0;

	// Go through the strategy rules and check for changes according to the default rate
	for (int i = 0; i < NUMBER_RULES; i++) {
		if (basicStrategy.rules[i] != mutatedStrategy.rules[i]) count++;
	}
	// mutation occured when the two strategies have one or more different rules
	if (count >= 12 && count <= 20) {
		printf("mutate05: %d changes\n", count);
		printf("TEST PASSED!\n");
	}
	else {
		printf("mutate05: %d changes\n", count);
		printf("TEST FAILED!\n");
	}

}