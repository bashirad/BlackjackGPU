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

#include <stdio.h>
#include "Strategy.h"

#include "Helpers.h"

#define NUM_THREADS_PER_BLOCK 5
#define NUM_THREADS_TOTAL (NUM_THREADS_PER_BLOCK * 1)
#define NUM_STRATEGIES NUM_THREADS_TOTAL
#define NUM_GAMES 1000

#include "GA.h"

/*!
	\brief Tests the isIdentical() and countStrategyDiffs() functions.
	\Test for Uniformity: Create one strategy. 
	\Use isIdentical function to check the one strategy against itself. 
	\Verify the one strategy is equal to itself.
*/
void isIdentical(void) {

	// Test for bugs in isIdentical
	Strategy strategy1 = BasicStrategy_();

	bool same = isIdentical(&strategy1, &strategy1);

	if (same) {
		printf("isIdentical\n");
		printf("TEST PASSED!\n");
	}
	else {
		printf("isIdentical\n");
		printf("TEST FAILED!\n");
	}
}