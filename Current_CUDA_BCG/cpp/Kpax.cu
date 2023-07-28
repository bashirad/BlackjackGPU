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

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <curand.h>
#include <curand_kernel.h>
#include "Card.h"
#include "Hand.h"
#include "Strategy.h"
#include "Player.h"
#include "Game.h"
#include "Helpers.h"
#include "Kpax.h"

#define ACE_AS_11 10

__device__ __shared__ curandState_t* states;

__device__ int random(int min, int max, curandState_t* state) {

	// See https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range/6852396
	return (curand(state) % (max + 1 - min)) + min;
}

///////////////// Card

__device__ Card Card_(Rank rank, Suit suit) {
	Card card = { rank, suit };
	return card;
}

__device__ Card Card_(int rank, Suit suit) {
	Card card = { (Rank)rank, suit };
	return card;
}

__device__ Suit randomSuit(curandState_t* state) {
	Suit suits[] = { HEARTS, SPADES, DIAMONDS, CLUBS };

	int index = random(0, 3, state);

	return suits[index];
}

__device__ Rank randomRank(curandState_t* state) {
	Rank rank = (Rank)random(ACE, KING, state);

	return rank;
}

__device__ Card deal() {
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	curandState_t* state = &states[index];

	// Get a random suit
	Suit suit = randomSuit(state);

	// Get a rank
	Rank rank = randomRank(state);

	// Make a card
	Card card = Card_(rank, suit);
	return card;
}

__device__ bool isFace(Card* card) {
	return card->rank == JACK || card->rank == QUEEN || card->rank == KING;
}

__device__ bool isAce(Card* card) {
	return card->rank == ACE;
}

__device__ bool is10(Card* card) {
	return isFace(card) || card->rank == TEN;
}


////////// Hand

__device__ Hand Hand_() {
	Hand hand = { {
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT) },
			0, 0, 1.0, NULL };

	return hand;
}

__device__ Hand Hand_(void* player) {
	Hand hand = { {
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT) },
			0, 0, 1.0, player };

	return hand;
}

__device__ Card hit(Player* player) {
	int sz = player->size;

	return hit(player, sz - 1);
}

__device__ Card hit(Player* player, int handno) {
	return hit(&player->hands[handno]);
}

__device__ int score(Hand* hand) {
	int sum = 0;

	int nAces = 0;

	for (int k = 0; k < hand->size; k++) {
		Card card = hand->cards[k];
		sum += isFace(&hand->cards[k]) ? 10 : hand->cards[k].rank;

		// If rank == ACE_AS_11 won't be counted here (correctly!)
		if (card.rank == ACE)
			nAces++;
	}

	// Account for soft aces
	for (int k = 0; k < nAces; k++) {
		if (sum + ACE_AS_11 > 21)
			break;

		sum += ACE_AS_11;
	}

	return sum;
}

__device__ bool isBroke(Hand* hand) {
	return hand->value > 21;
}

__device__ bool isCharlie(Hand* hand) {
	return hand->size == 5 && hand->value <= 21;
}

__device__ bool isBlackjack(Hand* hand) {
	return hand->size == 2 && hand->value == 21;
}

__device__ bool isBlackjack(void* player, Hand* hand) {
	Player* playor = (Player*)player;

	return isBlackjack(hand) && playor->size == 1;
}

__device__ Card hit(Hand* hand) {
	Card card = deal();

	hit(hand, &card);

	return card;
}

__device__ void hit(Hand* hand, Card* card) {
	int index = hand->size++;

	hand->cards[index] = *card;

	hand->value = score(hand);

	return;
}

__device__ bool isPair(Hand* hand) {
	if (hand->size != 2)
		return false;

	Card card1 = hand->cards[0];
	Card card2 = hand->cards[1];

	return card1.rank == card2.rank;
}

