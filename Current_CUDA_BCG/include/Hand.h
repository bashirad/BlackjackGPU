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
#include <curand.h>
#include <curand_kernel.h>
#include "Utils.h"
#include "Card.h"

/*! \def Maximum number of hards allowed in single hand. */
#define MAX_HAND_CARDS 10

/*!
  \struct Hand
  \brief  Defines a hand.
*/
typedef struct {
	Card cards[MAX_HAND_CARDS];  /**< Cards in hand */
	int value;                   /**< Point value of hand between 4 to >= 21 */
	int size;                    /**< Number of cards in hand not to exceed MAX_HAND_CARDS */
	float bet;                   /**< Bet amount for this hand */
	void* player;                /**< Back pointer to player of this hand */
} Hand;

/*!
  \brief Constructor of empty hand
  \param Random state pointer
  \return A hand instance
  This constructor does not initialize the player back pointer nor
  add any cards.
*/
__device__ Hand Hand_();

/*!
  \brief Constructor of empty hand
  \param player Player of this hand
  \param Random state pointer
  \return A hand instance
  This constructor initializes the player back point but does not add any cards. 
*/
__device__ Hand Hand_(void* player);

/*!
  \brief Scores hand according to its value.
  \param hand Hand pointer
  \return Value of hand
*/
__device__ int score(Hand* hand);

/*!
  \brief Hits hand with card from shoe.
  \param hand Hand pointer
  \return Card hit of hand
*/
__device__ Card hit(Hand* hand);

/*!
  \brief Hits hand with specified card.
  \param hand Hand pointer
  \param card Card pointer
  \return Card hit of hand
*/
__device__ void hit(Hand* hand, Card* card);

/*!
  \brief Returns true if hand is broke.
  \param hand Hand pointer
  \return True if hand broke, false otherwise
*/
__device__ bool isBroke(Hand* hand);

/*!
  \brief Returns true if hand is a charlie.
  \param hand Hand pointer
  \return True if hand is a charlie, false otherwise.
*/
__device__ bool isCharlie(Hand* hand);

/*!
  \brief Returns true if dealer hand is a blackjack.
  \param dealer Hand pointer
  \return True if hand is a blackjack, false otherwise.
*/
__device__ bool isBlackjack(Hand* dealer);

/*!
  \brief Returns true if player hand is a "natural" blackjack.
  \param player Player pointer
  \param player Hand pointer
  \return True if hand is a natural blackjack, false otherwise.
*/
__device__ bool isBlackjack(void* player, Hand* hand);

/*!
  \brief Returns true if hand is a pair, e.g., 2,2; 3,3; etc.
  \param hand Hand pointer
  \return True if hand is a pair, false otherwise.
*/
__device__ bool isPair(Hand* hand);

/*!
  \brief Returns true if hand is two cards, Ace+x.
  \param hand Hand pointer
  \return True if hand has A+x, false otherwise.
*/
__device__ bool isAcePlusX(Hand* hand);