#pragma once
//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"
#include "Strategy.h"
#include "Game.h"

#ifndef OK
#define OK 0
#endif

void report(Strategy* strategies, Game* statistics, int numCores);
cudaError_t check(cudaError_t status, const char msg[]);

/*!
  \brief Returns uniform integer random deviate in range, inclusive.
  \param min Minimum number in range, inclusive
  \param max Maximum number in range, inclusive
  \return Integer in range
*/
int random(int min, int max);

/*!
  \brief Returns uniform floating point random deviate in range [0, 1), that is, exclusive of 1.
  \return Floating point number.
*/
float random();
