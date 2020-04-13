#include "include/list.h"

#include <stddef.h>
#include <stdlib.h>



void list_init( List *list)
{
    list->nil = ( ListNode*)malloc( sizeof( ListNode));
	if (list->nil == NULL)
		return;
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


ListNode* list_insert( List *list, ListNode *node, ListItem *item)
{
    ListNode *next = ( ListNode*)malloc( sizeof( ListNode));
    if( next == NULL)
        return next;
    next->item = item;
    next->prev = node;
    next->next = node->next;
    node->next = next;

	++list->length;

    return next;
}

ListNode* list_push_back( List *list, ListItem *item)
{
    return list_insert( list, list->nil->prev, item);
}


ListNode* list_push_front( List *list, ListItem *item)
{
    return list_insert( list, list->nil, item);
}


ListItem* list_erase( List *list, ListNode *node)
{
	ListItem *item = NULL;

	if ( node == list->nil || node == NULL)
		return NULL;

	item = node->item;

    node->prev->next = node->next;
    node->next->prev = node->prev;

	--list->length;
    free( node);
	
    return item;
}

ListItem* list_pop_back( List *list)
{
    return list_erase( list, list->nil->prev);
}


ListItem* list_pop_front( List *list)
{
    return list_erase( list, list->nil->next);
}

ListNode * list_get(List * list, int32_t index)
{
	int32_t a = 0;
	ListNode *node = list->nil;
	if( index == 0 || abs(index) > list_get_length(list))
		return node;
	while ( a != index)
	{
		if (index > 0)
		{
			++a;
			node = node->next;
		}
		else
		{
			--a;
			node = node->prev;
		}
	}
	return node;
		
}

int32_t list_get_length(List * list)
{
	return list->length;
}




