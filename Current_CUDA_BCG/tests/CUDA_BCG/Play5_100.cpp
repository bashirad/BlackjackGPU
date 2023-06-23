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
Play5_100
tid        pl     hands      wins blackjack  charlies     loses     busts dealerbjs    pushes
  0 -0.004950       101        32         9         0        27        15         6        12
  1  0.148148       108        48         8         0        24        21         2         5
  2 -0.062500       104        43         1         0        29        18         4         9
  3  0.128713       101        42         6         0        20        20         1        12
  4  0.083333       102        41         9         0        28        12         1        11

tid     plays      none     stays      hits   doubles    splits
  0       146         0        78        59         8         1
  1       146         0        74        51        13         8
  2       154         0        75        68         7         4
  3       144         0        71        64         8         1
  4       138         0        74        48        14         2
*/

#include <stdio.h>
#include "Strategy.h"
#include "Game.h"
#include "Kpax.h"
#include "Helpers.h"

#define NUM_STRATEGIES 5
#define NUM_GAMES 100

void Play5_100(void) {

	Strategy strategies[NUM_STRATEGIES];

	for (int index = 0; index < NUM_STRATEGIES; index++) {
		strategies[index] = BasicStrategy_();
	}

	Game statistics[NUM_STRATEGIES];
	for (int index = 0; index < NUM_STRATEGIES; index++) {
		statistics[index] = Game_();
	}

	int status = evaluate(NUM_STRATEGIES, strategies, NUM_GAMES, statistics);

	if (status == 0) {
		printf("Play5_100\n");
		report(strategies, statistics, NUM_STRATEGIES);
	}
	else
		fprintf(stderr, "evaluate returned code = %d\n", status);
}