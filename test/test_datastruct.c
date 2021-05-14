#include <stdio.h>
#include <stdlib.h>

#include "include/srcsl_datastruct.h"

void printvec(SrcslVector *vec)
{
	uint32_t size = srcsl_vector_size(vec);
	printf("size:%d,cap:%d\n", size,vec->capacity);
	for (int a = 0; a < size; ++a)
	{
		printf("index:%d,item:%d\n", a, *(int*)(vec->item_space[a]));
	}
}

int vec_comp(int *a, int *b) {
	return *a - *b;
}

void test_vector()
{
	SrcslVector vec;
	int *temp = NULL;
	srcsl_vector_init(&vec, NULL);

	printf("vector empty?%s\n", srcsl_vector_empty(&vec) == SRCSL_TRUE ? "yes": "no");

	//添加0~19
	for (int a = 0; a < 20; a++) {
		temp = malloc(sizeof(int));
		*temp = a;
		srcsl_vector_push_back(&vec, temp);
		printf("insert:%d\n", a);
	}
	printf("vector empty?%s\n", srcsl_vector_empty(&vec) == SRCSL_TRUE ? "yes": "no");
	printvec(&vec);

	//删去最后5个（15~19）
	for (int a = 0; a < 5; a++) {
		srcsl_vector_pop_back(&vec);
	}
	printvec(&vec);
	//删去前5个（0~4）
	for (int a = 0; a < 5; a++) {
		srcsl_vector_pop_front(&vec);
	}
	printvec(&vec);

	//在后面添加10个数字（100~109）
	for (int a = 0; a < 10; a++) {
		temp = malloc(sizeof(int));
		*temp = a+100;
		srcsl_vector_push_back(&vec, temp);
	}
	printvec(&vec);
	//在前面添加10个数字（200~209）
	for (int a = 0; a < 10; a++) {
		temp = malloc(sizeof(int));
		*temp = a + 200;
		srcsl_vector_push_front(&vec, temp);
	}
	printvec(&vec);
	//删去5~10位置的数字
	for (int a = 0; a < 5; a++) {
		srcsl_vector_erase(&vec, 5);
	}
	printvec(&vec);
	//在索引10的位置添加数字500
	temp = malloc(sizeof(int));
	*temp = 500;
	srcsl_vector_insert(&vec, temp, 10);
	printvec(&vec);
	//寻找500的位置
	printf("find 500 in index:%d\n", srcsl_vector_find(&vec, temp, vec_comp));
}



void printlist(SrcslList *list)
{
	SrcslListNode *node = list->nil->next;
	uint32_t size = srcsl_list_get_length(list);
	printf("size:%d\n", size);
	for (int a=0;node != list->nil; node = node->next,a++)
	{
		printf("index:%d,item:%d\n", a, *(int*)(node->item));
		//printf("%d,%d\n", a, *(int*)(srcsl_list_get(list, a+1)->item));
	}
}
void printlistr(SrcslList *list)
{
	SrcslListNode *node = list->nil->prev;
	uint32_t size = srcsl_list_get_length(list);
	printf("resize:%d\n", size);
	for (int a = 0; node != list->nil; node = node->prev, a++)
	{
		printf("reindex:%d,item:%d\n", a, *(int*)(node->item));
		//printf("%d,%d\n", a, *(int*)(srcsl_list_get(list, a+1)->item));
	}
}

int list_comp(int *a, int *b) {
	return *a - *b;
}

void test_list()
{
	SrcslList list;
	int *temp = NULL;
	srcsl_list_init(&list, NULL);

	//添加0~19
	for (int a = 0; a < 20; a++) {
		temp = malloc(sizeof(int));
		*temp = a;
		srcsl_list_push_back(&list, temp);
	}
	printlist(&list);
	printlistr(&list);

	//删去最后5个（15~19）
	for (int a = 0; a < 5; a++) {
		srcsl_list_pop_back(&list);
	}
	printlist(&list);
	//删去前5个（0~4）
	for (int a = 0; a < 5; a++) {
		srcsl_list_pop_front(&list);
	}
	printlist(&list);

	//在后面添加10个数字（100~109）
	for (int a = 0; a < 10; a++) {
		temp = malloc(sizeof(int));
		*temp = a + 100;
		srcsl_list_push_back(&list, temp);
	}
	printlist(&list);
	//在前面添加10个数字（200~209）
	for (int a = 0; a < 10; a++) {
		temp = malloc(sizeof(int));
		*temp = a + 200;
		srcsl_list_push_front(&list, temp);
	}
	printlist(&list);
	//删去第三个的数字
	srcsl_list_erase(&list, list.nil->next->next->next);
	printlist(&list);
	printlistr(&list);
	//在第三个位置添加数字500
	temp = malloc(sizeof(int));
	*temp = 500;
	srcsl_list_insert(&list, list.nil->next->next, temp);
	printlist(&list);
	//寻找500
	printf("find 500 in list:%s\n", srcsl_list_find(&list, temp, list_comp)!= NULL ? "yes" : "no");
	//获取index应为10的节点
	printf("index 10 :%d\n", *(int*)(srcsl_list_get(&list, 10+1)->item));
}