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
Play100_On_16
tid        pl     hands      wins       bjs  charlies     loses    breaks      dbjs    pushes
  0 -0.004950       101        32         9         0        27        15         6        12
  1  0.148148       108        48         8         0        24        21         2         5
  2 -0.062500       104        43         1         0        29        18         4         9
  3  0.128713       101        42         6         0        20        20         1        12
  4  0.083333       102        41         9         0        28        12         1        11
  5 -0.102941       102        32         7         0        28        22         4         9
  6  0.014563       103        46         3         0        35        10         1         8
  7 -0.044118       102        43         1         0        27        22         0         9
  8 -0.130000       100        31         8         0        34        19         3         5
  9 -0.097087       103        39         4         0        33        19         2         6
 10  0.109524       105        42         7         0        28        14         2        12
 11  0.033981       103        41         5         0        28        20         2         7
 12  0.169903       103        46         7         0        25        10         6         9
 13 -0.107843       102        34         6         0        35        21         3         3
 14 -0.202970       101        35         3         0        33        21         2         7
 15  0.106796       103        43         6         0        26        12         5        11

tid     total     nones     stays      hits   doubles    splits
  0       146         0        78        59         8         1
  1       146         0        74        51        13         8
  2       154         0        75        68         7         4
  3       144         0        71        64         8         1
  4       138         0        74        48        14         2
  5       138         0        69        58         9         2
  6       151         0        86        55         7         3
  7       129         0        70        49         8         2
  8       141         0        71        60        10         0
  9       152         0        69        67        13         3
 10       144         0        77        50        12         5
 11       147         0        76        61         7         3
 12       143         0        80        49        11         3
 13       147         0        72        66         7         2
 14       157         0        71        76         9         1
 15       152         0        81        60         8         3

*/
#include <stdio.h>
#include "Strategy.h"
#include "Game.h"
#include "Kpax.h"
#include "Helpers.h"

#define NUM_STRATEGIES 16
#define NUM_GAMES 100

void Play100_On_16(void) {

	Strategy strategies[NUM_STRATEGIES];

	for (int index = 0; index < NUM_STRATEGIES; index++) {
		strategies[index] = BasicStrategy_();
	}

	Game statistics[NUM_STRATEGIES];
	for (int index = 0; index < NUM_STRATEGIES; index++) {
		statistics[index] = Game_();
	}

	int status = evaluate(NUM_STRATEGIES, strategies, NUM_GAMES, statistics, SEED_CURAND);

	if (status == 0) {
		printf("Play100_On_16\n");
		report(strategies, statistics, NUM_STRATEGIES);
	}
	else
		fprintf(stderr, "evaluate returned code = %d\n", status);
}