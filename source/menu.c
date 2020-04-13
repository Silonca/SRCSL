#include "include/menu.h"

#include <string.h>
#include <stdlib.h>



struct ListItem
{
	MenuNode menu_node;
};




static void merge_list(MenuNode *menu_node)
{
	//have set
	if (menu_node->nil_using != NULL)
		return;

	menu_node->nil_using = (ListNode*)malloc(sizeof(ListNode));
	//set new nil
	menu_node->nil_using->next = menu_node->children.nil->next;
	menu_node->nil_using->prev = menu_node->items.nil->prev;
	menu_node->nil_using->item = NULL;
	//merge
	menu_node->children.nil->prev->next = menu_node->items.nil->next;
	menu_node->items.nil->next->prev = menu_node->children.nil->prev;
}

static ListNode* find_node(Menu *menu, ListNode *list_node, int index)
{
	int i = 0;
	ListNode *node = list_node;
	for (; i < abs(index); ++i)
	{
		if (node != menu->current_node->nil_using)
		{
			if (index > 0)
				node = node->next;
			else
				node = node->prev;
		}
		else
		{
			if (index > 0)
				node = menu->current_node->nil_using->prev;
			else
				node = menu->current_node->nil_using->next;
			break;
		}
	}
	return node;
}


void menu_init( Menu *menu, uint8_t str_max_length)
{
    menu->root = ( MenuNode*)malloc( sizeof( MenuNode));
    list_init( &( menu->root->children));
	list_init(&(menu->root->items));
    menu->root->func = NULL;
    menu->root->parent = NULL;
    menu->root->index = 0;
    menu->root->str = "/";
    
    menu->current_node = menu->root;
    menu->window_rows = 0;
	menu->string_max_length = str_max_length;

}

static int menu_add_node(Menu *menu, List *list, char *name)
{
	ListItem *item = (ListItem*)malloc(sizeof(ListItem));
	item->menu_node.str = (char*)malloc(sizeof(char)*(menu->string_max_length));
	if (item->menu_node.str == NULL)
		return -1;
	strncpy(item->menu_node.str, name, menu->string_max_length);
	//item->menu_node.index = list->nil->prev->item->menu_node.index + 1;
	item->menu_node.func = NULL;
	item->menu_node.parent = &(list->nil->prev->item->menu_node);
	list_init(&(item->menu_node.children));
	list_init(&(item->menu_node.items));

	item->menu_node.nil_using = NULL;

	list_push_back( list, item);

	return 0;
}

int menu_set_path( Menu *menu, char *path)                      
{
    char *name = NULL;
	List *list = NULL;
	ListNode *list_node = NULL;
    
	list = &(menu->root->children);
	list_node = list->nil->next;
	
	//invalid path
	if (path == NULL)
		return -3;

    for( name = strtok( path, "/"); name != NULL; name = strtok( NULL, "/"))
    {
		//error string
		if (list_node->item->menu_node.str == NULL)
			return -4;

		//try to find
		for ( ; list_node != list->nil; list_node = list_node->next)
			if (strncmp(name, list_node->item->menu_node.str, menu->string_max_length) == 0)
				break;
		//do not exist, establish one
		if (list_node == list->nil)
		{
			menu_add_node(menu, list, name);
			list_node = list_get(list, -1);		//point to the new one
		}
		//get into the next layer
		list = &(list_node->item->menu_node.children);
		list_node = list->nil->next;
	
    }
	//set the found(or established) node as the current node 
	menu->current_node = &(list_node->item->menu_node);

	return 0;
}