__device__ bool isAcePlusX(Hand* hand) {
	if (hand->size != 2)
		return false;

	Card card1 = hand->cards[0];
	Card card2 = hand->cards[1];

	return (card1.rank == ACE && card2.rank != ACE) || (card1.rank != ACE && card2.rank == ACE);
}

/////////////// Strategy

__host__ __device__ Strategy Strategy_() {
	Strategy s = {
		0.0,
		{
			//          2  3  4  5  6  7  8  9  T  A
			/*21*/		X, X, X, X, X, X, X, X, X, X, // Section I: lower=0, upper=9
			/*20*/		X, X, X, X, X, X, X, X, X, X,
			/*19*/		X, X, X, X, X, X, X, X, X, X,
			/*18*/		X, X, X, X, X, X, X, X, X, X,
			/*17*/		X, X, X, X, X, X, X, X, X, X,
			/*16*/		X, X, X, X, X, X, X, X, X, X,
			/*15*/		X, X, X, X, X, X, X, X, X, X,
			/*14*/		X, X, X, X, X, X, X, X, X, X,
			/*13*/		X, X, X, X, X, X, X, X, X, X,
			/*12*/		X, X, X, X, X, X, X, X, X, X,

			/*11*/		X, X, X, X, X, X, X, X, X, X, // Section II: lower=10, upper=17
			/*10*/		X, X, X, X, X, X, X, X, X, X,
			/*9 */		X, X, X, X, X, X, X, X, X, X,
			/*8 */		X, X, X, X, X, X, X, X, X, X,
			/*7 */		X, X, X, X, X, X, X, X, X, X,
			/*6 */		X, X, X, X, X, X, X, X, X, X,
			/*5 */		X, X, X, X, X, X, X, X, X, X,
			/*4 */		X, X, X, X, X, X, X, X, X, X, // When number of splits limited by house use this row

			/*A,K */	X, X, X, X, X, X, X, X, X, X, // Section III: lower=18, upper=29
			/*A,Q */	X, X, X, X, X, X, X, X, X, X,
			/*A,J */	X, X, X, X, X, X, X, X, X, X,
			/*A,T */	X, X, X, X, X, X, X, X, X, X,
			/*A,9 */	X, X, X, X, X, X, X, X, X, X,
			/*A,8 */	X, X, X, X, X, X, X, X, X, X,
			/*A,7 */	X, X, X, X, X, X, X, X, X, X,
			/*A,6 */	X, X, X, X, X, X, X, X, X, X,
			/*A,5 */	X, X, X, X, X, X, X, X, X, X,
			/*A,4 */	X, X, X, X, X, X, X, X, X, X,
			/*A,3 */	X, X, X, X, X, X, X, X, X, X,
			/*A,2 */	X, X, X, X, X, X, X, X, X, X,

			/*A,A */	X, X, X, X, X, X, X, X, X, X, // Section IV: lower=30, upper=42
			/*T,K */	X, X, X, X, X, X, X, X, X, X,
			/*T,Q */	X, X, X, X, X, X, X, X, X, X,
			/*T,J */	X, X, X, X, X, X, X, X, X, X,
			/*T,T */	X, X, X, X, X, X, X, X, X, X,
			/*9,9 */	X, X, X, X, X, X, X, X, X, X,
			/*8,8 */	X, X, X, X, X, X, X, X, X, X,
			/*7,7 */	X, X, X, X, X, X, X, X, X, X,
			/*6,6 */	X, X, X, X, X, X, X, X, X, X,
			/*5,5 */	X, X, X, X, X, X, X, X, X, X,
			/*4,4 */	X, X, X, X, X, X, X, X, X, X,
			/*3,3 */	X, X, X, X, X, X, X, X, X, X,
			/*2,2 */	X, X, X, X, X, X, X, X, X, X,
		},
		{ { 0,  9 },
		{ 10, 17 },
		{ 18, 29 },
		{ 30, 42 } },
		{0, 0, 0, 0, 0}
	};
	return s;
}

