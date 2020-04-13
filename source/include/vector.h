#ifndef VECTOR_H_INCLUDED
#define VEVTOR_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

#define VECTOR_INITIAL_CAPACITY 8


typedef struct VectorItem VectorItem;

typedef struct Vector
{
    VectorItem **item_space;

    uint32_t size;
    uint32_t capacity;
} Vector;



void vector_init( Vector *vector);

uint32_t vector_find( Vector *vector, VectorItem *item, int ( *equal_func)( VectorItem *,VectorItem *));

int vector_insert( Vector *vector, VectorItem *item, uint32_t index);
int vector_push_back( Vector *vector, VectorItem *item);
int vector_push_front( Vector *vector, VectorItem *item);

VectorItem* vector_erase( Vector *vector, uint32_t index);
VectorItem* vector_pop_back( Vector *vector);
VectorItem* vector_pop_front( Vector *vector);

uint32_t vector_size( Vector *vector);
int vector_empty( Vector *vector);



#ifdef __cplusplus
}
#endif


#endif

