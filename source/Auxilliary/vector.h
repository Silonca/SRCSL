#ifndef VECTOR_H_INCLUDED
#define VEVTOR_H_INCLUDED


#include <stdint.h>

#define VECTOR_INITIAL_SIZE 8


typedef struct VectorItem VectorItem;

typedef struct Vector
{
    VectorItem **item_space;
    uint32_t cnt;
    uint32_t size;
} Vector;



void vector_init( Vector *vector);

uint32_t vector_find( Vector *vector, VectorItem *item, int ( *equal_func)( VectorItem *,VectorItem *));

uint32_t vector_insert( Vector *vector, VectorItem *item, uint32_t index);
uint32_t vector_push_back( Vector *vector, VectorItem *item);
uint32_t vector_push_front( Vector *vector, VectorItem *item);

VectorItem* vector_erase( Vector *vector, uint32_t *index);
VectorItem* vector_pop_back( Vector *vector);
VectorItem* vector_pop_front( Vector *vector);



#endif

