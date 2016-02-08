#ifndef DEQUE_CPP
#define DEQUE_CPP
#define INITIAL_SIZE 10

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Deque_DEFINE(myClassPtr)                                                     \
    struct Deque_##myClassPtr {                                                      \
        myClassPtr (*head)(Deque_##myClassPtr *), (*tail)(Deque_##myClassPtr *);    \
	myClassPtr *data;                                             \
	int (*size)(Deque_##myClassPtr *);					     \
	bool (*empty)(Deque_##myClassPtr *);					\
        bool (*func)(myClassPtr *, myClassPtr *);			\
	void (*push_back)(Deque_##myClassPtr *, myClassPtr);			\
	void (*push_front)(Deque_##myClassPtr *, myClassPtr);			\
	void (*dtor)(Deque_##myClassPtr *);					\
    }; 									\
    void Deque_##myClassPtr##_delete(Deque_##myClassPtr *deq) {               \
        free(deq);                                                            \
    }                                                               \
   int Deque_##myClassPtr##_size(Deque_##myClassPtr *deq) { \
	return 0;					\
   }		\
   bool Deque_##myClassPtr##_empty(Deque_##myClassPtr *deq) {		\
	return deq->size(&*deq) == 0;	\
	}							\
    void Deque_##myClassPtr##_ctor(Deque_##myClassPtr *deq, bool (*myClassPtr_less)(myClassPtr, myClassPtr)) {          \
	deq->data = (myClassPtr *) malloc(INITIAL_SIZE * sizeof(myClassPtr));	\
	deq->size = &Deque_##myClassPtr##_size;			\
        deq->dtor = &Deque_##myClassPtr##_delete;                             \
	deq->empty = &Deque_##myClassPtr##_empty;		\
	}							\
    myClassPtr Deque_##myClassPtr##_front(Deque_##myClassPtr *deq) { \
	return deq->data[0];						\
}									\
    myClassPtr Deque_##myClassPtr##_back(Deque_##myClassPtr *deq) { \
	return deq->data[deq->size(&*deq)];						\
}								\
   struct Deque_##myClassPtr##_Iterator {			\
	myClassPtr *head;						\
	void (*inc) (Deque_##myClassPtr##_Iterator *);			\
   };									\
   bool Deque_##myClassPtr##_equal(myClassPtr *deq) {			\
	return false;\
	} 			



bool int_less( int o1, int o2) {
    return o1 < o2;
}
Deque_DEFINE(int)

int main() {  
   printf("Testing\n");
   Deque_int deq;
   Deque_int_ctor(&deq, int_less);    
   assert(deq.size(&deq) == 0);
   assert(deq.empty(&deq)); 
}
  

#endif 
