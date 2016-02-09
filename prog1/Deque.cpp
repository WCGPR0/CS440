
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Deque.hpp"

#define Deque_DEFINE(myClassPtr)                                                     \
    struct Deque_##myClassPtr##_Iterator {			\
	myClassPtr *pointer;						\
	void (*inc) (Deque_##myClassPtr##_Iterator *);			\
	int deref(Deque_##myClassPtr##_Iterator *);								\
   };									\
    bool Deque_##myClassPtr##_Iterator_equal (Deque_##myClassPtr##_Iterator it1, Deque_##myClassPtr##_Iterator it2) {		\
	return *(it1.pointer) == *(it2.pointer);			\
}	\
struct Deque_##myClassPtr {                                                      \
	Deque_##myClassPtr##_Iterator (*begin)(Deque_##myClassPtr *);	\
	Deque_##myClassPtr##_Iterator (*end)(Deque_##myClassPtr *);	\
        myClassPtr (*front)(Deque_##myClassPtr *), (*back)(Deque_##myClassPtr *);    \
	myClassPtr *data;                                             \
	int capacity = INITIAL_SIZE, space = 0;					\
	char type_name[6 + sizeof(myClassPtr)];					\
	int (*size)(Deque_##myClassPtr *);					     \
	bool (*empty)(Deque_##myClassPtr *);					\
        bool (*func)(myClassPtr *, myClassPtr *);			\
	void (*push_back)(Deque_##myClassPtr *, myClassPtr);			\
	void (*push_front)(Deque_##myClassPtr *, myClassPtr);			\
	void (*pop_back)(Deque_##myClassPtr *);			\
	void (*pop_front)(Deque_##myClassPtr *);			\
	void (*dtor)(Deque_##myClassPtr *);					\
    }; 									\
	Deque_##myClassPtr##_Iterator.inc = &Deque_##myClassPtr##_Iterator_increment; \
   void Deque_##myClassPtr##_Iterator_increment(Deque_##myClassPtr##_Iterator it) {	\
	it.pointer += sizeof(Deque_##myClassPtr);			\
	}		\
    void Deque_##myClassPtr##_delete(Deque_##myClassPtr *deq) {               \
        free(deq);                                                            \
    }                                                               \
   Deque_##myClassPtr##_Iterator Deque_##myClassPtr##_begin(Deque_##myClassPtr *deq) { \
 	Deque_##myClassPtr##_Iterator di;			\
	di.pointer = &deq->data[0];				\
	return di;						\
   }		\
   Deque_##myClassPtr##_Iterator Deque_##myClassPtr##_end(Deque_##myClassPtr *deq) { \
 	Deque_##myClassPtr##_Iterator di;			\
	di.pointer = &deq->data[deq->space];			\
	return di;						\
   }		\
   int Deque_##myClassPtr##_size(Deque_##myClassPtr *deq) { \
	return deq->space;					\
   }		\
   bool Deque_##myClassPtr##_empty(Deque_##myClassPtr *deq) {		\
	return deq->size(&*deq) == 0;	\
	}							\
   void Deque_##myClassPtr##_push_back(Deque_##myClassPtr *deq, myClassPtr data) { \
	if (deq->space++ >= deq->capacity)	{					\
		deq->capacity *= 2;	\
		deq->data = (myClassPtr *) realloc(deq->data, deq->capacity * sizeof(myClassPtr)); \
	} \
	deq->data[deq->space] = data; \
}	\
   void Deque_##myClassPtr##_push_front(Deque_##myClassPtr *deq, myClassPtr data) { \
	if (deq->space++ >= deq->capacity)	{					\
		deq->capacity *= 2;	\
		deq->data = (myClassPtr *) realloc(deq->data, deq->capacity * sizeof(myClassPtr)); \
	} \
		for (int i = deq->space; i > 0; --i) \
			deq->data[i] = deq->data[i - 1];			\
		deq->data[0] = data;					\
}	\
   void Deque_##myClassPtr##_pop_front(Deque_##myClassPtr *deq) { \
	if (deq->space > 0)					\
		deq->data[deq->space--] = NULL; 		\
}	\
   void Deque_##myClassPtr##_pop_back(Deque_##myClassPtr *deq) { \
	if (deq->space-- > 0)					\
		for (int i = 0; i < deq->space + 1; ++i) \
			deq->data[i] = deq->data[i + 1];			\
}	\
myClassPtr Deque_##myClassPtr##_front(Deque_##myClassPtr *deq) { \
	return deq->data[0];						\
}									\
    myClassPtr Deque_##myClassPtr##_back(Deque_##myClassPtr *deq) { \
	return deq->data[deq->size(&*deq)];						\
} \
    void Deque_##myClassPtr##_ctor(Deque_##myClassPtr *deq, bool (*myClassPtr_less)(myClassPtr, myClassPtr)) {          \
	deq->data = (myClassPtr *) malloc(INITIAL_SIZE * sizeof(myClassPtr));	\
	deq->size = &Deque_##myClassPtr##_size;			\
        deq->dtor = &Deque_##myClassPtr##_delete;                             \
	deq->empty = &Deque_##myClassPtr##_empty;		\
	strcpy(deq->type_name, "Deque_" #myClassPtr); 			\
	deq->front = &Deque_##myClassPtr##_front;		\
	deq->back = &Deque_##myClassPtr##_back;			\
	deq->push_back = &Deque_##myClassPtr##_push_back;		\
	deq->push_front = &Deque_##myClassPtr##_push_front;		\
	deq->pop_back = &Deque_##myClassPtr##_pop_back;			\
	deq->pop_front = &Deque_##myClassPtr##_pop_front;		\
	deq->begin = &Deque_##myClassPtr##_begin;		\
	deq->end = &Deque_##myClassPtr##_end;			\
	}							\
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
   printf("---- %s, %d\n", deq.type_name, int(sizeof(deq.type_name)));
   deq.push_back(&deq, 1);
   deq.push_back(&deq, 2);
   deq.push_back(&deq, 3);
   deq.push_front(&deq, 0);
   deq.push_front(&deq, -1);

   printf("%d\n", deq.front(&deq));
   printf("%d\n", deq.back(&deq));
   assert(deq.front(&deq) == -1);
   assert(deq.back(&deq) == 3);

   deq.pop_front(&deq);
   deq.pop_back(&deq);
   printf("%d\n", deq.front(&deq));
   printf("%d\n", deq.back(&deq)); 
   assert(deq.front(&deq) == 0);
   assert(deq.back(&deq) == 2);
   assert(deq.size(&deq) == 3);

   for (Deque_int_Iterator it = deq.begin(&deq);
         !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            printf("%d\n", it.deref(&it));
        }
}



