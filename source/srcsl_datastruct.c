#include "include/srcsl_datastruct.h"

#include <stddef.h>
#include <stdlib.h>

//������ʼ��
void srcsl_vector_init( SrcslVector *vector, SrcslMemMang *mem)
{
	vector->mem = mem;

    vector->item_space = ( void**)srcsl_malloc( mem, sizeof( void*) * (uint32_t)(SRCSL_VECTOR_INITIAL_CAPACITY));
    vector->capacity = SRCSL_VECTOR_INITIAL_CAPACITY;
    vector->size = 0;
}


//�����в�����Ŀ����ȵ���
uint32_t srcsl_vector_find( SrcslVector *vector, void *item, int ( *compare_func)( void *,void *))
{
    uint32_t index;
    for( index = 0; index < vector->size; ++index)
        if( compare_func( vector->item_space[index], item) == 0)
            return index;
	return index;
}


//������ָ��λ�ò�����
int srcsl_vector_insert( SrcslVector *vector, void *item, uint32_t index)
{
    uint32_t temp;
    
	//����Խ��
    if( index > vector->size)
        return SRCSL_VECTOR_INSERT_OUTOFRANGE;

    ++vector->size;
	//����������
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
		//���ݺ���
		for( temp = vector->size - 1; temp > index; --temp)
		{
			vector->item_space[temp] = vector->item_space[temp-1];
		}
		
	}
	vector->item_space[index] = item;

    return SRCSL_VECTOR_INSERT_SUCCESS;
}

//������ĩβ������
int srcsl_vector_push_back( SrcslVector *vector, void *item)
{
    return srcsl_vector_insert( vector, item, vector->size);
}

//�������Ŀ�ͷ������
int srcsl_vector_push_front( SrcslVector *vector, void *item)
{
    return srcsl_vector_insert( vector, item, 0);
}


//�Ƴ�������ָ��λ�õ���
void* srcsl_vector_erase( SrcslVector *vector, uint32_t index)
{
	//���汻����Ԫ��λ�õ����ݵ�ָ��
    void *item = vector->item_space[index];
	//λ�ó�������ʵ�ʴ�С
    if( index >= vector->size)
        return NULL;
    
	//����ǰ�ƣ�������������
    for(; index < vector->size - 1; ++index)
    {
        vector->item_space[index] = vector->item_space[index + 1];
    } 
    --vector->size;
    return item;
}


//�Ƴ����������һ��
void* srcsl_vector_pop_back( SrcslVector *vector)
{
    return srcsl_vector_erase( vector, vector->size - 1);
}


//�Ƴ������еĵ�һ��
void* srcsl_vector_pop_front( SrcslVector *vector)
{
    return srcsl_vector_erase( vector, 0);
}


//��ȡ�����Ĵ�С
uint32_t srcsl_vector_size( SrcslVector *vector)
{
    return vector->size;
}


//�ж������Ƿ�Ϊ��
int srcsl_vector_empty( SrcslVector *vector)
{
    return vector->size == 0 ? 1 : 0;
}


//----------------------------------------------------------

//�����ʼ��
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

//Ѱ�������з�����������
SrcslListNode* srcsl_list_find(SrcslList *list, void *item, int(*equal_func)(void *, void *))
{
	SrcslListNode *node = list->nil->next;
	while (node != list->nil && equal_func(node->item, item) != 0)
	{
		node = node->next;
	}
	return node;
}


//������ָ��λ�ú����
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


//������ĩβ�����
SrcslListNode* srcsl_list_push_back(SrcslList *list, void *item)
{
	return srcsl_list_insert(list, list->nil->prev, item);
}


//������ͷ�����
SrcslListNode* srcsl_list_push_front(SrcslList *list, void *item)
{
	return srcsl_list_insert(list, list->nil, item);
}



//�Ƴ�������ָ���Ľڵ�
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


//�Ƴ���������һ��
void* srcsl_list_pop_back(SrcslList *list)
{
	return srcsl_list_erase(list, list->nil->prev);
}


//�Ƴ�����ĵ�һ��
void* srcsl_list_pop_front(SrcslList *list)
{
	return srcsl_list_erase(list, list->nil->next);
}



//��ȡ�����е��±�ӦΪindex�Ľڵ�
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



//��ȡ������
int32_t srcsl_list_get_length(SrcslList * list)
{
	return list->length;
}

