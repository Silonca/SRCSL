#ifndef SRCSL_MEMMANG_H_INCLUDED
#define SRCSL_MEMMANG_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct MemBlock
{
	uint8_t *next;
	unsigned int size;
} MemBlock;

typedef struct MemMang
{
	uint8_t *base;
	unsigned int size;

	MemBlock start;
	MemBlock *end;
} MemMang;


void srcsl_memmang_init(MemMang *m, uint8_t *base);

void* srcsl_malloc(MemMang *m, unsigned int size);
void* srcsl_realloc(MemMang *m, void *p, unsigned int size);

void srcsl_free(MemMang *m, void *p);


#ifdef __cplusplus
}
#endif


#endif 