int menu_add( Menu *menu, char *name, void (*func)(void))
{
	ListItem *item = NULL;
	if (func == NULL)
		return -1;
	if (name == NULL)
		return -2;

	item = (ListItem*)malloc(sizeof(ListItem));
	item->menu_node.str = (char*)malloc(sizeof(char)*(menu->string_max_length));
	if (item->menu_node.str == NULL)
		return -1;
	strncpy(item->menu_node.str, name, menu->string_max_length);
	//item->menu_node.index = menu->current_node->items;// ->nil->prev->item->menu_node.index + 1;
	item->menu_node.func = NULL;
	item->menu_node.parent = menu->current_node;
	list_init(&(item->menu_node.children));
	list_init(&(item->menu_node.items));
	item->menu_node.nil_using = NULL;

	list_push_back( &(menu->current_node->items), item);

    return 0;
}






void menu_ctrl_init(Menu * menu, uint8_t rows_num)
{
	menu->window_rows = rows_num;
	menu->current_node = menu->root;
	menu->display_first = menu->current_node->nil_using->next;
	menu->display_last = find_node(menu, menu->display_first, menu->window_rows);
	menu->display_index = 1;

	menu->window = (char*)malloc(sizeof(char) * menu->string_max_length * menu->window_rows);
	merge_list(menu->current_node);
}

void menu_home(Menu * menu)
{
	menu->current_node = menu->root;
	menu->display_first = menu->current_node->nil_using->next;
	menu->display_last = find_node(menu, menu->display_first, menu->window_rows);

	menu->display_index = 1;
}

void menu_back(Menu * menu)
{
	menu->current_node = menu->current_node->parent;
	menu->display_first = menu->current_node->nil_using->next;
	menu->display_last = find_node(menu, menu->display_first, menu->window_rows);
	menu->display_index = 1;
}

void menu_confirm(Menu * menu)
{
	if (menu->current_list_node->item->menu_node.func != NULL)
	{
		menu->current_list_node->item->menu_node.func();
		//do something to show having done sth.
		return;
	}
	menu->current_node = &(menu->current_list_node->item->menu_node);
	merge_list(menu->current_node);
	menu->display_first = menu->current_node->nil_using->next;
	menu->display_last = find_node(menu, menu->display_first, menu->window_rows);
	menu->display_index = 1;
}

void menu_up(Menu * menu)
{
	--menu->display_index;
	menu->current_list_node = menu->current_list_node->prev;

	//within the window and within the list
	if (menu->display_index > 0 && menu->current_list_node != menu->current_node->nil_using)
			return;

	//outside the window
	else
	{

		//reach the header
		if (menu->current_list_node == menu->current_node->children.nil)
		{
			//back to the end
			menu->display_last = menu->current_node->nil_using->prev;
			menu->display_first = find_node(menu, menu->display_last, -menu->window_rows);
			menu->display_index = menu->window_rows;
			return;
		}
		else
		{
			//move the window
			menu->display_first = menu->current_list_node;
			menu->display_last = menu->display_first->prev;
		}
		//set display_index
		menu->display_index = 1;
	}
}

void menu_down(Menu * menu)
{
	++menu->display_index;
	menu->current_list_node = menu->current_list_node->next;
	
	//within the window and within the list
	if (menu->display_index <= menu->window_rows && menu->current_list_node != menu->current_node->nil_using)
		return ;
	//outside the window
	else
	{
		//reach the end
		if(menu->current_list_node == menu->current_node->nil_using)
		{
			//back to header
			menu->display_first = menu->current_node->nil_using->next;
			menu->display_last = find_node(menu, menu->display_first, menu->window_rows);
			menu->display_index = 1;
			return;
		}
		else
		{
			//move the window
			menu->display_last = menu->current_list_node;
			menu->display_first = menu->display_first->next;
		}
		//set display_index
		menu->display_index = menu->window_rows;
	}
}


char* menu_out(Menu *menu)
{
	ListNode *node;
	if(menu->window == NULL)
		return NULL;
	menu->window = "";
	for (node = menu->display_first; node != menu->display_last; node = node->next)
	{
		strcat(menu->window, node->item->menu_node.str);
		strcat(menu->window, "\n");
	}
	return menu->window;
}
