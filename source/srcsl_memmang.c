/**
* @file srcsl_memmang.c
* @brief 简易内存管理，用于在单片机中替代标准内存管理函数，提高对内存的控制
* @author Silonca
*/
#include "include/srcsl_memmang.h"

#include <stdlib.h>

//内存管理功能初始化
void srcsl_memmang_init(SrcslMemMang * m, uint8_t * base, unsigned int size)
{
	m->base = base;
	m->size = size;
	m->end = (SrcslMemBlock*) base;
	m->start = (SrcslMemBlock*)base;
	m->start->next = NULL;
	m->start->size = 0;
	m->consumption = 0;
}

//内存分配函数，用于替代malloc
void * srcsl_malloc(SrcslMemMang * m, unsigned int size)
{
	uint8_t *address;
	//没有指定的空间就执行普通的分配函数
	if (m == NULL) {
		address = (uint8_t*)malloc(size);
		return address;
	}
	//全空时的分配
	if ((uint8_t*)m->start == m->base && m->consumption == 0)
	{
		//申请空间大小合法性检测
		if (size + sizeof(SrcslMemBlock) > m->size)
			return NULL;
		m->start->next = NULL;
		m->start->size = size;
		m->consumption += sizeof(SrcslMemBlock) + size;	//统计空间使用量
		return (uint8_t*)m->start + sizeof(SrcslMemBlock);
	}
	//检查开头部分是否存在可用空闲块并分配（第一块前）
	if ((uint8_t*)m->start != m->base && (unsigned int)((uint8_t*)m->start - m->base) > sizeof(SrcslMemBlock) + size)
	{
		uint8_t *temp = (uint8_t*)m->start;
		(uint8_t*)m->start = m->base;
		m->start->next = temp;
		m->start->size = size;
		m->consumption += sizeof(SrcslMemBlock) + size;	//统计空间使用量
		return (uint8_t*)m->start + sizeof(SrcslMemBlock);
	}
	//寻找块间空闲块（首次适应算法）
	for (address = (uint8_t*)m->start;
		((SrcslMemBlock*)address)->next != NULL &&
		((SrcslMemBlock*)address)->next < (uint8_t*)address 
		+ sizeof(SrcslMemBlock) + ((SrcslMemBlock*)address)->size + sizeof(SrcslMemBlock) + size;
		address = ((SrcslMemBlock*)address)->next);

	//块间无空闲块,检测末尾是否足够空闲
	if (((SrcslMemBlock*)address)->next == NULL)
	{
		uint8_t *new_address = (uint8_t*)(address)+sizeof(SrcslMemBlock) + ((SrcslMemBlock*)address)->size;
		//范围合法性检测
		if (new_address + sizeof(SrcslMemBlock) + size > m->base + m->size)
			return NULL;

		((SrcslMemBlock*)address)->next = new_address;
		((SrcslMemBlock*)address) = (SrcslMemBlock*)((SrcslMemBlock*)address)->next;
		((SrcslMemBlock*)address)->next = NULL;
		((SrcslMemBlock*)address)->size = size;

		m->end = (SrcslMemBlock*)address;						//设置尾部指针
		m->consumption += sizeof(SrcslMemBlock) + size;			//统计空间使用量

		return (uint8_t*)address + sizeof(SrcslMemBlock);
	}
	else
	{
		//块间有可用空闲块
		uint8_t *temp = ((SrcslMemBlock*)address)->next;
		((SrcslMemBlock*)address)->next = (address) + sizeof(SrcslMemBlock) + ((SrcslMemBlock*)address)->size;
		((SrcslMemBlock*)address) = (SrcslMemBlock*)((SrcslMemBlock*)address)->next;
		((SrcslMemBlock*)address)->next = temp;
		((SrcslMemBlock*)address)->size = size;

		m->consumption += sizeof(SrcslMemBlock) + size;	//统计空间使用量

		return (uint8_t*)address + sizeof(SrcslMemBlock);
	}
	
	
}


//内存重分配函数，实现容量更改，用于替代realloc
void * srcsl_realloc(SrcslMemMang * m, void * pre, unsigned int size)
{
	uint8_t *pr = (uint8_t*)pre - sizeof(SrcslMemBlock);
	//没有指定的空间就执行普通的重分配函数
	if (m == NULL) {
		void *temp = realloc( pre, size);
		if (temp != NULL)
		{
			pre = temp;
			return pre;
		}
		else return NULL;
	}

	//减小容量
	if (size < ((SrcslMemBlock*)pr)->size)
	{
		m->consumption -= ((SrcslMemBlock*)pr)->size - size;
		((SrcslMemBlock*)pr)->size = size;

		return pre;
	}

	//扩大容量
	//检测此块后紧接着的块间空间是否满足扩容条件
	if (((SrcslMemBlock*)pre)->next > (uint8_t*)pr + sizeof(SrcslMemBlock) + size)
	{
		m->consumption += size - ((SrcslMemBlock*)pr)->size;
		((SrcslMemBlock*)pre)->size = size;

		return pre;
	}
	else 
	{
		//异地扩容

		uint8_t *temp = (uint8_t*)srcsl_malloc(m, size);
		unsigned int i;
		//扩容失败
		if (temp == NULL) 
			return NULL;
		//转移数据
		for (i = 0; i < ((SrcslMemBlock*)pr)->size; ++i)
			temp[i] = ((uint8_t*)pr)[i];
		srcsl_free(m, pre);
		pre = temp;

		return pre;
	}

	
}


//内存释放函数，用于替代free
void srcsl_free(SrcslMemMang * m, void * p)
{
	SrcslMemBlock *temp;
	uint8_t *pr = (uint8_t*)p - sizeof(SrcslMemBlock);
	
	//没有指定的空间就执行普通的释放函数
	if (m == NULL) {
		free(p);
		p = NULL;
		return ;
	}

	//检测地址合法性
	if ((uint8_t*)pr > m->base + m->size || (uint8_t*)pr < m->base)
	{
		//错误处理
	}
	//释放目标块（首块）
	if (pr == m->start)
	{
		m->start = (SrcslMemBlock*)m->start->next;
		m->consumption -= sizeof(SrcslMemBlock) + ((SrcslMemBlock*)pr)->size;
		return ;
	}

	//寻找目标块的上一块
	for (temp = m->start; (uint8_t*)temp->next != NULL; temp = (SrcslMemBlock*)temp->next)
	{
		if ((uint8_t*)temp->next == pr) 
		{
			//释放目标块（将目标块的上一块与下一块相连）
			m->consumption -= ((SrcslMemBlock*)pr)->size + sizeof(SrcslMemBlock);
			temp->next = (SrcslMemBlock*)((SrcslMemBlock*)temp->next)->next;
			break;
		}
	}
	//未找到目标块的上一块，说明参数给出的指针不是由srcsl_malloc产生的
	if ((uint8_t*)temp->next == NULL) 
	{
		//错误处理
	}

}

//获取内存空间使用率
float srcsl_get_usage(SrcslMemMang * m)
{
	//非指定空间，无法得知使用情况
	if (m == NULL) {
		return 0;
	}
	return (float)m->consumption / (float)m->size;
}


