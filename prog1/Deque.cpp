#ifndef DEQUE_CPP
#define DEQUE_CPP

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Deque_DEFINE(myClassPtr)                                                     \
    struct Deque_##myClassPtr {                                                      \
        myClassPtr* head, tail;   				\
	myClassPtr data;                                             \
	int (*size)(Deque_##myClassPtr *);					     \
	bool (*empty)(Deque_##myClassPtr *);					\
        bool (*func);					\
	void (*push_back)(Deque_##myClassPtr *, myClassPtr);			\
	void (*push_front)(Deque_##myClassPtr *, myClassPtr);			\
	void (*dtor)(Deque_##myClassPtr *);					\
    }; 									\
    void Deque_##myClassPtr##_delete(Deque_##myClassPtr *ap) {               \
        free(ap);                                                            \
    }                                                               \
   int Deque_##myClassPtr##_size(Deque_##myClassPtr *) { \
	return 0;					\
   }		\
    void Deque_##myClassPtr##_ctor(Deque_##myClassPtr *t, bool (ap)) {          \
        t = (Deque_##myClassPtr *) malloc(sizeof(Deque_##myClassPtr));            \
        t->func = &ap;                                    \
	t->size = &Deque_##myClassPtr##_size;			\
        t->dtor = &Deque_##myClassPtr##_delete;                             \
	}							\
   struct Deque_##myClassPtr##_Iterator {			\
	myClassPtr *head;						\
	void (*inc) (Deque_##myClassPtr##_Iterator *);			\
   };									\
   bool Deque_##myClassPtr##_equal(myClassPtr *deq) {			\
	\
	} 			



bool int_less(const int &o1, const int &o2) {
    return o1 < o2;
}
Deque_DEFINE(int)

int main() {  
   printf("Testing\n");
   Deque_int deq;
   Deque_int_ctor(&deq, int_less);    

   assert(deq.size(&deq) == 0);
   //assert(deq.empty(&deq)); 
}
  

#endif 
