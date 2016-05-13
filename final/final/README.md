Victor Wu
B00403882

--- Comments ----
I originally approached this problem by thinking of creating a generic vector that takes from the varadic parameters of the function; it was hard to do this without using the Boost::any library and since having to dynamically cast everything back afterwards from a void type is way too much work - I started working on trying to use a virtual function to do the ostream.

I was stuck on this approach and didn't know where I could implement the virtual function inheritance for the mapping, unfortunately. Didn't have too much time to compile and remove most of the errors, and the current approach is a mix of what I was originally trying to do and what I moved onto doing.
