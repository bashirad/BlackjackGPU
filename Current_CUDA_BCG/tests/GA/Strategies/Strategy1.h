#pragma once

#include "GA.h"
#include "Strategy.h"

//#define E D
//#define T S
//#define Q P
//#define I H

/*!
	\brief Strategy1 is identical to the BasicStrategy except at [0][0].
	\Strategy1 has X at [0][0] while the BasicStrategy has S.
	\Strategy1 can be used for testing purposes.
*/

Strategy Strategy1_() {
	Strategy s = {
		0.0,
		{
			//          2  3  4  5  6  7  8  9  T  A
			/*21*/		X, S, S, S, S, S, S, S, S, S, // Section I: lower=0, upper=9
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
