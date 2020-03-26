#ifndef QUEUE_H_INCULDED
#define QUEUE_H_INCLUDED

#include "list.h"

typedef ListItem QueueItem;

typedef struct Queue
{
    List list;
} Queue;


void queue_init( Queue *queue);
int queue_push( Queue *queue, QueueItem *item);
QueueItem* queue_pop( Queue *queue);



#endif
