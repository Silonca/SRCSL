#include <stdio.h>
#include <stdlib.h>

#include "include/srcsl_memmang.h"

static uint8_t space[200];
SrcslMemMang m;

static void memshow()
{
	printf("mem:\n     ");
	for (int b = 0; b < 10; ++b) {
		printf("%4d", b);
	}
	printf("\n\n");
	for (int a = 0; a < sizeof(space) / 10; ++a) {
		printf("%4d:", a);
		for (int b = 0; b < 10; ++b) {
			printf("%4x", space[a * 10 + b]);
		}
		printf("\n");
	}
	printf("usage:%3.2f%%\n", srcsl_get_usage(&m)*100);
	printf("-------------------------------------------------------\n");
}

static int cnt = 0;

static uint8_t* memin(int size) {
	cnt++;
	printf("malloc size:%d,cnt:%d\n", size,cnt);
	uint8_t *temp = (uint8_t*)srcsl_malloc(&m, sizeof(uint8_t)*size);
	if (temp == NULL) {
		printf("insert fail\n");
		return NULL;
	}
	for (int a = 0; a < size; ++a) {
		temp[a] = cnt;
	}
	return temp;
}

static uint8_t* memrein(uint8_t *mem,int size) {

	cnt++;
	printf("realloc size:%d,cnt:%d\n", size,cnt);
	uint8_t *temp = (uint8_t*)srcsl_realloc(&m, mem, sizeof(uint8_t)*size);
	if (temp == NULL) {
		printf("reinsert fail\n");
		return NULL;
	}
	for (int a = 0; a < size; ++a) {
		temp[a] = cnt;
	}
	return temp;
}

int test_memmang(void)
{

	for (int a = 0; a < sizeof(space); ++a) {
		space[a] = 0;
	}
	srcsl_memmang_init(&m, space, 200);

	memin(200);
	memshow();

	uint8_t *q = memin(30);
	memshow();

	uint8_t *w = memin(20);
	memshow();
	uint8_t *e = memin(10);
	memshow();
	uint8_t *r = memin(30);
	memshow();
	srcsl_free(&m, e);
	printf("free e\n");
	memshow();
	memrein(w, 30);
	memshow();
	memrein(w, 5);
	memshow();
	uint8_t *t = memin(10);
	memshow();

	uint8_t *y = memin(50);
	memshow();

	uint8_t *u = memin(60);
	memshow();

	memrein(y, 60);
	memshow();

	srcsl_free(&m, y);
	printf("free y\n");
	memshow();

	uint8_t *i = memin(30);
	memshow();

	srcsl_free(&m, q);
	printf("free q\n");
	memshow();
	q = memin(5);
	memshow();
	uint8_t *o = memin(5);
	memshow();
	uint8_t *qq = memin(10);
	memshow();
}

