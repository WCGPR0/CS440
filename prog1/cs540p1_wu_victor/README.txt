----------------------
Author
----------------------

Name: Victor Wu
B-number: B00403882
E-mail: vwu4@binghamton.edu

----------------------
Setup
----------------------
Have the two files, test.cpp int the same (sub)directories.
Compile using C++11 or later, and ignore warnings.

----------------------
Issues and Concerns
----------------------

While the basic double ended queue has been implemented, there are some key implementations that is not executing properly. As such, the provided test file is a snipped from the original test, and tests only the deque.

Hoping to resolve the following issues:
	-Iterator has a segfault, likely an off-by-one, error during iteration
	-Tests (Test random access performance), comparing, and equality 

This project took me a long time because the compiler was not useful in providing hints where there could be an error. The line it references is the declaration of the macro, and with so many lines of macros, it is hard to find where the error was except to go through manually line by line. But I learned a lot about macros, and hope to fix the incomplete portions in this program.
