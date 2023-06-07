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
running tests: 1
test 00:
tid        pl     hands      wins blackjack  charlies     loses     busts dealerbjs    pushes
  0  0.600000        10         7         0         0         0         3         0         0
  1  0.363636        11         5         2         0         1         1         1         1
  2  0.300000        10         6         0         0         3         0         1         0
  3 -0.100000        10         4         0         0         0         5         0         1
  4 -0.200000        10         3         2         0         3         1         1         0

tid     plays      none     stays      hits   doubles    splits
  0        16         0         5         9         2         0
  1        13         0         9         2         1         1
  2        15         0         9         5         1         0
  3        12         0         5         7         0         0
  4        11         0         6         2         3         0

*/
#include <stdio.h>
#include "Strategy.h"
#include "Game.h"
#include "Kpax.h"
#include "Helpers.h"

#define NUM_STRATEGIES 5
#define NUM_GAMES 10

void test00(void) {

	Strategy strategies[NUM_STRATEGIES];

	for (int index = 0; index < NUM_STRATEGIES; index++) {
		strategies[index] = BasicStrategy_();
	}

	Game statistics[NUM_STRATEGIES];
	for (int index = 0; index < NUM_STRATEGIES; index++) {
		statistics[index] = Game_();
	}

	int status = evaluate(NUM_STRATEGIES, strategies, NUM_GAMES, statistics);

	if (status == 0)
		report(strategies, statistics, NUM_STRATEGIES);
	else
		fprintf(stderr, "evaluate returned code = %d\n", status);
}