__host__ __device__ Strategy BasicStrategy_() {
	Strategy s = {
		0.0,
		{
			//          2  3  4  5  6  7  8  9  T  A
			/*21*/		S, S, S, S, S, S, S, S, S, S, // Section I: lower=0, upper=9
			/*20*/		S, S, S, S, S, S, S, S, S, S,
			/*19*/		S, S, S, S, S, S, S, S, S, S,
			/*18*/		S, S, S, S, S, S, S, S, S, S,
			/*17*/		S, S, S, S, S, S, S, S, S, S,
			/*16*/		S, S, S, S, S, H, H, H, H, H,
			/*15*/		S, S, S, S, S, H, H, H, H, H,
			/*14*/		S, S, S, S, S, H, H, H, H, H,
			/*13*/		S, S, S, S, S, H, H, H, H, H,
			/*12*/		H, H, S, S, S, H, H, H, H, H,

			/*11*/		D, D, D, D, D, D, D, D, D, H, // Section II: lower=10, upper=17
			/*10*/		D, D, D, D, D, D, D, D, H, H,
			/*9 */		H, D, D, D, D, H, H, H, H, H,
			/*8 */		H, H, H, H, H, H, H, H, H, H,
			/*7 */		H, H, H, H, H, H, H, H, H, H,
			/*6 */		H, H, H, H, H, H, H, H, H, H,
			/*5 */		H, H, H, H, H, H, H, H, H, H,
			/*4 */		H, H, H, H, H, H, H, H, H, H, // When number of splits limited by house use this row

			/*A,K */	S, S, S, S, S, S, S, S, S, S, // Section III: lower=18, upper=29
			/*A,Q */	S, S, S, S, S, S, S, S, S, S,
			/*A,J */	S, S, S, S, S, S, S, S, S, S,
			/*A,T */	S, S, S, S, S, S, S, S, S, S,
			/*A,9 */	S, S, S, S, S, S, S, S, S, S,
			/*A,8 */	S, S, S, S, S, S, S, S, S, S,
			/*A,7 */	S, D, D, D, D, S, S, H, H, H,
			/*A,6 */	H, D, D, D, D, H, H, H, H, H,
			/*A,5 */	H, H, D, D, D, H, H, H, H, H,
			/*A,4 */	H, H, D, D, D, H, H, H, H, H,
			/*A,3 */	H, H, H, D, D, H, H, H, H, H,
			/*A,2 */	H, H, H, D, D, H, H, H, H, H,

			/*A,A */	P, P, P, P, P, P, P, P, P, P, // Section IV: lower=30, upper=42
			/*T,K */	S, S, S, S, S, S, S, S, S, S,
			/*Q,Q */	S, S, S, S, S, S, S, S, S, S,
			/*J,J */	S, S, S, S, S, S, S, S, S, S,
			/*T,T */	S, S, S, S, S, S, S, S, S, S,
			/*9,9 */	P, P, P, P, P, S, P, P, S, S,
			/*8,8 */	P, P, P, P, P, P, P, P, P, P,
			/*7,7 */	P, P, P, P, P, P, H, H, H, H,
			/*6,6 */	P, P, P, P, P, H, H, H, H, H,
			/*5,5 */	D, D, D, D, D, D, D, D, H, H,
			/*4,4 */	H, H, H, P, P, H, H, H, H, H,
			/*3,3 */	P, P, P, P, P, P, H, H, H, H,
			/*2,2 */	P, P, P, P, P, P, H, H, H, H,
		},
		{ { 0,   9 },
		{ 10, 17 },
		{ 18, 29 },
		{ 30, 42 } },
		{ 0, 0, 0, 0, 0 }
	};
	return s;
}

#define RANK(rank) (rank >= 10 ? 10 : rank)

