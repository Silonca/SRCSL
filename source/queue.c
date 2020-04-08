#include "include/queue.h"



void queue_init( Queue *queue)
{
    list_init( &(queue->list));
}


void queue_push( Queue *queue, QueueItem *item)
{
    list_push_back( &(queue->list), item);
}

QueueItem* queue_pop( Queue *queue)
{
    return list_pop_front( &(queue->list));
}
