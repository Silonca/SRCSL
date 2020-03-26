#include "vector.h"

#include <stddef.h>
#include <stdlib.h>


void vector( Vector *vector)
{
    vector->item_space = ( Vector*)malloc( sizeof( VectorItem*) * (uint32_t)(VECTOR_INITIAL_SIZE));
    vector->size = VECTOR_INITIAL_SIZE;
    vector->cnt = 0;
}

uint32_t vector_find( Vector *vector, VectorItem *item, int ( *equal_func)( VectorItem *,VectorItem *))
{
    for( uint32_t index = 0; index < vector->cnt; ++index)
        if( equal_func( vector->item_space[index], item) == 0)
            return index;
}

int vector_insert( Vector *vector, VectorItem *item, uint32_t index)
{
    
    if( index > vector->cnt)
        return -1;

    ++vector->cnt;
    if(  vector->cnt >= vector->size)
    {
        vector->item_space = ( Vector*)realloc( vector->item_space, sizeof( VectorItem*) * vector->size *2);
        if( vector->item_space == NULL)
            return -2;
    }
    
    for( uint32_t temp = vector->cnt; temp > index; --temp)
    {
        vector->item_space[temp] = vector->item_space[temp-1];
    }
    vector->item_space[index] = item;

    return 0;
}


int vector_push_back( Vector *vector, VectorItem *item)
{
    return vector_insert( vector, item, vector->cnt);
}


int vector_push_front( Vector *vector, VectorItem *item)
{
    return vector_insert( vector, item, 0);
}

VectorItem* vector_erase( Vector *vector, uint32_t index)
{
    VectorItem *item = vector->item_space[index];
    if( index >= vector->cnt)
        return NULL;
    
    for(; index < vector->cnt - 1; ++index)
    {
        vector->item_space[index] = vector->item_space[index + 1];
    } 
    --vector->cnt;
    return item;
}


VectorItem* vector_pop_back( Vector *vector)
{
    return vector_erase( vector, vector->cnt);
}

VectorItem* vector_pop_front( Vector *vector)
{
    return vector_erase( vector, 0);
}

