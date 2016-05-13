/** @file SharedPtr.hpp
 *  @author Victor Wu
 *  @date May 16, 2016
 *  All rights reserved, code for CS540 - Advanced Object Oriented Programming - class
 */

#include <cstddef>

namespace cs540 {

struct SharedPtr_counter {
	std::size_t* count_;
	SharedPtr_counter() : count_(nullptr) {}	
};


template <typename T>
class SharedPtr {

public:

/// Public data members
std::size_t* count_; 
T* smartPointer;



/// Constructors, Assignments Operators, and Destructor


/** Shared Pointer Constructor
 *  Sets count and smart pointer to null
 */
SharedPtr() : count_(nullptr), smartPointer(nullptr) {
	
}

/** Shared Pointer Constructor
 *  Constructs a smart pointer that points to the given object. The reference count is initialized to one.
 *  @param p reference for the smart pointer
 */

template <typename U>
explicit SharedPtr(U *p) : smartPointer(p) {
	count_ = new size_t(0);	
}

/** Shared Pointer Copy Constructor
 * If p is not null, then reference count of the managed object is incremented. If U * is not implicitly convertible to T *, use of the second constructor will result in a compile-time error when the compiler attempts to instantiate the member template.
 *  @param p reference to a SharedPtr object
 */

SharedPtr(const SharedPtr &p) {
	if (p != NULL) {
		++(*count_);
		smartPointer = p.smartPointer;
	}
}
template <typename U> SharedPtr(const SharedPtr<U> &p) {
	}

/** Shared Pointer Copy Constructor
 * Move the managed object from the given smart pointer. The reference count must remain unchanged. After this function, p must be null. This must work if U * is implicitly convertible to T *.
 */
SharedPtr(SharedPtr &&p);
template <typename U> SharedPtr(SharedPtr<U> &&p);

/** Shared Pointer Assigment Operator
 * Copy assignment. Must handle self assignment. Decrement reference count of current object, if any, and increment reference count of the given object. If U * is not implicitly convertible to T *, this will result in a syntax error. Note that both the normal assignment operator and a member template assignment operator must be provided for proper operation.
 */
SharedPtr &operator=(const SharedPtr &);
template <typename U>
	SharedPtr<T> &operator=(const SharedPtr<U> &);


SharedPtr &operator=(SharedPtr &&p);
template <typename U> SharedPtr &operator=(SharedPtr<U> &&p) {
	swap(p);
	return *this;

}

/** Shared Pointer Deconstructor
 *  Decrement reference count of managed object. If the reference count is zero, delete the object.
 */
~SharedPtr();


///Modifiers

/** Resets modifier
 * The smart pointer is set to point to the null pointer. The reference count for the currently pointed to object, if any, is decremented.
 */
void reset();

template <typename U> void reset(U *p);


/// Accessors

/** Retrieve owned object
 *  Return pointer to the owned object; Note that this will be a pointer-to-const if T is a const-qualified type.
 *  @return a pointer to the owned object
 */
T *get() const;

/** Retrieve owned object
 * Return reference to the owned object; Note that this will be a const-reference if T is a const-qualified type.
 * @return a reference to the owned object
 */
T &operator*() const;

/** Retrieve owned object
 *  Return pointer; Note that this will be a pointer-to-const if T is a const-qualified type.
 *  @return pointer
 */
T *operator->() const;

/** Bool operator 
 *  @return true if the SharedPtr is not null. Else false.
 */
explicit operator bool() const;

};


/// Free Functions

/** Equality operator
 *  @return true if the two smart pointers point to the same object or if they are both null. Note that implicit conversions may be applied.
 */
template <typename T1, typename T2>
bool operator==(const SharedPtr<T1> &, const SharedPtr<T2> &);

/** Equality operator
 * Compare the SharedPtr against nullptr.
 * @return true if shared pointer is null.
 */
template <typename T>
bool operator==(const SharedPtr<T> &, std::nullptr_t);
template <typename T>
bool operator==(std::nullptr_t, const SharedPtr<T> &);

/** Inequality operator
 *  @return true if the SharedPtrs point to different objects, or one points to null while the other does not.
 */
template <typename T1, typename T2>
bool operator!=(const SharedPtr<T1>& p1, const SharedPtr<T2> &p2) {
	return !(p1 == p2);
}

/** Inequality operator
 * Compare the SharedPtr against nullptr.
 * @return false if shared pointer is null
 */ 
template <typename T>
bool operator!=(const SharedPtr<T> &p1, std::nullptr_t &p2) {
	return !(p1 == p2);
}
template <typename T>
bool operator!=(std::nullptr_t, const SharedPtr<T> &);

/**
 * Convert sp by using static_cast to cast the contained pointer. It will result in a syntax error if static_cast cannot be applied to the relevant types.
 */
template <typename T, typename U>
SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp);

/**
 * Convert sp by using dynamic_cast to cast the contained pointer. It will result in a syntax error if dynamic_cast cannot be applied to the relevant types, and will result in a smart pointer to null if the dynamic type of the pointer in sp is not T *.
 */
template <typename T, typename U>
SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp);

}
