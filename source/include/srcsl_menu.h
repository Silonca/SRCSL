#ifndef SRCSL_MENU_H_INCLUDED
#define SRCSL_MUNE_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include "srcslsys.h"

struct SrcslMenuNode;
struct SrcslMenuLayer;

///menu�ڵ㣬�൱���ļ��ĸ�����ڵ����Ӳ�ʱ�����൱���н飬�����Ӳ�����ֺ���һ��
typedef struct SrcslMenuNode
{
	char *name;								//!< �ڵ�����
	void(*func)(void);						//!< �ڵ㹦��
	struct SrcslMenuLayer *next_layer;		//!< �ڵ��Ӳ㣨���ΪNULLʱfuncΪNULL������ȡһ�����ܻ��⣩
} SrcslMenuNode;

///menu�㣬�������ļ��еĸ���
typedef struct SrcslMenuLayer
{
	struct SrcslMenuLayer *parent;			//!< ���㣬��ԽMenuNodeֱ��ָ����һ��MenuLayer
	SrcslMenuNode *nodes;					//!< ��ǰ������
	uint8_t nodes_nums;						//!< ��ǰ����������
} SrcslMenuLayer;


typedef struct 
{
	SrcslMenuLayer *root;					//!< ����
	SrcslMenuLayer *current_layer;			//!< ��ǰ��

	//��ʾ���򼰹��λ��
	uint8_t display_rows;					//!< ��ʾ�����С
	uint8_t display_first;					//!< ��ʾ�����һ��
	uint8_t display_last;					//!< ��ʾ�������һ��
	uint8_t display_selection;				//!< ���λ��

} SrcslMenu;


/**
* @brief �˵����Ƴ�ʼ��
* @param *menu		�˵�ʵ����ָ��
* @param rows_num	Ҫ��ʾ������
*/
void srcsl_menu_ctrl_init(SrcslMenu *menu, uint8_t rows_num);



/**
* @brief ��ʼ���˵���
* @param *menu			�˵���ʵ����ָ��
* @param node_index		���нڵ�ʵ����ָ��
* @param nodes_nums		��ӵ�еĽڵ���
*/
void srcsl_menu_layer_init(SrcslMenuLayer * layer, SrcslMenuNode * nodes, uint8_t nodes_nums);

/**
* @brief �༭���еĽڵ�
* @param *menu			�˵���ʵ����ָ��
* @param node_index		�ڵ����ڵ�λ��
* @param *node_name		�ڵ������
* @param *fun			�ڵ�Ĺ���
* @return
*/
int srcsl_menu_layer_edit(SrcslMenuLayer * layer, int node_index, char * node_name, void(*func)(void));

/**
* @brief ���������˵���
* @param *child			�Ӳ˵���ʵ����ָ��
* @param *parent		���˵���ʵ����ָ��
* @param node_index		�Ӳ˵����ڸ��˵����е�λ��
*/
void srcsl_menu_layer_link(SrcslMenuLayer * child, SrcslMenuLayer * parent, int node_index);




/**
* @brief �˵��ص�����
* @param *menu �˵�ʵ����ָ��
*/
void srcsl_menu_home(SrcslMenu* menu);			

/**
* @brief �˵��ص���һ��
* @param *menu �˵�ʵ����ָ��
*/
void srcsl_menu_back( SrcslMenu *menu);		

/**
* @brief �˵�ȷ�ϣ�������һ���ִ�й��ܣ�
* @param *menu �˵�ʵ����ָ��
*/
void srcsl_menu_confirm( SrcslMenu *menu);		

/**
* @brief ���ƹ��
* @param *menu �˵�ʵ����ָ��
*/
void srcsl_menu_up( SrcslMenu *menu);			

/**
* @brief ���ƹ��
* @param *menu �˵�ʵ����ָ��
*/
void srcsl_menu_down( SrcslMenu *menu);		


//���ͨ��current_layer��display��ر������ж���


#ifdef __cplusplus
}
#endif

#endif 