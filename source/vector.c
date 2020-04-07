#include "include/vector.h"

#include <stddef.h>
#include <stdlib.h>


void vector( Vector *vector)
{
    vector->item_space = ( VectorItem**)malloc( sizeof( VectorItem*) * (uint32_t)(VECTOR_INITIAL_CAPACITY));
    vector->capacity = VECTOR_INITIAL_CAPACITY;
    vector->size = 0;
}

uint32_t vector_find( Vector *vector, VectorItem *item, int ( *equal_func)( VectorItem *,VectorItem *))
{
    uint32_t index;
    for( index = 0; index < vector->size; ++index)
        if( equal_func( vector->item_space[index], item) == 0)
            return index;
}

int vector_insert( Vector *vector, VectorItem *item, uint32_t index)
{
    uint32_t temp;
    
    if( index > vector->size)
        return -1;

    ++vector->size;
    if(  vector->size >= vector->capacity)
    {
        vector->item_space = ( VectorItem**)realloc( vector->item_space, sizeof( VectorItem*) * vector->capacity *2);
        if( vector->item_space == NULL)
            return -2;
    }
    
    for( temp = vector->size; temp > index; --temp)
    {
        vector->item_space[temp] = vector->item_space[temp-1];
    }
    vector->item_space[index] = item;

    return 0;
}


int vector_push_back( Vector *vector, VectorItem *item)
{
    return vector_insert( vector, item, vector->size);
}


int vector_push_front( Vector *vector, VectorItem *item)
{
    return vector_insert( vector, item, 0);
}

VectorItem* vector_erase( Vector *vector, uint32_t index)
{
    VectorItem *item = vector->item_space[index];
    if( index >= vector->size)
        return NULL;
    
    for(; index < vector->size - 1; ++index)
    {
        vector->item_space[index] = vector->item_space[index + 1];
    } 
    --vector->size;
    return item;
}


VectorItem* vector_pop_back( Vector *vector)
{
    return vector_erase( vector, vector->size);
}

VectorItem* vector_pop_front( Vector *vector)
{
    return vector_erase( vector, 0);
}


uint32_t vector_size( Vector *vector)
{
    return vector->size;
}

int vector_empty(  Vector *vector)
{
    return vector->size == 0 ? 1 : 0;
}
