/**
* @file srcsl_menu.c
* @brief 简易的字符菜单
* @author Silonca
*/
#include "include/srcsl_menu.h"

#include <string.h>
#include <stdlib.h>


/**
* @brief 菜单显示相关参数初始化（局部）
* @param *menu 菜单实例的指针
*/
static void menu_display_init(SrcslMenu *menu) {
	menu->display_first = 0;
	menu->display_last = menu->display_first +
		(menu->display_rows < menu->current_layer->nodes_nums ? menu->display_rows - 1 : menu->current_layer->nodes_nums - 1);
	menu->display_selection = menu->display_first;
}

void srcsl_menu_ctrl_init(SrcslMenu * menu, uint8_t rows_num)
{
	menu->current_layer = menu->root;
	menu->display_rows = rows_num;
	menu_display_init(menu);
}

void srcsl_menu_layer_init(SrcslMenuLayer * layer, SrcslMenuNode * nodes, uint8_t nodes_nums)
{
	layer->parent = NULL;
	layer->nodes = nodes;
	layer->nodes_nums = nodes_nums;
}

int srcsl_menu_layer_edit(SrcslMenuLayer * layer, int node_index, char * node_name, void(*func)(void))
{
	if (node_index >= layer->nodes_nums) {
		//error handler
	}
	layer->nodes[node_index].name = node_name;
	layer->nodes[node_index].next_layer = NULL;
	layer->nodes[node_index].func = func;
	return 0;
}


void srcsl_menu_layer_link(SrcslMenuLayer * child, SrcslMenuLayer * parent, int node_index) {
	parent->nodes[node_index].next_layer = child;
	child->parent = parent;
}


void srcsl_menu_home(SrcslMenu * menu)
{
	menu->current_layer = menu->root;
	menu_display_init(menu);
}


void srcsl_menu_back(SrcslMenu * menu)
{
	menu->current_layer = menu->current_layer->parent;
	menu_display_init(menu);
}


void srcsl_menu_confirm(SrcslMenu * menu)
{
	if (menu->current_layer->nodes[menu->display_selection].next_layer != NULL) {
		menu->current_layer = menu->current_layer->nodes[menu->display_selection].next_layer;
		menu_display_init(menu);
	}
	else if (menu->current_layer->nodes[menu->display_selection].func != NULL) {
		menu->current_layer->nodes[menu->display_selection].func();
		//other operation
	}
}


void srcsl_menu_up(SrcslMenu * menu)
{
	//光标移动后在显示区域内
	if (menu->display_selection > menu->display_first) {
		menu->display_selection--;
	}
	//光标移动后在显示区域外，显示区域移动后在节点区域内
	else if (menu->display_selection > 0) {
		menu->display_selection--;
		menu->display_first--;
		menu->display_last--;
	}
	//光标移动后在显示区域外，显示区域移动后在节点区域外，需要整体移到最末端
	else {
		menu->display_selection = menu->current_layer->nodes_nums - 1;
		menu->display_last = menu->current_layer->nodes_nums - 1;
		menu->display_first = menu->current_layer->nodes_nums - menu->display_rows;
		//显示区域大于节点数量
		if (menu->current_layer->nodes_nums < menu->display_rows) {
			menu->display_first = 0;
		}
	}
}


void srcsl_menu_down(SrcslMenu * menu)
{
	//光标移动后在显示区域内
	if (menu->display_selection < menu->display_last) {
		menu->display_selection++;
	}
	//光标移动后在显示区域外，显示区域移动后在节点区域内
	else if (menu->display_selection + 1 < menu->current_layer->nodes_nums) {
		menu->display_selection++;
		menu->display_first++;
		menu->display_last++;
	}
	//光标移动后在显示区域外，显示区域移动后在节点区域外，需要整体移到最末端
	else {
		menu_display_init(menu);
	}
}
