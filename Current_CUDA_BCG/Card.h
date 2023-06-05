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
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Utils.h"

/*! \enum Suit
    \brief Suits in shoe
*/
typedef enum {
	NO_SUIT = 0,     /**< Default suit */
	HEARTS = 'H',
	SPADES = 'S',
	DIAMONDS = 'D',
	CLUBS = 'C'
} Suit;

/*! 
  \enum Rank
  \brief Ranks in shoe
*/
typedef enum {
	NO_RANK=0,        /**< Default rank */
	ACE,
	TWO, 
	THREE, 
	FOUR, 
	FIVE, 
	SIX, 
	SEVEN,
	EIGHT, 
	NINE, 
	TEN, 
	JACK, 
	QUEEN, 
	KING 
} Rank;

/*! \struct Card
    \brief  Defines a card.
*/
typedef struct {
	Rank rank;
	Suit suit;
} Card;

/*!
  \brief Constructor
  \param rank Card rank
  \param suit Card suit
*/
__device__ Card Card_(Rank rank, Suit suit);

/*!
  \brief Returns true if card is a J, Q, or K.
  \param card Card pointer
  \return True if card is a face card
*/
__device__ bool isFace(Card* card);

/*!
  \brief Returns true if card is an Ace.
  \param card Card pointer
  \return True if card is an ace
*/
__device__ bool isAce(Card* card);

/*!
  \brief Returns true if card is a 10, J, Q, or K.
  \param card Card pointer
  \return True if card is a 10
*/
__device__ bool is10(Card* card);

/*!
  \brief Deals a card from the shoe.
  \param Random state pointer
  \return Card
*/
__device__ Card deal(curandState_t* state);

/*!
  \brief Randomly selects a suit.
  \param Random state pointer
  \return Suit
*/
__device__ Suit randomSuit(curandState_t* state);


/*!
\brief Randomly selects a rank.
\param Random state pointer
\return Rank
*/
__device__ Rank randomRank(curandState_t* state);