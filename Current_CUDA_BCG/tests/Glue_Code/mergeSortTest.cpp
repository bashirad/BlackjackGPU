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
#include "GA.h"
#include "Glue_Code.h"

/*!
	\brief Tests the isIdentical() and cross() functions.
	\Use cross function to cross the one strategy against itself.
	\Use isIdentical function to check the one strategy against itself.
	\Verify the child strategy is identical to the two identical parents
*/
void mergeSortTest(void) {

	int arr[] = { 12, 11, 13, 5, 6, 7 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, arr_size);
	

	mergeSort(arr, 0, arr_size - 1);

	printf("\nSorted array is \n");
	printArray(arr, arr_size);

	/*// check if the new population has the same size
	bool check = false;

	printf("Population size is %d", population.size);

	if (population.size == 5) {
		check = true;
	}

	if (check) {
		printf("popularizeTest\n");
		printf("TEST PASSED!\n");
	}
	else {
		printf("popularizeTest\n");
		printf("TEST FAILED!\n");
	}*/
}