__device__ Play doSection4(Hand* hand, Card* upcard, Strategy* strategy) {
	Card card1 = hand->cards[0];

	int offset = 0;

	if (!isAce(&card1))
		offset = KING - card1.rank + 1;

	int row = strategy->jumpTab[SECTION4].lower + offset;

	int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	int index = row * 10 + col;

	Play play = strategy->rules[index];

	return play;
}

__device__ Play doSection3(Hand* hand, Card* upcard, Strategy* strategy) {
	Card card1 = hand->cards[0];
	Card card2 = hand->cards[1];

	Card card = card1;
	if (card1.rank == ACE)
		card = card2;

	int offset = KING - card.rank;

	int row = strategy->jumpTab[SECTION3].lower + offset;

	int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	int index = row * 10 + col;

	Play play = strategy->rules[index];

	return play;
}

__device__ Play doSection2(Hand* hand, Card* upcard, Strategy* strategy) {
	int offset = 11 - hand->value;

	int row = strategy->jumpTab[SECTION2].lower + offset;

	int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	int index = row * 10 + col;

	Play play = strategy->rules[index];

	// Double-down when more than 2 cards means hit -- see Instructional Services (1983, 2000)
	if (play == DOUBLE_DOWN && hand->size > 2)
		return HIT;

	return play;
}

__device__ Play doSection1(Hand* hand, Card* upcard, Strategy* strategy) {
	int offset = 21 - hand->value;

	int row = strategy->jumpTab[SECTION1].lower + offset;

	int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	int index = row * 10 + col;

	Play play = strategy->rules[index];

	// Double-down when more than 2 cards means hit -- see Instructional Services (1983, 2000)
	if (play == DOUBLE_DOWN && hand->size > 2)
		return HIT;

	return play;
}


/////////////// Player

__device__ Player Player_(Strategy* strategy) {
	// TODO: the player's hand is not pointing back to the player
	Player player = { { Hand_() }, 1, strategy, 0.0 };

	return player;
}

__device__ void init(Player* player) {
	player->hands[0].player = player;
}

__device__ int add(Player* player, Hand* hand) {
	int index = player->size++;

	hand->player = player;

	player->hands[index] = *hand;

	return index;
}


/////////////// Game

__host__ Game Game_() {
	return{ { 0, 0, 0, 0, 0, 0, 0 }, 0, 0.0 };
}

__device__ void play(Strategy* strategy, Game* statistics) {
	// Create the heads-up game
	Player player = Player_(strategy);
	init(&player);

	Hand dealer = Hand_();

	// Deal the initial round
	hit(&player);

	hit(&dealer);

	hit(&player);

	hit(&dealer);

	Card upcard = dealer.cards[0];
	
	// Play the player's hand
	play(&player, &upcard);

	// Player the dealer's hand
	play(&dealer, &player, statistics);

	// Save the statistics.
	statistics->pl += player.pl;

	statistics->nohands += player.size;

//	int sum = 0;
//
//	int n = sizeof(statistics->count) / sizeof(int);
//
//	for (int index = 0; index < n; index++)
//		sum += statistics->count[index];
}

__device__ void play(Player* player, Card* upcard) {
	playout(&player->hands[0], upcard);
}

__device__ void playout(Hand* hand, Card* upcard) {
	Play play = getPlay(hand, upcard);

	Player* player = (Player*)hand->player;
	player->strategy->visits[play]++;

	switch (play) {
	case NO_PLAY:
		break;

	case STAY:
		break;

	case HIT:
		hit(hand);

		if (isBroke(hand) || isBlackjack(hand))
			return;

		if (hand->size >= MAX_HAND_CARDS)
			return;

		///*
		//if (isCharlie(hand))
		//return;
		//*/

		playout(hand, upcard);
		break;

	case DOUBLE_DOWN:
		// Double bet and hit once
		hand->bet *= 2.0;

		hit(hand);
		break;

	case SPLIT:
		if (hand->size != 2)
			return;

		split(hand, upcard);
		break;
	}

	return;
}

