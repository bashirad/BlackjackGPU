/*
  \ To test the cross function, you can consider the following ideas:

  \ 1. Test for Rule Inheritance: Create two parent strategies with different rules. 
  \		Then, call the cross function to generate a child strategy. 
  \		Verify that the child strategy contains a mixture of rules inherited from both parents.

  \ 2. Test for Uniformity: Create two parent strategies with identical rules. 
  \		Use the cross function to generate multiple child strategies. 
  \		Verify that all the generated child strategies have the same rules as the parents.

  \ 3. Test for Randomness: Create two parent strategies with different rules. 
  \		Use the cross function to generate multiple child strategies. 
  \		Print the rules of each child strategy and observe if there is a random alternation of 
  \ 	genes from both parents. 
  \		Analyze the distribution of inherited rules across the child strategies.

  \ 4. Edge Cases: Test the cross function with extreme cases, such as empty parent strategies or 
  \		strategies with only "NO PLAY" rules. 
  \		Ensure that the function handles these cases gracefully and returns a valid child strategy.
 

  \ To test the mutate function, you can consider the following test cases:

  \ 1. Test Case 1: Mutation occurs

  \		Create a Strategy object with initial rules.
  \		Set a fixed seed for the random number generator to ensure deterministic results.
  \		Call the mutate function on the Strategy object.
  \		Assert that at least one rule has been mutated.
  
  \ 2. Test Case 2: No mutation occurs

  \		Create a Strategy object with initial rules.
  \		Set a fixed seed for the random number generator to ensure deterministic results.
  \		Set the mutation rate to a value higher than 1.0 to ensure no mutation occurs.
  \		Call the mutate function on the Strategy object.
  \		Assert that none of the rules have been mutated.
	
  \ 3. Test Case 3: Multiple mutations occur

  \		Create a Strategy object with initial rules.
  \		Set a fixed seed for the random number generator to ensure deterministic results.
  \		Set the mutation rate to a value close to 0.0 to increase the probability of mutations.
  \		Call the mutate function on the Strategy object.
  \		Assert that multiple rules have been mutated.

	// Test for bugs in cross where strategies are identical
	Strategy child1 = cross(&strategy1, &strategy2);
	bool same = isIdentical(&strategy1, &child1);
	assert(same);
	bool same = isIdentical(&strategy2, &child1);

	// Testing cross over
	1. Trivial test of crossing a strategy with itself: exercises both cross and countDiffs
	2. Trivial test of crossing a strategy with itself: exercises both cross and isIdentical
	3. Test basic strategy vs. strategy 1 has one change: child will be same as strategy 1 50%
	4. Test basic strategy vs. strategy 2 has two changes: child will be same as strategy 2 25%.

	// Testing Mutation
	1. At default rate expect 0.015*430*0.75 +- changes against basic strategy
	2. At non-default rate 5% expect 0.05*430*0.75 +- changes against basic strategy
	3. At non-default rate 0% expect 0 changes against basic strategy

	// Test evolve
	1. Test getFittest
	2. Test evolve -- crashed
	3. Test evolve for tracer X and ... 


	cout



*/