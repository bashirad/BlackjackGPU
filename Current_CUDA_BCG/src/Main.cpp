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
#include <stdlib.h>

void Test00_CUDA_BCG_Basic_Env_Check(void);
void Test01_CUDA_BCG_100_Games(void);
void Test02_CUDA_BCG_1000_Games(void);
void Test03_CUDA_BCG_10000_Games(void);
void Test04_CUDA_BCG_Evolver_3700_Games(void);
void Test05_CUDA_BCG_Population_Instantiation_1000_Games(void);
void Test06_GA_Cross_Uniformity(void);
void Test07_GA_Cross_Rule_Inheritance(void);

int main(int argc, char** argv) {
  void(*tests[])(void) = { 
    /*Test00_CUDA_BCG_Basic_Env_Check,
    Test01_CUDA_BCG_100_Games,
    Test02_CUDA_BCG_1000_Games,
    Test03_CUDA_BCG_10000_Games,
    Test04_CUDA_BCG_Evolver_3700_Games,
    Test05_CUDA_BCG_Population_Instantiation_1000_Games,*/
    //Test06_GA_Cross_Uniformity,
    Test07_GA_Cross_Rule_Inheritance
  };

  int n = sizeof(tests) / sizeof(void*);

  printf("running tests: %d\n", n);
  for (int k = 0; k < n; k++) {
    printf("test %02x: \n", k);
    (*tests[k])();
    printf(" PASSED!\n");
  }

  system("pause>0");
}