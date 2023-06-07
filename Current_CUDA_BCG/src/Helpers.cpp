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
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Strategy.h"
#include "Game.h"

void report(Strategy* strategies, Game* statistics, int numThreads) {
	printf("%3s %9s %9s %9s %9s %9s %9s %9s %9s %9s\n",
		"tid", "pl", "hands", "wins", "bjs", "charlies", "loses", "breaks", "dbjs", "pushes");

	for (int threadIdx = 0; threadIdx < numThreads; threadIdx++) {
		int n = sizeof(statistics[threadIdx].count) / sizeof(int);
		int nohands = 0;
		for (int index = 0; index < n; index++)
			nohands += statistics[threadIdx].count[index];
		double mean = statistics[threadIdx].pl / nohands;

		assert(nohands == statistics[threadIdx].nohands);

		printf("%3d %9.6f %9d %9d %9d %9d %9d %9d %9d %9d\n",
			threadIdx, mean, nohands,
			statistics[threadIdx].count[WINS],
			statistics[threadIdx].count[BLACKJACKS],
			statistics[threadIdx].count[CHARLIES],
			statistics[threadIdx].count[LOSSES],
			statistics[threadIdx].count[BUSTS],
			statistics[threadIdx].count[DEALER_BLACKJACKS],
			statistics[threadIdx].count[PUSHES]);

	}

	printf("\n");

	printf("%3s %9s %9s %9s %9s %9s %9s\n", "tid", "total", "nones", "stays", "hits", "doubles", "splits");
	for (int blk = 0; blk < numThreads; blk++) {
		int numPlays =
			strategies[blk].visits[NO_PLAY] +
			strategies[blk].visits[STAY] +
			strategies[blk].visits[HIT] +
			strategies[blk].visits[DOUBLE_DOWN] +
			strategies[blk].visits[SPLIT];

		printf("%3d %9d %9d %9d %9d %9d %9d\n",
			blk, numPlays,
			strategies[blk].visits[NO_PLAY],
			strategies[blk].visits[STAY],
			strategies[blk].visits[HIT],
			strategies[blk].visits[DOUBLE_DOWN],
			strategies[blk].visits[SPLIT]
		);
	}
}

cudaError_t check(cudaError_t status, const char msg[]) {
	if (status != cudaSuccess) {
		fprintf(stderr, msg);
		fprintf(stderr, "\n");

		throw status;
	}

	return cudaSuccess;
}

int random(int min, int max) {
	/*
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
	*/
	/*
	double scaled = (double)rand() / RAND_MAX;
	return (max - min + 1)*scaled + min;
	*/
	// See https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range/6852396
	return (rand() % (max + 1 - min)) + min;
}

float random() {
	float ran = rand() / (float)RAND_MAX;

	return ran;
}