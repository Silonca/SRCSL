#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "vector.h"

typedef VectorItem StackItem;

typedef struct Stack 
{
    Vector vector;
} Stack;


void stack_init( Stack *stack);
void stack_push( Stack *stack, StackItem *item);
StackItem* stack_pop( Stack *stack);


#endif 