__device__ void split(Hand* hand1, Card* upcard) {
	// If there's a split overflow, fallback to non-split option
	Player* player = (Player*)hand1->player;

	if (player->size >= MAX_YOUR_HANDS) {
		overflowSplit(hand1, upcard);
		return;
	}

	// Allow splitting Aces once and hit each Ace once without playthrough.
	// TODO: look up whether double-down allowed on split hand
	bool playThrough = true;

	if (isPair(hand1) && hand1->cards[0].rank == ACE)
		playThrough = false;

	// Make the new hand
	Hand newHand = Hand_(player);

	// Get card from 1st hand
	Card card = hand1->cards[1];
	hand1->size--;

	// Hit the 1st hand with new card from the deck
	hit(hand1);

	// Hit 2nd hand with card from 1st hand and the deck
	hit(&newHand, &card);

	hit(&newHand);

	// Add 2nd hand to the player
	int index = add(player, &newHand);

	Hand* hand2 = &player->hands[index];

	// Not playing through after hitting
	if (!playThrough)
		return;

	// Play through each hand recursively
	playout(hand1, upcard);

	playout(hand2, upcard);
}

__device__ void overflowSplit(Hand* hand, Card* upcard) {
	Player* player = (Player*)hand->player;

	Strategy* strategy = player->strategy;

	Play play = NO_PLAY;

	if (hand->value >= 12) {
		play = doSection1(hand, upcard, strategy);
	}
	else {
		play = doSection2(hand, upcard, strategy);
	}

	switch (play) {
	case STAY:
		break;

	case HIT:
		hit(hand);

		if (!isBroke(hand))
			playout(hand, upcard);

		break;

	case DOUBLE_DOWN:
		hit(hand);

		hand->bet *= 2.0;

		break;

	case SPLIT:
		// A split here is tantamount to STAY
		break;

	case NO_PLAY:
		//assert(false);
		break;
	}

	return;
}

__device__ void play(Hand* dealer, Player* player, Game* statistics) {
	int remaining = player->size;

	// Payout the hands we can at this point...
	for (int index = 0; index < player->size; index++) {
		Hand* hand = &player->hands[index];

		if (isBroke(hand)) {
			player->pl -= hand->bet;

			statistics->count[BUSTS]++;

			remaining--;
		}
		// A+10 on split hand not "natural" blackjack and doesn't receive bonus.
		// See https://en.wikipedia.org/wiki/Aces_and_eights_(blackjack).
		else if (isBlackjack(player, hand)) {
			player->pl += (hand->bet * PAYOFF_BLACKJACK);

			statistics->count[BLACKJACKS]++;

			remaining--;
		}
		/*
		else if (isCharlie(hand)) {
		player->pl += (hand->bet * PAYOFF_CHARLIE);

		statistics->count[CHARLIES]++;

		remaining--;
		}
		*/
	}

	// If no hands remaining, the dealer does not have to play
	if (remaining == 0)
		return;

	// Dealer stands on (soft or otherwise) 17 or higher 
	while (dealer->value < 17) {
		hit(dealer);
	}

	// Test all the remaining hands
	for (int index = 0; index < player->size; index++) {
		Hand* hand = &player->hands[index];

		// We've handle these above
		if (isBroke(hand) || isBlackjack(player, hand))
			continue;

		// Dealer blackjack beats all except player blackjack and charlie
		if (isBlackjack(dealer)) {
			player->pl -= hand->bet;
			statistics->count[DEALER_BLACKJACKS]++;
		}

		// If dealer broke, pay the player
		else if (isBroke(dealer)) {
			player->pl += hand->bet;
			statistics->count[WINS]++;
		}

		// If dealer lost, pay the player
		else if (dealer->value < hand->value) {
			player->pl += hand->bet;
			statistics->count[WINS]++;
		}

		// If player lost, collect for house
		else if (dealer->value > hand->value) {
			player->pl -= hand->bet;
			statistics->count[LOSSES]++;
		}

		// If hands same, nobody wins or loses
		else if (dealer->value == hand->value) {
			player->pl += 0;
			statistics->count[PUSHES]++;
		}
		else
			/* DO NOTHING */ ;
	}
}

