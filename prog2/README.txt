Victor Wu
vwu4@binghamton.edu
B00403882

------------------------------------------
CS440 Advanced Object Oriented Programming
	PROJECT 2 README FILE
------------------------------------------

IMPORTANT!!!
Please do not grade this project yet; I'm hoping to submit an updated version late.
IMPORTANT!!!

This currently doesn't work with the supplied test code, and it has only been tested with my custom Driver code. It is also missing a few implementation of a few functions.

I used a SkipList as a data structure, and had to change around the code a couple of times. I felt it had too much space complexity when I created an entire graph of nodes - so I created only n nodes, given n data points. Each of these nodes have an array of keys and pointers of size X, where X is the preset tier levels - which is defined as a macro constant (MAX_LEVEL).

This implementation is under a few presumed constraints:
	-There are built in comparison (less than, greater than, etc). for templated members
	-The SkipList tiers are not dynamic- that is, while nodes can grow, tiers cannot grow
