#include "stack.h"




void stack_init( Stack *stack)
{
    vector_init( &(stack->vector));
}


int stack_push( Stack *stack, StackItem *item)
{
    return vector_push_back( &(stack->vector), item);
}


StackItem* stack_pop( Stack *stack)
{
    return vector_pop_back( &(stack->vector));
}


