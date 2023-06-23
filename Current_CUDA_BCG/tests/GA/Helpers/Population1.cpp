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

#include "Population.h"

Population Population1_() {

	Strategy strategy1 = BasicStrategy_();
	Strategy strategy2 = BasicStrategy_();
	Strategy strategy3 = BasicStrategy_();
	Strategy strategy4 = BasicStrategy_();
	Strategy strategy5 = BasicStrategy_();

	// modify pl for strategies to create different fittnesses 
	strategy1.pl = 50;
	strategy2.pl = 40;
	strategy3.pl = 30;
	strategy4.pl = 20;
	strategy5.pl = 10;
	
	Population population = { 5, 0, 
		{ strategy1, strategy2, strategy3, strategy4, strategy5 }};

	return population;
}