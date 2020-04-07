#include "include/list.h"

#include <stddef.h>
#include <stdlib.h>



void list_init( List *list)
{
    list->nil = ( ListNode*)malloc( sizeof( ListNode));
    list->nil->item = NULL;
    list->nil->next = list->nil;
    list->nil->prev = list->nil;
}


ListNode* list_find( List *list, ListItem *item, int ( *equal_func)( ListItem *,ListItem *))
{
    ListNode *node = list->nil->next;
    while( node != list->nil && equal_func( node->item, item) != 0)
    {
        node = node->next;
    }
    return node;
}


ListNode* list_insert( ListNode *node, ListItem *item)
{
    ListNode *next = ( ListNode*)malloc( sizeof( ListNode));
    if( next == NULL)
        return next;
    next->item = item;
    next->prev = node;
    next->next = node->next;
    node->next = next;
    return next;
}

ListNode* list_push_back( List *list, ListItem *item)
{
    return list_insert( list->nil->prev, item);
}


ListNode* list_push_front( List *list, ListItem *item)
{
    return list_insert( list->nil, item);
}


ListItem* list_erase( ListNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;

    ListItem *item = node->item;
    if( node->item != NULL)
        free( node);
    return item;
}

ListItem* list_pop_back( List *list)
{
    return list_erase( list->nil->prev);
}


ListItem* list_pop_front( List *list)
{
    return list_erase( list->nil->next);
}




