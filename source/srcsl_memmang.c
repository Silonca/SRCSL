/**
* @file srcsl_memmang.c
* @brief �����ڴ���������ڵ�Ƭ���������׼�ڴ����������߶��ڴ�Ŀ���
* @author Silonca
*/
#include "include/srcsl_memmang.h"

#include <stdlib.h>

//�ڴ�����ܳ�ʼ��
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

//�ڴ���亯�����������malloc
void * srcsl_malloc(SrcslMemMang * m, unsigned int size)
{
	uint8_t *address;
	//û��ָ���Ŀռ��ִ����ͨ�ķ��亯��
	if (m == NULL) {
		address = (uint8_t*)malloc(size);
		return address;
	}
	//ȫ��ʱ�ķ���
	if ((uint8_t*)m->start == m->base && m->consumption == 0)
	{
		//����ռ��С�Ϸ��Լ��
		if (size + sizeof(SrcslMemBlock) > m->size)
			return NULL;
		m->start->next = NULL;
		m->start->size = size;
		m->consumption += sizeof(SrcslMemBlock) + size;	//ͳ�ƿռ�ʹ����
		return (uint8_t*)m->start + sizeof(SrcslMemBlock);
	}
	//��鿪ͷ�����Ƿ���ڿ��ÿ��п鲢���䣨��һ��ǰ��
	if ((uint8_t*)m->start != m->base && (unsigned int)((uint8_t*)m->start - m->base) > sizeof(SrcslMemBlock) + size)
	{
		uint8_t *temp = (uint8_t*)m->start;
		(uint8_t*)m->start = m->base;
		m->start->next = temp;
		m->start->size = size;
		m->consumption += sizeof(SrcslMemBlock) + size;	//ͳ�ƿռ�ʹ����
		return (uint8_t*)m->start + sizeof(SrcslMemBlock);
	}
	//Ѱ�ҿ����п飨�״���Ӧ�㷨��
	for (address = (uint8_t*)m->start;
		((SrcslMemBlock*)address)->next != NULL &&
		((SrcslMemBlock*)address)->next < (uint8_t*)address 
		+ sizeof(SrcslMemBlock) + ((SrcslMemBlock*)address)->size + sizeof(SrcslMemBlock) + size;
		address = ((SrcslMemBlock*)address)->next);

	//����޿��п�,���ĩβ�Ƿ��㹻����
	if (((SrcslMemBlock*)address)->next == NULL)
	{
		uint8_t *new_address = (uint8_t*)(address)+sizeof(SrcslMemBlock) + ((SrcslMemBlock*)address)->size;
		//��Χ�Ϸ��Լ��
		if (new_address + sizeof(SrcslMemBlock) + size > m->base + m->size)
			return NULL;

		((SrcslMemBlock*)address)->next = new_address;
		((SrcslMemBlock*)address) = (SrcslMemBlock*)((SrcslMemBlock*)address)->next;
		((SrcslMemBlock*)address)->next = NULL;
		((SrcslMemBlock*)address)->size = size;

		m->end = (SrcslMemBlock*)address;						//����β��ָ��
		m->consumption += sizeof(SrcslMemBlock) + size;			//ͳ�ƿռ�ʹ����

		return (uint8_t*)address + sizeof(SrcslMemBlock);
	}
	else
	{
		//����п��ÿ��п�
		uint8_t *temp = ((SrcslMemBlock*)address)->next;
		((SrcslMemBlock*)address)->next = (address) + sizeof(SrcslMemBlock) + ((SrcslMemBlock*)address)->size;
		((SrcslMemBlock*)address) = (SrcslMemBlock*)((SrcslMemBlock*)address)->next;
		((SrcslMemBlock*)address)->next = temp;
		((SrcslMemBlock*)address)->size = size;

		m->consumption += sizeof(SrcslMemBlock) + size;	//ͳ�ƿռ�ʹ����

		return (uint8_t*)address + sizeof(SrcslMemBlock);
	}
	
	
}


//�ڴ��ط��亯����ʵ���������ģ��������realloc
void * srcsl_realloc(SrcslMemMang * m, void * pre, unsigned int size)
{
	uint8_t *pr = (uint8_t*)pre - sizeof(SrcslMemBlock);
	//û��ָ���Ŀռ��ִ����ͨ���ط��亯��
	if (m == NULL) {
		void *temp = realloc( pre, size);
		if (temp != NULL)
		{
			pre = temp;
			return pre;
		}
		else return NULL;
	}

	//��С����
	if (size < ((SrcslMemBlock*)pr)->size)
	{
		m->consumption -= ((SrcslMemBlock*)pr)->size - size;
		((SrcslMemBlock*)pr)->size = size;

		return pre;
	}

	//��������
	//���˿������ŵĿ��ռ��Ƿ�������������
	if (((SrcslMemBlock*)pre)->next > (uint8_t*)pr + sizeof(SrcslMemBlock) + size)
	{
		m->consumption += size - ((SrcslMemBlock*)pr)->size;
		((SrcslMemBlock*)pre)->size = size;

		return pre;
	}
	else 
	{
		//�������

		uint8_t *temp = (uint8_t*)srcsl_malloc(m, size);
		unsigned int i;
		//����ʧ��
		if (temp == NULL) 
			return NULL;
		//ת������
		for (i = 0; i < ((SrcslMemBlock*)pr)->size; ++i)
			temp[i] = ((uint8_t*)pr)[i];
		srcsl_free(m, pre);
		pre = temp;

		return pre;
	}

	
}


//�ڴ��ͷź������������free
void srcsl_free(SrcslMemMang * m, void * p)
{
	SrcslMemBlock *temp;
	uint8_t *pr = (uint8_t*)p - sizeof(SrcslMemBlock);
	
	//û��ָ���Ŀռ��ִ����ͨ���ͷź���
	if (m == NULL) {
		free(p);
		p = NULL;
		return ;
	}

	//����ַ�Ϸ���
	if ((uint8_t*)pr > m->base + m->size || (uint8_t*)pr < m->base)
	{
		//������
	}
	//�ͷ�Ŀ��飨�׿飩
	if (pr == m->start)
	{
		m->start = (SrcslMemBlock*)m->start->next;
		m->consumption -= sizeof(SrcslMemBlock) + ((SrcslMemBlock*)pr)->size;
		return ;
	}

	//Ѱ��Ŀ������һ��
	for (temp = m->start; (uint8_t*)temp->next != NULL; temp = (SrcslMemBlock*)temp->next)
	{
		if ((uint8_t*)temp->next == pr) 
		{
			//�ͷ�Ŀ��飨��Ŀ������һ������һ��������
			m->consumption -= ((SrcslMemBlock*)pr)->size + sizeof(SrcslMemBlock);
			temp->next = (SrcslMemBlock*)((SrcslMemBlock*)temp->next)->next;
			break;
		}
	}
	//δ�ҵ�Ŀ������һ�飬˵������������ָ�벻����srcsl_malloc������
	if ((uint8_t*)temp->next == NULL) 
	{
		//������
	}

}

//��ȡ�ڴ�ռ�ʹ����
float srcsl_get_usage(SrcslMemMang * m)
{
	//��ָ���ռ䣬�޷���֪ʹ�����
	if (m == NULL) {
		return 0;
	}
	return (float)m->consumption / (float)m->size;
}


