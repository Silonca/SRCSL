#include <stdio.h>
#include <stdlib.h>

#include "include/srcsl_menu.h"

SrcslMenu menu;

SrcslMenuLayer root;
SrcslMenuNode root_nodes[5];
SrcslMenuLayer a1;
SrcslMenuLayer a2;
SrcslMenuNode a1_nodes[6];
SrcslMenuNode a2_nodes[7];
SrcslMenuLayer a11;
SrcslMenuNode a11_nodes[3];

void a3(void)
{
	printf("a3\n");
}
void a4(void)
{
	printf("a4\n");
}
void a5(void)
{
	printf("a5\n");
}

void a12(void)
{
	printf("a12\n");
}
void a13(void)
{
	printf("a13\n");
}
void a14(void)
{
	printf("a14\n");
}
void a15(void)
{
	printf("a15\n");
}
void a16(void)
{
	printf("a16\n");
}

void a21(void)
{
	printf("a21\n");
}
void a22(void)
{
	printf("a22\n");
}
void a23(void)
{
	printf("a23\n");
}
void a24(void)
{
	printf("a24\n");
}
void a25(void)
{
	printf("a25\n");
}
void a26(void)
{
	printf("a26\n");
}
void a27(void)
{
	printf("a27\n");
}
void a111(void)
{
	printf("a111\n");
}
void a112(void)
{
	printf("a112\n");
}
void a113(void)
{
	printf("a113\n");
}

void test_menu_init(void)
{

	srcsl_menu_layer_init(&root, root_nodes, 5);
	srcsl_menu_layer_init(&a1, a1_nodes, 6);
	srcsl_menu_layer_init(&a2, a2_nodes, 7);
	srcsl_menu_layer_init(&a11, a11_nodes, 3);

	srcsl_menu_layer_edit(&root, 0, "a1", NULL);
	srcsl_menu_layer_edit(&root, 1, "a2", NULL);
	srcsl_menu_layer_edit(&root, 2, "a3", a3);
	srcsl_menu_layer_edit(&root, 3, "a4", a4);
	srcsl_menu_layer_edit(&root, 4, "a5", a5);

	srcsl_menu_layer_edit(&a1, 0, "a11", NULL);
	srcsl_menu_layer_edit(&a1, 1, "a12", a12);
	srcsl_menu_layer_edit(&a1, 2, "a13", a13);
	srcsl_menu_layer_edit(&a1, 3, "a14", a14);
	srcsl_menu_layer_edit(&a1, 4, "a15", a15);
	srcsl_menu_layer_edit(&a1, 5, "a16", a16);

	srcsl_menu_layer_edit(&a2, 0, "a21", a21);
	srcsl_menu_layer_edit(&a2, 1, "a22", a22);
	srcsl_menu_layer_edit(&a2, 2, "a23", a23);
	srcsl_menu_layer_edit(&a2, 3, "a24", a24);
	srcsl_menu_layer_edit(&a2, 4, "a25", a25);
	srcsl_menu_layer_edit(&a2, 5, "a26", a26);
	srcsl_menu_layer_edit(&a2, 6, "a27", a27);

	srcsl_menu_layer_edit(&a11, 0, "a111", a111);
	srcsl_menu_layer_edit(&a11, 1, "a112", a112);
	srcsl_menu_layer_edit(&a11, 2, "a113", a113);

	menu.root = &root;
	srcsl_menu_layer_link(&a1, &root, 0);
	srcsl_menu_layer_link(&a2, &root, 1);
	srcsl_menu_layer_link(&a11, &a1, 0);

	srcsl_menu_ctrl_init(&menu, 4);



}


void test_menu_display(void)
{
	for (uint8_t index = menu.display_first; index <= menu.display_last; ++index) 
	{
		if (index == menu.display_selection)
			printf("*");
		printf("menu:%s\n",menu.current_layer->nodes[index].name);
	}
	printf("%d,%d,%d\n", menu.display_first, menu.display_selection, menu.display_last);
	printf("-------------------------\n");
}

void test_menu(void)
{
	test_menu_init();

	//≤‚ ‘root
	test_menu_display();
	printf("rootdown\n");
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	printf("rootup\n");
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	
	printf("confirm\n");
	srcsl_menu_confirm(&menu);				test_menu_display();
											
	//≤‚ ‘a1
	printf("a1down\n");
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	printf("a1up\n");
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
				
	printf("confirm\n");
	srcsl_menu_confirm(&menu);				test_menu_display();
											
	//≤‚ ‘a11	
	printf("a11down\n");
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	printf("a11up\n");
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
	srcsl_menu_up(&menu);					test_menu_display();
											
	//≤‚ ‘a11nodes	
	printf("cdcdcd\n");
	srcsl_menu_confirm(&menu);				test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_confirm(&menu);				test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
	srcsl_menu_confirm(&menu);				test_menu_display();
	srcsl_menu_down(&menu);					test_menu_display();
											
	//root									
	printf("hcbcbccbch\n");
	srcsl_menu_home(&menu);					test_menu_display();
	//a1									test_menu_display();
	srcsl_menu_confirm(&menu);				test_menu_display();
	//root									test_menu_display();
	srcsl_menu_back(&menu);					test_menu_display();
	//a1									test_menu_display();
	srcsl_menu_confirm(&menu);				test_menu_display();
	//root									test_menu_display();
	srcsl_menu_back(&menu);					test_menu_display();
	//a11									test_menu_display();
	srcsl_menu_confirm(&menu);				test_menu_display();
	srcsl_menu_confirm(&menu);				test_menu_display();
	//a1									test_menu_display();
	srcsl_menu_back(&menu);					test_menu_display();
	//a11									test_menu_display();
	srcsl_menu_confirm(&menu);				test_menu_display();
	srcsl_menu_home(&menu);					test_menu_display();
}

