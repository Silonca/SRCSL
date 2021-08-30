#include "include/srcsl_datastruct.h"

#include <stddef.h>
#include <stdlib.h>

//向量初始化
void srcsl_vector_init( SrcslVector *vector, SrcslMemMang *mem)
{
	vector->mem = mem;

    vector->item_space = ( void**)srcsl_malloc( mem, sizeof( void*) * (uint32_t)(SRCSL_VECTOR_INITIAL_CAPACITY));
    vector->capacity = SRCSL_VECTOR_INITIAL_CAPACITY;
    vector->size = 0;
}


//向量中查找与目标相等的项
uint32_t srcsl_vector_find( SrcslVector *vector, void *item, int ( *compare_func)( void *,void *))
{
    uint32_t index;
    for( index = 0; index < vector->size; ++index)
        if( compare_func( vector->item_space[index], item) == 0)
            return index;
	return index;
}


//向量中指定位置插入项
int srcsl_vector_insert( SrcslVector *vector, void *item, uint32_t index)
{
    uint32_t temp;
    
	//请求越界
    if( index > vector->size)
        return SRCSL_VECTOR_INSERT_OUTOFRANGE;

    ++vector->size;
	//超容量扩容
    if(  vector->size >= vector->capacity)
    {
		void **p = ( void**)srcsl_realloc( vector->mem, vector->item_space, sizeof( void*) * vector->capacity *2);
        if( vector->item_space == NULL)
            return SRCSL_VECTOR_INSERT_EXPANSION_FAIL;
		vector->item_space = p;
		vector->capacity *= 2;
    }

	if (vector->size > 1 )
	{
		//数据后移
		for( temp = vector->size - 1; temp > index; --temp)
		{
			vector->item_space[temp] = vector->item_space[temp-1];
		}
		
	}
	vector->item_space[index] = item;

    return SRCSL_VECTOR_INSERT_SUCCESS;
}

//在向量末尾插入项
int srcsl_vector_push_back( SrcslVector *vector, void *item)
{
    return srcsl_vector_insert( vector, item, vector->size);
}

//在向量的开头插入项
int srcsl_vector_push_front( SrcslVector *vector, void *item)
{
    return srcsl_vector_insert( vector, item, 0);
}


//移除向量中指定位置的项
void* srcsl_vector_erase( SrcslVector *vector, uint32_t index)
{
	//保存被覆盖元素位置的内容的指针
    void *item = vector->item_space[index];
	//位置超过向量实际大小
    if( index >= vector->size)
        return NULL;
    
	//数据前移，覆盖欲擦除项
    for(; index < vector->size - 1; ++index)
    {
        vector->item_space[index] = vector->item_space[index + 1];
    } 
    --vector->size;
    return item;
}


//移除向量中最后一项
void* srcsl_vector_pop_back( SrcslVector *vector)
{
    return srcsl_vector_erase( vector, vector->size - 1);
}


//移除向量中的第一项
void* srcsl_vector_pop_front( SrcslVector *vector)
{
    return srcsl_vector_erase( vector, 0);
}


//获取向量的大小
uint32_t srcsl_vector_size( SrcslVector *vector)
{
    return vector->size;
}


//判断向量是否为空
int srcsl_vector_empty( SrcslVector *vector)
{
    return vector->size == 0 ? 1 : 0;
}


//----------------------------------------------------------

//链表初始化
void srcsl_list_init(SrcslList *list, SrcslMemMang *mem)
{
	list->mem = mem;
	list->length = 0;

	list->nil = (SrcslListNode*)srcsl_malloc(mem, sizeof(SrcslListNode));
	if (list->nil == NULL)
		return;
	list->nil->item = NULL;
	list->nil->next = list->nil;
	list->nil->prev = list->nil;
}

//寻找链表中符合条件的项
SrcslListNode* srcsl_list_find(SrcslList *list, void *item, int(*equal_func)(void *, void *))
{
	SrcslListNode *node = list->nil->next;
	while (node != list->nil && equal_func(node->item, item) != 0)
	{
		node = node->next;
	}
	return node;
}


//在链表指定位置后插入
SrcslListNode* srcsl_list_insert(SrcslList *list, SrcslListNode *node, void *item)
{
	SrcslListNode *next = (SrcslListNode*)srcsl_malloc(list->mem, sizeof(SrcslListNode));
	if (next == NULL)
		return next;
	next->item = item;
	next->prev = node;
	next->next = node->next;
	

	next->next->prev = next;
	next->prev->next = next;
	
	/*node->next = next;
	if (next->next == list->nil) {
		list->nil->prev = next;
	}*/

	++list->length;

	return next;
}


//在链表末尾添加项
SrcslListNode* srcsl_list_push_back(SrcslList *list, void *item)
{
	return srcsl_list_insert(list, list->nil->prev, item);
}


//在链表开头添加项
SrcslListNode* srcsl_list_push_front(SrcslList *list, void *item)
{
	return srcsl_list_insert(list, list->nil, item);
}



//移除链表中指定的节点
void* srcsl_list_erase(SrcslList *list, SrcslListNode *node)
{
	void *item = NULL;

	if (node == list->nil || node == NULL)
		return NULL;

	item = node->item;

	node->prev->next = node->next;
	node->next->prev = node->prev;

	--list->length;
	srcsl_free(list->mem, node);

	return item;
}


//移除链表的最后一项
void* srcsl_list_pop_back(SrcslList *list)
{
	return srcsl_list_erase(list, list->nil->prev);
}


//移除链表的第一项
void* srcsl_list_pop_front(SrcslList *list)
{
	return srcsl_list_erase(list, list->nil->next);
}



//获取链表中的下标应为index的节点
SrcslListNode * srcsl_list_get(SrcslList * list, int32_t index)
{
	int32_t a = 0;
	SrcslListNode *node = list->nil;
	if (index == 0 || abs(index) > srcsl_list_get_length(list))
		return node;
	while (a != index)
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



//获取链表长度
int32_t srcsl_list_get_length(SrcslList * list)
{
	return list->length;
}

