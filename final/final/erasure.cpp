#include <iostream>
#include <vector>

// Put your code here.
#include <functional>


// Do not modify this class.
struct A {
        friend std::ostream &operator<<(std::ostream &, const A &);
    public:
        A(int i) : ptr{new int{i}} {}
        A(const A &tt) : ptr(new int{*tt.ptr}) {}
        ~A() { delete ptr; }
        A &operator=(const A &) = delete;
    private:
        int *ptr;
};

struct Base {
	virtual	void execute() { //Virtual function
		value = new A(); //Pass in parameter to execute!
	}
	private:
		void* value; //Hidden Value	
};

struct Val : Base {		
	void execute() {
			//value = new 	
		}
		~Val() {
			delete value;
		}
};


template <typename... Ts>
std::vector<Val *>
helper(Ts... params) {
	std::vector<std::function<void()> > v1;
	[v1](...) { v1.push_back(wrap(Ts)) };	
	return v1; 
}

template <typename T>
std::function<void()> wrap(const T& t) {
	return std::bind(&Val<T>::execute, Val<T>(t));
}

// Do not modify this function.
std::ostream &
operator<<(std::ostream &os, const A &a) {
    return os << *a.ptr;
}

/*
 * This returns a vector of pointers to objects that have the given value
 * "hidden" inside of them.  Arguments to this function should be saved by
 * value, and are guaranteed to have copy constructors, but not assignment
 * operators.
 */
template <typename... Ts>
std::vector<Val *>
erase_type(Ts... params) {
    return helper(params...);
}

int main() {

    std::vector<Val *> v = erase_type(1, 3.14, std::string("hello"), A(1234));

    // The below should print out one line:
    // [1, 3.14, hello, 1234]
    std::cerr << v << std::endl;

    // Free.
    for (auto e : v) {
        delete e;
    }
}
