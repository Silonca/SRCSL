#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


#ifdef __cplusplus
extern "C"{
#endif

#include "vector.h"

typedef VectorItem StackItem;

typedef struct Stack 
{
    Vector vector;
} Stack;


void stack_init( Stack *stack);
int stack_push( Stack *stack, StackItem *item);
StackItem* stack_pop( Stack *stack);


#ifdef __cplusplus
}
#endif

#endif 

