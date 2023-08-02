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
#include <time.h>

void isIdentical(void);
void cross0(void);
void cross1(void);
void mutate015(void);
void mutate0(void);
void mutate05(void);
void populationInstantiation(void);
void getFittest(void);
void evolve(void);
void strategize(void);
void popularizeTest(void);
void engine(void);
void randStrategyTest(void);
void mergeSortTest(void);
void Evolver10_3700(void);


// 10 Games on Diff Num of Cores
void Play10_On_4(void);
void Play10_On_16(void);
void Play10_On_32(void);
void Play10_On_64(void);
void Play10_On_128(void);
void Play10_On_256(void);
void Play10_On_512(void);
void Play10_On_1024(void);

// 100 Games on Diff Num of Cores
void Play100_On_4(void);
void Play100_On_16(void);
void Play100_On_32(void);
void Play100_On_64(void);
void Play100_On_128(void);
void Play100_On_256(void);
void Play100_On_512(void);
void Play100_On_1024(void);

// Diff Num of Games on 1024 Cores
void Play10_On_1024(void);
void Play100_On_1024(void);
void Play1000_On_1024(void);
void Play10000_On_1024(void);
void Play100000_On_1024(void);
void Play1000000_On_1024(void);



int main(int argc, char** argv) {
    // Timer for tests
    time_t start_seconds;
    time_t end_seconds;

    start_seconds = time(NULL);

    void(*tests[])(void) = {


    // Testing the functions of the Genetic Algorithm.
    //isIdentical,
    /*cross0,
    cross1,
    mutate015,
    mutate0,
    mutate05,*/
    //populationInstantiation//,
    //getFittest,
    //evolve
    //strategize//,
    //popularizeTest//,
    //randStrategyTest
    //engine
    mergeSortTest
    //Evolver10_3700,*/

    // Testing to play games on the GPU: Play# Cores_# Games
    
    // Test how many of 1024 cores you can use
    /*
    Play10_On_4,
    Play10_On_16,
    Play10_On_32,
    Play10_On_64,
    Play10_On_128,
    Play10_On_256,
    Play10_On_512,
    Play10_On_1024,

    Play100_On_4,
    Play100_On_16,
    Play100_On_32,
    Play100_On_64,
    Play100_On_128,
    Play100_On_256,
    Play100_On_512,*/

    //Play10_On_1024//,                       1       sec
    //Play100_On_1024//,                    2       sec
    //Play1000_On_1024//,                   6       sec
    //Play10000_On_1024,                    48      sec
    //Play100000_On_1024//,                 485     sec OR 8    min
    //Play1000000_On_1024                   4868    sec OR 81   min OR 1 hr and 20 min
    
    // We can use the Play10000_On_1024 to play 10,000,000 games
    // Each cycle takes 48 sec. 
    // to play 2 billion games, we need 200 cycles.
    // That is 200 * 48 seconds = 9600
    //  9600 / 60 seconds = 160 minutes OR 2 hrs and 40 minutes
  };
  
  int n = sizeof(tests) / sizeof(void*);

  printf("running tests: %d\n\n", n);
  for (int k = 0; k < n; k++) {
    printf("test %02x: \n", k);
    (*tests[k])();
    printf("\n\n");
  }

  end_seconds = time(NULL);

  time_t duration;
  duration = end_seconds - start_seconds;

  printf("Test lasted for %d seconds ", duration);

  system("pause>0");
}