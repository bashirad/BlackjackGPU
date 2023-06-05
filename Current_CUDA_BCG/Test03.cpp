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
tid        pl     hands      wins       bjs  charlies     loses    breaks      dbjs    pushes
0    0.035437      1030       408        49         0       285       156        34        98
1   -0.006737      1039       400        50         0       279       177        45        88
2    0.014947      1037       424        47         0       287       174        32        73
3   -0.008252      1030       406        43         0       270       187        32        92
4    0.004873      1026       410        48         0       282       162        28        96
5   -0.004892      1022       392        56         0       290       177        29        78
6    0.100681      1028       433        57         0       282       141        30        85
7    0.001934      1034       404        44         0       294       180        28        84
8   -0.020039      1023       387        53         0       298       168        22        95
9   -0.030732      1025       396        39         0       277       198        40        75

tid   total     nones     stays      hits   doubles    splits
0      1462         0       760       570       102        30
1      1476         0       749       585       103        39
2      1485         0       744       601       103        37
3      1504         0       735       643        96        30
4      1454         0       751       574       103        26
5      1450         0       716       593       119        22
6      1451         0       758       548       117        28
7      1477         0       752       595        96        34
8      1500         0       752       626        99        23
9      1452         0       717       612        98        25

*/
#include <stdio.h>
#include "Strategy.h"
#include "Game.h"
#include "Kpax.h"
#include "Helpers.h"

#define NUM_BLOCKS 4
#define NUM_THREADS_PER_BLOCK 32
#define NUM_THREADS_TOTAL (NUM_BLOCKS * NUM_THREADS_PER_BLOCK)
#define NUM_STRATEGIES NUM_THREADS_TOTAL
#define NUM_GAMES 10000

void test03(void) {
  Strategy strategies[NUM_STRATEGIES];

  for (int index = 0; index < NUM_STRATEGIES; index++) {
    strategies[index] = BasicStrategy_();
  }

  Game statistics[NUM_STRATEGIES];
  for (int index = 0; index < NUM_STRATEGIES; index++) {
    statistics[index] = Game_();
  }

  int status = evaluate(NUM_BLOCKS, NUM_STRATEGIES, strategies, NUM_GAMES, statistics);

  if (status == 0)
    report(strategies, statistics, NUM_STRATEGIES);
  else
    fprintf(stderr, "evaluate returned code = %d\n", status);
}