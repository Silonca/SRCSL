#ifndef SRCSL_MEMMANG_H_INCLUDED
#define SRCSL_MEMMANG_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "srcslsys.h"

typedef struct SrcslMemBlock
{
	uint8_t *next;						//!< 下一块的指针
	unsigned int size;					//!< 当前块的大小
} SrcslMemBlock;

typedef struct SrcslMemMang
{
	uint8_t *base;						//!< 基址
	unsigned int size;					//!< 总大小
										  
	SrcslMemBlock *start;				//!< 指向第一块的指针
	SrcslMemBlock *end;					//!< 指向最后一块的指针
										  
	unsigned int consumption;			//!< 使用量
} SrcslMemMang;


/**
* @brief 内存管理功能初始化
* @param *m		内存管理结构体指针
* @param *base	内存空间指针，由用户通过uint8_t数组形式建立并传入
* @paramm size	内存空间大小，即用户自建数组的大小
*/
void srcsl_memmang_init(SrcslMemMang *m, uint8_t *base, unsigned int size);


/**
* @brief 内存分配函数，用于替代malloc
* @param *m		内存分配模块指针，若为NULL则调用malloc
* @param size	需要的内存大小（单位：字节）
* @return 分配的内存块，分配失败时返回NULL
*/
void* srcsl_malloc(SrcslMemMang *m, unsigned int size);

/**
* @brief 内存重分配函数，实现容量更改，用于替代realloc
* @attention 用法与realloc相同
* @param *m		内存分配模块指针，若为NULL则调用malloc
* @param *pre	要重新分配空间的内存块的指针
* @param size	需要的内存大小（单位：字节）
* @return 重新分配的内存块，分配失败时返回NULL
*/
void* srcsl_realloc(SrcslMemMang *m, void *pre, unsigned int size);

/**
* @brief 内存释放函数，用于替代free
* @param *m		内存分配模块指针，若为NULL则调用free
* @param *p		之前分配的内存块的指针
*/
void srcsl_free(SrcslMemMang *m, void *p);


/**
* @brief 获取内存空间使用率
* @param *m		内存分配模块指针，若为NULL则返回0
* @return 内存空间的使用率
*/
float srcsl_get_usage(SrcslMemMang *m);

#ifdef __cplusplus
}
#endif


#endif 

