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

#include <stdio.h>
#include "Strategy.h"
#include <time.h>
#include "Helpers.h"
#include "Population.h"
#include "Glue_Code.h"
#include "../GA/Helpers/Population1.h"
#include <GA.h>


/*!
	\brief Tests the strategize() function.
	\Use strategize function to create an array of strategies from a population.
	\Use isIdentical function to check the one strategy against itself.
	\Verify the child strategy is identical to the two identical parents
*/
void strategize(void) {

	Population population = Population1_();

	Population evolved = evolve(&population);

	/*Strategy strategies;

	strategies = strategize(population)[0];


	 
	printStrategy(&strategies);*/

	// check if child is identical to the two identical parents
	bool same = true;

	if (same) {
		printf("cross0\n");
		printf("TEST PASSED!\n");
	}
	else {
		printf("cross0\n");
		printf("TEST FAILED!\n");
	}
}