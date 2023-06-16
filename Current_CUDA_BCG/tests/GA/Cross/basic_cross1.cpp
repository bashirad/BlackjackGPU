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
#include "Strategy.h"

#include "Helpers.h"

#define NUM_THREADS_PER_BLOCK 5
#define NUM_THREADS_TOTAL (NUM_THREADS_PER_BLOCK * 1)
#define NUM_STRATEGIES NUM_THREADS_TOTAL
#define NUM_GAMES 1000

#include "GA.h"

/*!
 \ 3. Test for Randomness: Create two parent strategies with different rules.
 \    Use the cross function to generate multiple child strategies.
 \    Print the rules of each child strategy and observe if there is a random alternation of
 \	  genes from both parents.
 \    Analyze the distribution of inherited rules across the child strategies.
*/

void basic_cross1(void) {

	bool status = false;

	Strategy strategy1 = CustomStrategy2_();
	Strategy strategy2 = BasicStrategy_();

	srand(0);

	Strategy child1 = cross(&strategy1, &strategy1); 

	///////////////////////

	Strategy child2 = cross(&strategy1, &strategy2);
	Strategy child3 = cross(&strategy1, &strategy2);
	Strategy child4 = cross(&strategy1, &strategy2); 
	Strategy child5 = cross(&strategy1, &strategy2);
	Strategy child6 = cross(&strategy1, &strategy2);

	bool result1 = isIdentical(&child1, &child2);
	bool result2 = isIdentical(&child3, &child4);
	bool result3 = isIdentical(&child5, &child6);

	if (result1 == true && result1 == result2 && result1 == result3 && result2 == result3) {
		printf("TEST PASSED! Test08_GA_Cross_Randomness. Pass = %s\n", result1 ? "TRUE" : "FALSE");
	}
	else {
		printf("TEST FAILED! Test08_GA_Cross_Randomness. Pass = %s\n", result1 ? "TRUE" : "FALSE");
	}


}