__device__ Play getPlay(Hand* hand, Card* upcard) {
	Strategy* strategy = ((Player*)hand->player)->strategy;

	Play play1 = NO_PLAY;

	if (isPair(hand))
		play1 = doSection4(hand, upcard, strategy);

	else if (isAcePlusX(hand))
		play1 = doSection3(hand, upcard, strategy);

	else if (hand->value >= 5 && hand->value <= 11)
		play1 = doSection2(hand, upcard, strategy);

	else
		play1 = doSection1(hand, upcard, strategy);

	return play1;

	// Commented code below left for debugging only.
/*
	int dealer = isFace(upcard) ? 10 : upcard->rank;

	if (dealer == ACE)
		dealer += ACE_AS_11;

	Play play2 = NO_PLAY;

	if (isPair(hand) && (hand->cards[0].rank == ACE || hand->cards[0].rank == EIGHT))
		play2 = SPLIT;

	else if (hand->value == 11 && hand->size == 2)
		play2 = DOUBLE_DOWN;

	else if (hand->value <= 10)
		play2 = HIT;

	else if (hand->value >= 17)
		play2 = STAY;

	else if (hand->value <= 16 && dealer <= 6)
		play2 = STAY;

	else if (hand->value <= 16 && dealer > 6)
		play2 = HIT;

	//else
		//assert(false);

	return play2;
*/
}

__device__ Game go(int ngames, Strategy* strategy) {
	Game statistics = Game_();

	for (int gameno = 0; gameno < ngames; gameno++) {
		play(strategy, &statistics);
	}
	
	return statistics;
}


/////////////// See http://cs.umw.edu/~finlayson/class/fall16/cpsc425/notes/cuda-random.html

/* this GPU kernel function is used to initialize the random states */
__global__ void init(unsigned int seed, curandState_t* states_) {
	// Calculate the thread's index
	int index = blockIdx.x * blockDim.x + threadIdx.x;

	/* we have to initialize the state */
	curand_init(seed, // the seed can be the same for each core, here we pass the time in from the CPU
		index,        // the sequence number should be different for each thread (unless you want all
					  // thread to get the same sequence of numbers for some reason - use thread id!
		0,            // the offset is how much extra we advance in the sequence for each call, can be 0
		&states_[index]);

	states = states_;
}

/* this GPU kernel takes plays n games given pointer to the strategies and pointer return statistics. */
__global__ void run(unsigned int numGames, Strategy* strategies, Game* statistics) {
	// Calculate the thread's unique index
	int index = blockIdx.x * blockDim.x + threadIdx.x;

	// Play the games
	statistics[index] = go(numGames, &strategies[index]);
}

/////////////// GPU driver

