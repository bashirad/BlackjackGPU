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

#pragma once

#define LIMIT_STACK_SIZE (8*4096) // LIMIT_STACK_SIZE (4*4096)
#define SEED_CURAND 0

/*!
  \brief Evaluates a number of strategies with an equal number of threads for a number of games using exactly one GPU block.
  \param numStrategies Number of strategies
  \param strategies Strategies must be size as numStrategies
  \param numGames Number of games to play for each strategy
  \param statistics Result statistics for each strategy
  \return OK if successful, not OK (e.g., the CUDA error) if not ok
*/
int evaluate(int numThreads, Strategy* strategies, int numGames, Game* statistics, int seed);

/*!
  \brief Evaluates a number of strategies with an equal number of threads for a number of games using a number of GPU blocks.
  \param numBlocks Number of GPU blocks
  \param numStrategies Number of strategies
  \param strategies Strategies must be size as numStrategies
  \param numGames Number of games to play for each strategy
  \param statistics Result statistics for each strategy
  \return OK if successful, not OK (e.g., the CUDA error) if not ok
*/
int evaluate(int numBlocks, int numThreads, Strategy* strategies, int numGames, Game* statistics, int seed);