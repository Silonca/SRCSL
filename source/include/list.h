#ifndef SRCSL_LIST_H_INCLUDED
#define SRCSL_LIST_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

typedef struct ListItem ListItem;

typedef struct ListNode
{
    struct ListNode *prev;
    struct ListNode *next;

    struct ListItem *item;
} ListNode;


typedef struct List
{
    ListNode *nil;
	int32_t length;
} List;

void list_init( List *list);

ListNode* list_find( List *list, ListItem *item, int ( *equal_func)( ListItem *,ListItem *));

ListNode* list_insert( List *list, ListNode *node, ListItem *item);
ListNode* list_push_back( List *list, ListItem *item);
ListNode* list_push_front( List *list, ListItem *item);

ListItem* list_erase( List *list, ListNode *node);
ListItem* list_pop_back( List *list);
ListItem* list_pop_front( List *list);

ListNode* list_get(List *list, int32_t index);

int32_t list_get_length(List *list);

#ifdef __cplusplus
}
#endif

#endif
