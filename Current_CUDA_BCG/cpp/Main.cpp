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

/*void isIdentical(void);
void cross0(void);
void cross1(void);
void mutate015(void);
void mutate0(void);
void mutate05(void);
void populationInstantiation(void);
void getFittest(void);
void evolve(void);*/

void Play4_10(void);
void Play16_10(void);
void Play32_10(void);
void Play64_10(void);
void Play128_10(void);
void Play256_10(void);
void Play512_10(void);
void Play1024_10(void);

void Play4_100(void);
void Play16_100(void);
void Play32_100(void);
void Play64_100(void);
void Play128_100(void);
void Play256_100(void);
void Play512_100(void);
void Play1024_100(void);

/*void Play5_10(void);
void Play5_100(void);
void Play100_1000(void);
void Play128_10000(void);
void Play256_10000(void);

void Evolver10_3700(void);*/

int main(int argc, char** argv) {
  void(*tests[])(void) = { 
    // Testing the functions of the Genetic Algorithm.
    /*isIdentical,
    cross0,
    cross1,
    mutate015,
    mutate0,
    mutate05,
    populationInstantiation,
    getFittest,
    evolve,*/

    // Testing to play games on the GPU: Play# Cores_# Games
    
      // Test how many of 1024 cores you can use
    /*Play4_10,
    Play16_10,
    Play32_10,
    Play64_10,
    Play128_10,
    Play256_10,
    Play512_10,
    Play1024_10,*/

    // Test how many of 1024 cores you can use
    Play4_100,
    Play16_100,
    Play32_100,
    Play64_100,
    Play128_100,
    Play256_100,
    Play512_100,
    Play1024_100
     
    
    //Play5_10,
    //Play5_100,
    //Play100_1000,
    //Play128_10000,   // 46 seconds
    //Play256_10
    
    //Evolver10_3700
  };
  
  int n = sizeof(tests) / sizeof(void*);

  printf("running tests: %d\n\n", n);
  for (int k = 0; k < n; k++) {
    printf("test %02x: \n", k);
    (*tests[k])();
    printf("\n\n");
  }

  system("pause>0");
}