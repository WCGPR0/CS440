#ifndef DEQUE_CPP
#define DEQUE_CPP
#define INITIAL_SIZE 10

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Deque_DEFINE(myClassPtr)                                                     \
    struct Deque_##myClassPtr {                                                      \
        myClassPtr (*front)(Deque_##myClassPtr *), (*back)(Deque_##myClassPtr *);    \
	myClassPtr *data;                                             \
	int capacity = INITIAL_SIZE, space = 0;					\
	char type_name[6 + sizeof(myClassPtr)];					\
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
	return deq->space;					\
   }		\
   bool Deque_##myClassPtr##_empty(Deque_##myClassPtr *deq) {		\
	return deq->size(&*deq) == 0;	\
	}							\
   void Deque_##myClassPtr##_push_back(Deque_##myClassPtr *deq, myClassPtr data) { \
	if (deq->capacity)	{					\
		deq->capacity *= 2;	\
		deq->data = (myClassPtr *) realloc(deq->data, deq->capacity * sizeof(myClassPtr)); \
	} \
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
	}							\
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
   printf("---- %s, %d\n", deq.type_name, int(sizeof(deq.type_name)));
   deq.push_back(&deq, 1);
   //deq.push_back(&deq, 2);
   //deq.push_back(&deq, 3);
   //deq.push_front(&deq, 0);
   //deq.push_front(&deq, -1);

   //printf("%d\n", deq.front(&deq));
   //printf("%d\n", deq.back(&deq));
   //assert(deq.front(&deq) == -1);
  // assert(deq.back(&deq) == 3);

}


#endif 
