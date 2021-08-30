#ifndef SRCSL_DATASTRUCT_H_INCLUDED
#define SRCSL_DATASTRUCT_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

#include "srcsl_memmang.h"


enum SRCSL_VECTOR_INSERT
{
	SRCSL_VECTOR_INSERT_SUCCESS,			//!< ��������ɹ�
	SRCSL_VECTOR_INSERT_OUTOFRANGE,			//!< ���������±�Խ��
	SRCSL_VECTOR_INSERT_EXPANSION_FAIL		//!< ������������ʧ��
};


///����
typedef struct
{
	SrcslMemMang *mem;						//!< ʹ�õ��ڴ��

    void **item_space;						//!< ���ָ�������

    uint32_t size;							//!< ������С
    uint32_t capacity;						//!< ��������
} SrcslVector;


/**
* @brief ������ʼ��
* @param *vector	����ʵ����ָ��
* @param *mem		ʹ�õ��ڴ����ģ��ʵ����ָ��
*/
void srcsl_vector_init( SrcslVector *vector, SrcslMemMang *mem);

/**
* @brief �����в�����Ŀ����ȵ���
* @param *vector		����ʵ����ָ��
* @param *item			�����ҵ���
* @param *compare_func	�ȽϺ���
* @return ��������Ŀ����ȵ�����±�
*/
uint32_t srcsl_vector_find( SrcslVector *vector, void *item, int ( *compare_func)( void *,void *));

/**
* @brief ������ָ��λ�ò�����
* @param *vector	����ʵ����ָ��
* @param *item		���������
* @param index		�������λ��
* @return �������
* @retval SRCSL_VECTOR_INSERT_SUCCESS			��������ɹ�
* @retval SRCSL_VECTOR_INSERT_OUTOFRANGE		���������±�Խ��
* @retval SRCSL_VECTOR_INSERT_EXPANSION_FAIL	������������ʧ��
*/
int srcsl_vector_insert( SrcslVector *vector, void *item, uint32_t index);

/**
* @brief ������ĩβ������
* @param *vector	����ʵ����ָ��
* @param *item		���������
* @return �������
*/
int srcsl_vector_push_back( SrcslVector *vector, void *item);

/**
* @brief �������Ŀ�ͷ������
* @param *vector	����ʵ����ָ��
* @param *item		���������
* @return �������
*/
int srcsl_vector_push_front( SrcslVector *vector, void *item);

/**
* @brief �Ƴ�������ָ��λ�õ���
* @param *vector	����ʵ����ָ��
* @param index		���Ƴ������λ��
* @return ��������������ݵ�ָ��
*/
void* srcsl_vector_erase( SrcslVector *vector, uint32_t index);

/**
* @brief �Ƴ����������һ��
* @param *vector	����ʵ����ָ��
* @return ��������������ݵ�ָ��
*/
void* srcsl_vector_pop_back( SrcslVector *vector);

/**
* @brief �Ƴ������еĵ�һ��
* @param *vector	����ʵ����ָ��
* @return ��������������ݵ�ָ��
*/
void* srcsl_vector_pop_front( SrcslVector *vector);

/**
* @brief ��ȡ�����Ĵ�С
* @param *vector	����ʵ����ָ��
* @return �����Ĵ�С
*/
uint32_t srcsl_vector_size( SrcslVector *vector);

/**
* @brief �ж������Ƿ�Ϊ��
* @param *vector	����ʵ����ָ��
* @return
*/
int srcsl_vector_empty( SrcslVector *vector);





//------------------------------------------------------------

///˫������Ľڵ�
typedef struct SrcslListNode
{
	struct SrcslListNode *prev;		//!< ��һ�ڵ�
	struct SrcslListNode *next;		//!< ��һ�ڵ�

	void *item;						//!< ��ǰ�ڵ�����
} SrcslListNode;


///˫������
typedef struct
{
	SrcslMemMang *mem;				//!< ʹ�õ��ڴ��

	SrcslListNode *nil;				//!< �ڱ��ڵ㣨��һ��Ϊ��һ���һ��Ϊ���һ�
	int32_t length;					//!< ������
} SrcslList;

/**
* @brief �����ʼ��
* @param *list	����ʵ����ָ��
* @param *mem	ʹ�õ��ڴ����ģ��ʵ����ָ��
*/
void srcsl_list_init(SrcslList *list, SrcslMemMang *mem);

/**
* @brief Ѱ�������з�����������
* @param *list			����ʵ����ָ��
* @param *item			�Ƚ�����
* @param *equal_func	�ȽϺ���
* @return ������������
*/
SrcslListNode* srcsl_list_find(SrcslList *list, void *item, int(*equal_func)(void *, void *));

/**
* @brief ������ָ��λ�ú����
* @param *list	����ʵ����ָ��
* @param *node	������Ľڵ�λ�õ���һ���ڵ�
* @param *item	�����������
* @return ����Ľڵ�
*/
SrcslListNode* srcsl_list_insert(SrcslList *list, SrcslListNode *node, void *item);

/**
* @brief ������ĩβ�����
* @param *list	����ʵ����ָ��
* @param *item	�����������
* @return �������
*/
SrcslListNode* srcsl_list_push_back(SrcslList *list, void *item);

/**
* @brief ������ͷ�����
* @param *list	����ʵ����ָ��
* @param *item	�����������
* @return �������
*/
SrcslListNode* srcsl_list_push_front(SrcslList *list, void *item);

/**
* @brief �Ƴ�������ָ���Ľڵ�
* @param *list	����ʵ����ָ��
* @param *node	���Ƴ��Ľڵ�
* @return ���Ƴ��ڵ�����ݣ����з���Ŀռ䣬Ӧ���������
*/
void* srcsl_list_erase(SrcslList *list, SrcslListNode *node);

/**
* @brief �Ƴ���������һ��
* @param *list	����ʵ����ָ��
* @return ���Ƴ��ڵ������
*/
void* srcsl_list_pop_back(SrcslList *list);

/**
* @brief �Ƴ�����ĵ�һ��
* @param *list	����ʵ����ָ��
* @return ���Ƴ��ڵ������
*/
void* srcsl_list_pop_front(SrcslList *list);

/**
* @brief ��ȡ�����е��±�ӦΪindex�Ľڵ�
* @param *list	����ʵ����ָ��
* @param index	�±꣨��0��ʼ��
* @return Ŀ��ڵ�
*/
SrcslListNode* srcsl_list_get(SrcslList *list, int32_t index);

/**
* @brief ��ȡ������
* @param *list ����ʵ����ָ��
* @return ����ĳ���
*/
int32_t srcsl_list_get_length(SrcslList *list);


#ifdef __cplusplus
}
#endif


#endif