int evaluate(int numThreads, Strategy* strategies, int numGames, Game* statistics, int seed) {
	return evaluate(1, numThreads, strategies, numGames, statistics, seed);
}

 int evaluate(int numBlocks, int numThreads, Strategy* strategies, int numGames, Game* statistics, int seed) {
	try {
//		printf("start evaluate function\n");

		// Setup and initialize the device

		// Choose the GPU to run on
		cudaError_t cudaStatus = cudaSetDevice(0);
		check(cudaStatus, "could not find gpu device!");
//		printf("cudaSetDevice: %d\n",cudaStatus);
		
		
		// Allocate a stack space per thread on the GPU
		cudaStatus = cudaDeviceSetLimit(cudaLimitStackSize, LIMIT_STACK_SIZE);
		check(cudaStatus, "set stack limit failed!");
//		printf("cudaDeviceSetLimit: %d\n",cudaStatus);

		size_t asize;
		cudaStatus = cudaDeviceGetLimit(&asize, cudaLimitStackSize);
		check(cudaStatus, "get stack limit test failed!");
//		printf("cudaDeviceGetLimit: %d asize=%d\n",cudaStatus,asize);

		if (asize != LIMIT_STACK_SIZE)
			check(cudaErrorNotSupported, "test stack limit failed!");

		// Random states per thread
		curandState_t* dev_states;

		// Allocate space on the GPU for the random states
		cudaStatus = cudaMalloc((void**)&dev_states, numThreads * sizeof(curandState_t));
		check(cudaStatus, "failed to malloc random states!");
//		printf("cudaMalloc: %d\n",cudaStatus);

		// Invoke kernel to initialize all of the random states
		init <<< numBlocks, numThreads/numBlocks >>> (seed, dev_states);
//		printf("init random states done!\n");		

		// Check for any errors launching the kernel
		cudaStatus = cudaGetLastError();
		check(cudaStatus, "failed to launch kernel to initialize random states on device!");

		cudaStatus = cudaDeviceSynchronize();
		check(cudaStatus, "failed to initialize random states on device!");

		// Create the strategies
		Strategy* dev_strategies = 0;

		// Allocate the space on the GPU for the strategies

		cudaStatus = cudaMalloc((void**)&dev_strategies, numThreads * sizeof(Strategy));
		check(cudaStatus, "failed to malloc stategies on device!");

		// Copy the strategies to the GPU
		cudaStatus = cudaMemcpy(dev_strategies, strategies, numThreads * sizeof(Strategy), cudaMemcpyHostToDevice);
//		printf("cudaMemcpy strategies to device: %d\n",cudaStatus);
		
		check(cudaStatus, "failed to copy stategies to device!");

		// Allocate space on the GPU for the game statistics
		Game* dev_statistics = 0;

		cudaStatus = cudaMalloc((void**)&dev_statistics, numThreads * sizeof(Game));
		check(cudaStatus, "failed to malloc statistics on device!");
//		printf("cudaMalloc strategies %d bytes: %d\n",cudaStatus,numThreads * sizeof(Game));

		// There is no need to copy the statistics to the GPU since they are generated by the GPU

		// Finally invoke the kernel to run the games */
		run <<< numBlocks, numThreads/numBlocks >>> (numGames, dev_strategies, dev_statistics);
//		printf("run %d games returned!\n",numGames);		
		
		// Check for any errors launching the kernel
		cudaStatus = cudaGetLastError();
		check(cudaStatus, "failed to launch kernel to run games on device!");
//		printf("cudaGetLastError: %d\n",cudaStatus);


		// cudaDeviceSynchronize waits for the kernel to finish, and returns
		// any errors encountered during the launch.
		cudaStatus = cudaDeviceSynchronize();
		check(cudaStatus, "failed to run games on device!");
//		printf("cudaDeviceSynchronize: %d\n",cudaStatus); 

		// Copy results back to host
		cudaStatus = cudaMemcpy(strategies, dev_strategies, numThreads * sizeof(Strategy), cudaMemcpyDeviceToHost);
//		printf("cudaMemcpy results %d bytes: %d\n",cudaStatus,numThreads * sizeof(Strategy));

		check(cudaStatus, "failed to copy back strategies from device!");
//		printf("cudaMemcpy results %d bytes: %d\n",cudaStatus,numThreads * sizeof(Strategy));

		cudaMemcpy(statistics, dev_statistics, numThreads * sizeof(Game), cudaMemcpyDeviceToHost);
		check(cudaStatus, "failed to copy back statistics from device!");
//		printf("cudaMemcpy statistics %d bytes: %d\n",cudaStatus,numThreads * sizeof(Game));

		/* free the memory we allocated for the states and numbers */
		cudaFree(dev_states);
		// We don't use dev_games
		//cudaFree(dev_games);
		cudaFree(dev_strategies);
		cudaFree(dev_statistics);

		return OK;
	}
	catch (cudaError_t err) {
		return err;
	}
}


