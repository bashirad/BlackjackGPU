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
#include "Strategy.h"

/*! \def Maximum number of hards allowed by player, ie, player can split n-1 times. */
#define MAX_YOUR_HANDS 4

/*!
  \struct Player
  \brief  Defines a player with a collection of hands.
*/
typedef struct {
	Hand hands[MAX_YOUR_HANDS];  /**< Hands of player */
	int size;                    /**< Number of hands of player not to exceed MAX_YOUR_HANDS */
	Strategy* strategy;          /**< Pointer to strategy player uses across all hands */
	float pl;                    /**< P&L for player */
} Player;

/*!
  \brief Constructor.
  \param strategy Strategy pointer
  \param state Random state pointer
  \return A player instance
*/
__device__ Player Player_(Strategy* strategy);

/*! 
  \brief Initializes a player.
  \param player Player pointer
*/
__device__ void init(Player* player);

/*!
  \brief Adds a hand to player.
  \param player Player pointer
  \param hand Hand pointer--the hand to add to player
*/
__device__ int add(Player* player, Hand* hand);

/*!
  \brief Hits player with one card from the shoe.
  \param player Player pointer
  \return Card player hit with
*/
__device__ Card hit(Player* player);

/*!
  \brief Hits player specified hand number with one card from the shoe.
  \param player Player pointer
  \param handno Hand number
  \return Card player hit with
*/
__device__ Card hit(Player* player, int handno);