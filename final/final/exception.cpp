/*
 * Consider the push_back() member function of a vector class based on
 * std::vector.  Make it exception-safe and exception-neutral.  This code will
 * not run, but will compile (use -c).
 *
 * Exception-safe means that if an exception is thrown, the container is not in
 * an inconsistent state, and is unchanged as much as possible.
 *
 * Exception-neutral means that exceptions of application-level types are
 * propagated up so that the application can handle them.
 */

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <cassert>

// Leave the class definition unchanged.
template <typename T>
class Vector {
    public:
        Vector() : size(0) {}
        // Other stuff here.
        void push_back(const T &);
    private:
        // Capacity is fixed to 100.
        T array[100];
        std::size_t size;
};

// You only need to modify the body of this function.  You may consider
// exceeding the capacity to be undefined behavior.  (Hint: You need to delete
// code also.)
template <typename T>
void
Vector<T>::push_back(const T &v) { 
    try {
    	assert(size<100);
        array[size] = v;
	++size;
	if (size >= 100) size = 0; //Defining out of Range to be a circular loop!
    }
    catch (const std::out_of_range& oor) {
	std::cerr << "Out of Range error. Unexpected behavior: " << oor.what() <<  std::endl;
    } 
    catch (const std::exception& ba) {
    	std::cerr << "Bad allocation: " << ba.what() << std::endl;
    }
    catch (...) {
        std::cerr << "User object threw." << std::endl;
        std::abort();
    }
}

// Example of usage.
void
foo(Vector<std::string> &v) {
    v.push_back("hello");
}
