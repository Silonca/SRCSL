#ifndef SRCSL_MENU_H_INCLUDED
#define SRCSL_MUNE_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

#include "list.h"

typedef struct MenuNode
{
	struct MenuNode *parent;
	List children;
	List items;
	ListNode *nil_using;

	void(*func)(void);
	int index;
	char *str;
} MenuNode;



typedef struct 
{
    MenuNode *root;

    MenuNode *current_node;			//like the current folder of the file system

	ListNode *current_list_node;	//like the selected subfolder or file of the file system


	ListNode *display_first;
	ListNode *display_last;
	uint8_t display_index;

	uint8_t window_rows;
	uint8_t string_max_length;
	char *window;
} Menu;

//establish menu
void menu_init( Menu *menu, uint8_t str_max_length);

int menu_set_path( Menu *menu, char *path);						//set path to add item,if the path doesn't exist,establish it
int menu_add( Menu *menu, char *child, void (*func)(void));		//add child item

//use menu
void menu_ctrl_init(Menu *menu, uint8_t rows_num);

void menu_home(Menu* menu);			//return to the root
void menu_back( Menu *menu);
void menu_confirm( Menu *menu);
void menu_up( Menu *menu);
void menu_down( Menu *menu);
char* menu_out( Menu *menu);

#ifdef __cplusplus
}
#endif

#endif 