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
	\brief Tests the instantiation of two populations.
	\Test for Uniformity: Create two parent strategies with identical rules. 
	\Use the cross function to generate multiple child strategies. 
	\Verify that all the generated child strategies have the same rules as the parents
*/
void Test06_GA_Cross_Uniformity(void) {

	Strategy strategy1 = BasicStrategy_();
	Strategy strategy2 = BasicStrategy_();

	Strategy child1 = cross(&strategy1, &strategy2);
	Strategy child2 = cross(&strategy1, &strategy2);
	Strategy child3 = cross(&strategy1, &strategy2);
	Strategy child4 = cross(&strategy1, &strategy2);
	Strategy child5 = cross(&strategy1, &strategy2);
	Strategy child6 = cross(&strategy1, &strategy2);

	bool status = false;

	int result1 = compareStrategyRules(&strategy1, &child1);
	int result2 = compareStrategyRules(&child1, &child2);
	int result3 = compareStrategyRules(&child3, &child4);
	int result4 = compareStrategyRules(&child5, &child6);

	if (result1 == result2 == result3 == result4) {
		status = true;
		printf("TEST PASSED! Test06_GA_Cross_Uniformity.\n");
	}
	else {
		printf("TEST FAILED! Test06_GA_Cross_Uniformity.\n");

	}	
}