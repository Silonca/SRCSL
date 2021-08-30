#ifndef SRCSL_DATASTRUCT_H_INCLUDED
#define SRCSL_DATASTRUCT_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

#include "srcsl_memmang.h"


enum SRCSL_VECTOR_INSERT
{
	SRCSL_VECTOR_INSERT_SUCCESS,			//!< 向量插入成功
	SRCSL_VECTOR_INSERT_OUTOFRANGE,			//!< 向量插入下标越界
	SRCSL_VECTOR_INSERT_EXPANSION_FAIL		//!< 向量插入扩容失败
};


///向量
typedef struct
{
	SrcslMemMang *mem;						//!< 使用的内存块

    void **item_space;						//!< 项的指针的数组

    uint32_t size;							//!< 向量大小
    uint32_t capacity;						//!< 向量容量
} SrcslVector;


/**
* @brief 向量初始化
* @param *vector	向量实例的指针
* @param *mem		使用的内存管理模块实例的指针
*/
void srcsl_vector_init( SrcslVector *vector, SrcslMemMang *mem);

/**
* @brief 向量中查找与目标相等的项
* @param *vector		向量实例的指针
* @param *item			欲查找的项
* @param *compare_func	比较函数
* @return 向量中与目标相等的项的下标
*/
uint32_t srcsl_vector_find( SrcslVector *vector, void *item, int ( *compare_func)( void *,void *));

/**
* @brief 向量中指定位置插入项
* @param *vector	向量实例的指针
* @param *item		欲插入的项
* @param index		欲插入的位置
* @return 插入情况
* @retval SRCSL_VECTOR_INSERT_SUCCESS			向量插入成功
* @retval SRCSL_VECTOR_INSERT_OUTOFRANGE		向量插入下标越界
* @retval SRCSL_VECTOR_INSERT_EXPANSION_FAIL	向量插入扩容失败
*/
int srcsl_vector_insert( SrcslVector *vector, void *item, uint32_t index);

/**
* @brief 在向量末尾插入项
* @param *vector	向量实例的指针
* @param *item		欲插入的项
* @return 插入情况
*/
int srcsl_vector_push_back( SrcslVector *vector, void *item);

/**
* @brief 在向量的开头插入项
* @param *vector	向量实例的指针
* @param *item		欲插入的项
* @return 插入情况
*/
int srcsl_vector_push_front( SrcslVector *vector, void *item);

/**
* @brief 移除向量中指定位置的项
* @param *vector	向量实例的指针
* @param index		欲移除的项的位置
* @return 被擦除的项的内容的指针
*/
void* srcsl_vector_erase( SrcslVector *vector, uint32_t index);

/**
* @brief 移除向量中最后一项
* @param *vector	向量实例的指针
* @return 被擦除的项的内容的指针
*/
void* srcsl_vector_pop_back( SrcslVector *vector);

/**
* @brief 移除向量中的第一项
* @param *vector	向量实例的指针
* @return 被擦除的项的内容的指针
*/
void* srcsl_vector_pop_front( SrcslVector *vector);

/**
* @brief 获取向量的大小
* @param *vector	向量实例的指针
* @return 向量的大小
*/
uint32_t srcsl_vector_size( SrcslVector *vector);

/**
* @brief 判断向量是否为空
* @param *vector	向量实例的指针
* @return
*/
int srcsl_vector_empty( SrcslVector *vector);





//------------------------------------------------------------

///双向链表的节点
typedef struct SrcslListNode
{
	struct SrcslListNode *prev;		//!< 上一节点
	struct SrcslListNode *next;		//!< 下一节点

	void *item;						//!< 当前节点内容
} SrcslListNode;


///双向链表
typedef struct
{
	SrcslMemMang *mem;				//!< 使用的内存块

	SrcslListNode *nil;				//!< 哨兵节点（下一项为第一项，上一项为最后一项）
	int32_t length;					//!< 链表长度
} SrcslList;

/**
* @brief 链表初始化
* @param *list	链表实例的指针
* @param *mem	使用的内存管理模块实例的指针
*/
void srcsl_list_init(SrcslList *list, SrcslMemMang *mem);

/**
* @brief 寻找链表中符合条件的项
* @param *list			链表实例的指针
* @param *item			比较内容
* @param *equal_func	比较函数
* @return 符合条件的项
*/
SrcslListNode* srcsl_list_find(SrcslList *list, void *item, int(*equal_func)(void *, void *));

/**
* @brief 在链表指定位置后插入
* @param *list	链表实例的指针
* @param *node	欲插入的节点位置的上一个节点
* @param *item	欲插入的内容
* @return 插入的节点
*/
SrcslListNode* srcsl_list_insert(SrcslList *list, SrcslListNode *node, void *item);

/**
* @brief 在链表末尾添加项
* @param *list	链表实例的指针
* @param *item	欲插入的内容
* @return 插入的项
*/
SrcslListNode* srcsl_list_push_back(SrcslList *list, void *item);

/**
* @brief 在链表开头添加项
* @param *list	链表实例的指针
* @param *item	欲插入的内容
* @return 插入的项
*/
SrcslListNode* srcsl_list_push_front(SrcslList *list, void *item);

/**
* @brief 移除链表中指定的节点
* @param *list	链表实例的指针
* @param *node	欲移除的节点
* @return 已移除节点的内容（自行分配的空间，应自行清除）
*/
void* srcsl_list_erase(SrcslList *list, SrcslListNode *node);

/**
* @brief 移除链表的最后一项
* @param *list	链表实例的指针
* @return 已移除节点的内容
*/
void* srcsl_list_pop_back(SrcslList *list);

/**
* @brief 移除链表的第一项
* @param *list	链表实例的指针
* @return 已移除节点的内容
*/
void* srcsl_list_pop_front(SrcslList *list);

/**
* @brief 获取链表中的下标应为index的节点
* @param *list	链表实例的指针
* @param index	下标（从0开始）
* @return 目标节点
*/
SrcslListNode* srcsl_list_get(SrcslList *list, int32_t index);

/**
* @brief 获取链表长度
* @param *list 链表实例的指针
* @return 链表的长度
*/
int32_t srcsl_list_get_length(SrcslList *list);


#ifdef __cplusplus
}
#endif


#endif

