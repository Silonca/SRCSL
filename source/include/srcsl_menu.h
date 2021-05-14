#ifndef SRCSL_MENU_H_INCLUDED
#define SRCSL_MUNE_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

struct SrcslMenuNode;
struct SrcslMenuLayer;

///menu节点，相当于文件的概念，当节点是子层时，它相当于逻辑中介，表明子层的名字和下一层
typedef struct SrcslMenuNode
{
	char *name;								//!< 节点名字
	void(*func)(void);						//!< 节点功能
	struct SrcslMenuLayer *next_layer;		//!< 节点子层（此项不为NULL时func为NULL，两项取一，功能互斥）
} SrcslMenuNode;

///menu层，类似于文件夹的概念
typedef struct SrcslMenuLayer
{
	struct SrcslMenuLayer *parent;			//!< 父层，跨越MenuNode直接指向上一层MenuLayer
	SrcslMenuNode *nodes;					//!< 当前层内容
	uint8_t nodes_nums;						//!< 当前层内容数量
} SrcslMenuLayer;


typedef struct 
{
	SrcslMenuLayer *root;					//!< 根层
	SrcslMenuLayer *current_layer;			//!< 当前层

	//显示区域及光标位置
	uint8_t display_rows;					//!< 显示区域大小
	uint8_t display_first;					//!< 显示区域第一项
	uint8_t display_last;					//!< 显示区域最后一项
	uint8_t display_selection;				//!< 光标位置

} SrcslMenu;


/**
* @brief 菜单控制初始化
* @param *menu		菜单实例的指针
* @param rows_num	要显示的行数
*/
void srcsl_menu_ctrl_init(SrcslMenu *menu, uint8_t rows_num);



/**
* @brief 初始化菜单层
* @param *menu			菜单层实例的指针
* @param node_index		层中节点实例的指针
* @param nodes_nums		层拥有的节点数
*/
void srcsl_menu_layer_init(SrcslMenuLayer * layer, SrcslMenuNode * nodes, uint8_t nodes_nums);

/**
* @brief 编辑层中的节点
* @param *menu			菜单层实例的指针
* @param node_index		节点所在的位置
* @param *node_name		节点的名字
* @param *fun			节点的功能
* @return
*/
int srcsl_menu_layer_edit(SrcslMenuLayer * layer, int node_index, char * node_name, void(*func)(void));

/**
* @brief 连接两个菜单层
* @param *child			子菜单层实例的指针
* @param *parent		父菜单层实例的指针
* @param node_index		子菜单层在父菜单层中的位置
*/
void srcsl_menu_layer_link(SrcslMenuLayer * child, SrcslMenuLayer * parent, int node_index);




/**
* @brief 菜单回到根部
* @param *menu 菜单实例的指针
*/
void srcsl_menu_home(SrcslMenu* menu);			

/**
* @brief 菜单回到上一层
* @param *menu 菜单实例的指针
*/
void srcsl_menu_back( SrcslMenu *menu);		

/**
* @brief 菜单确认（进入下一层或执行功能）
* @param *menu 菜单实例的指针
*/
void srcsl_menu_confirm( SrcslMenu *menu);		

/**
* @brief 上移光标
* @param *menu 菜单实例的指针
*/
void srcsl_menu_up( SrcslMenu *menu);			

/**
* @brief 下移光标
* @param *menu 菜单实例的指针
*/
void srcsl_menu_down( SrcslMenu *menu);		


//char* menu_out( Menu *menu);

//输出通过current_layer和display相关变量自行读出


#ifdef __cplusplus
}
#endif

#endif 