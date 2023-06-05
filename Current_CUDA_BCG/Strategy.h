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
#include "Utils.h"
#include "Hand.h"

/*!
  \enum Strategy
  \brief Plays player can make.
  The raw enum values from 0...n which is important for indexing the plays.
*/
typedef enum {
	NO_PLAY = 0, 
	STAY, 
	HIT, 
	DOUBLE_DOWN, 
	SPLIT 
} Play;

/*! \def Total number of rules in a strategy. */
#define NUMBER_RULES (10*43)

/*! \def Section 1 index in jump (lookaside) table */
#define SECTION1 0

/*! \def Section 2 index in jump (lookaside) table */
#define SECTION2 1

/*! \def Section 2 index in jump (lookaside) table */
#define SECTION3 2

/*! \def Section 2 index in jump (lookaside) table */
#define SECTION4 3

// Macros to make table formatting read better
#define S STAY
#define H HIT
#define D DOUBLE_DOWN
#define P SPLIT
#define X NO_PLAY

/*!
  \typedef Lookaside
  \brief Jump lookaside table entry
*/
typedef struct {
	int lower;    /**< Lower or starting index */
	int upper;    /**< Upper or ending (inclusive) index */
} Lookaside;


/*!
  \struct Strategy
  \brief  Defines a strategy.
  \see Play
*/
typedef struct {
	float pl;                  /**< P&L */
	Play rules[NUMBER_RULES];  /**< Rules */
	Lookaside jumpTab[4];      /**< Jump table */
	int visits[5];             /**< Play visit record indexed by STAY, HIT, etc. */
} Strategy;


/*!
\brief Basic strategy constructor
Makes a default, "no play" strategy
*/
__host__ __device__ Strategy Strategy_(void);

/*!
  \brief Basic strategy constructor
  Makes a basic strategy from Instructional Services (1983, 2000)
*/
__host__ __device__ Strategy BasicStrategy_(void);

/*!
  \brief Does section IV of strategy
  \param hand Hand pointer
  \param upcard Dealer upcard pointer
  \param strategy Strategy pointer
*/
__device__ Play doSection4(Hand* hand, Card* upcard, Strategy* strategy);

/*!
  \brief Does section III of strategy
  \param hand Hand pointer
  \param upcard Dealer upcard pointer
  \param strategy Strategy pointer
*/
__device__ Play doSection3(Hand* hand, Card* upcard, Strategy* strategy);

/*!
  \brief Does section II of strategy
  \param hand Hand pointer
  \param upcard Dealer upcard pointer
  \param strategy Strategy pointer
*/
__device__ Play doSection2(Hand* hand, Card* upcard, Strategy* strategy);

/*!
  \brief Does section I of strategy
  \param hand Hand pointer
  \param upcard Dealer upcard pointer
  \param strategy Strategy pointer
*/
__device__ Play doSection1(Hand* hand, Card* upcard, Strategy* strategy);
