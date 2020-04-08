#ifndef QUEUE_H_INCULDED
#define QUEUE_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "list.h"

typedef ListItem QueueItem;

typedef struct Queue
{
    List list;
} Queue;


void queue_init( Queue *queue);
void queue_push( Queue *queue, QueueItem *item);
QueueItem* queue_pop( Queue *queue);

#ifdef __cplusplus
}
#endif

#endif
