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
Play100_On_32
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
 16 -0.009524       105        44         4         0        37        13         1         6
 17  0.087379       103        40         8         0        33        14         1         7
 18  0.063725       102        41         3         0        26        14         5        13
 19 -0.072816       103        43         1         0        33        16         3         7
 20 -0.037736       106        38         6         0        30        19         5         8
 21 -0.039216       102        39         4         0        22        21         5        11
 22 -0.029412       102        40         6         0        32        16         1         7
 23 -0.158416       101        33         4         0        32        19         4         9
 24  0.085714       105        44         6         0        27        19         2         7
 25 -0.037736       106        47         2         0        30        17         1         9
 26  0.073529       102        41         5         0        24        17         4        11
 27  0.074257       101        45         1         0        21        15         5        14
 28  0.009804       102        43         2         0        25        20         2        10
 29 -0.121359       103        34         5         0        31        20         4         9
 30 -0.247619       105        31         4         0        34        21         7         8
 31 -0.189320       103        37         3         0        36        14         3        10

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
 16       162         0        76        65        16         5
 17       161         0        78        69        11         3
 18       152         0        77        62        11         2
 19       150         0        72        62        13         3
 20       152         0        76        61         9         6
 21       137         0        69        56        10         2
 22       151         0        75        65         9         2
 23       140         0        65        59        15         1
 24       160         0        76        69        10         5
 25       157         0        71        66        14         6
 26       139         0        73        52        12         2
 27       146         0        74        59        12         1
 28       142         0        74        60         6         2
 29       144         0        70        62         9         3
 30       155         0        75        70         5         5
 31       143         0        75        51        14         3

*/
#include <stdio.h>
#include "Strategy.h"
#include "Game.h"
#include "Kpax.h"
#include "Helpers.h"

#define NUM_STRATEGIES 32
#define NUM_GAMES 100

void Play100_On_32(void) {

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
		printf("Play100_On_32\n");
		report(strategies, statistics, NUM_STRATEGIES);
	}
	else
		fprintf(stderr, "evaluate returned code = %d\n", status);
}