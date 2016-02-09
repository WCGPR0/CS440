#ifndef test
#define INITIAL_SIZE 10
#endif

#define Deque_DEFINE(myClassPtr)                                                     \
    struct Deque_##myClassPtr##_Iterator;			\
    bool Deque_##myClassPtr##_Iterator_equal (Deque_##myClassPtr##_Iterator it1, Deque_##myClassPtr##_Iterator it2);		\
struct Deque_##myClassPtr;                                                    \
   void Deque_##myClassPtr##_Iterator_increment(Deque_##myClassPtr##_Iterator it);	\
   void Deque_##myClassPtr##_delete(Deque_##myClassPtr *deq);               \
   Deque_##myClassPtr##_Iterator Deque_##myClassPtr##_begin(Deque_##myClassPtr *deq);	\
   Deque_##myClassPtr##_Iterator Deque_##myClassPtr##_end(Deque_##myClassPtr *deq);		\
   int Deque_##myClassPtr##_size(Deque_##myClassPtr *deq);	\
   bool Deque_##myClassPtr##_empty(Deque_##myClassPtr *deq);		\
   void Deque_##myClassPtr##_push_back(Deque_##myClassPtr *deq, myClassPtr data); \
   void Deque_##myClassPtr##_push_front(Deque_##myClassPtr *deq, myClassPtr data); \
   void Deque_##myClassPtr##_pop_front(Deque_##myClassPtr *deq); \
   void Deque_##myClassPtr##_pop_back(Deque_##myClassPtr *deq);  \
   myClassPtr Deque_##myClassPtr##_front(Deque_##myClassPtr *deq); \
   myClassPtr Deque_##myClassPtr##_back(Deque_##myClassPtr *deq);		\
   void Deque_##myClassPtr##_ctor(Deque_##myClassPtr *deq, bool (*myClassPtr_less)(myClassPtr, myClassPtr));	\
   bool Deque_##myClassPtr##_equal(myClassPtr *deq);


