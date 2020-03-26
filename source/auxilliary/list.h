#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

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
} List;

void list_init( List *list);

ListNode* list_find( List *list, ListItem *item, int ( *equal_func)( ListItem *,ListItem *));

ListNode* list_insert( ListNode *node, ListItem *item);
ListNode* list_push_back( List *list, ListItem *item);
ListNode* list_push_front( List *list, ListItem *item);

ListItem* list_erase( ListNode *node);
ListItem* list_pop_back( List *list);
ListItem* list_pop_front( List *list);


#endif
