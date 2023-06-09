/*
 \ To test the cross function, you can consider the following ideas:

 \ 1. Test for Rule Inheritance: Create two parent strategies with different rules. 
 \    Then, call the cross function to generate a child strategy. 
 \    Verify that the child strategy contains a mixture of rules inherited from both parents.

 \ 2. Test for Uniformity: Create two parent strategies with identical rules. 
 \    Use the cross function to generate multiple child strategies. 
 \    Verify that all the generated child strategies have the same rules as the parents.

 \ 3. Test for Randomness: Create two parent strategies with different rules. 
 \    Use the cross function to generate multiple child strategies. 
 \    Print the rules of each child strategy and observe if there is a random alternation of 
 \	  genes from both parents. 
 \    Analyze the distribution of inherited rules across the child strategies.

 \ 4. Edge Cases: Test the cross function with extreme cases, such as empty parent strategies or 
 \    strategies with only "NO PLAY" rules. 
 \    Ensure that the function handles these cases gracefully and returns a valid child strategy.
 
*/