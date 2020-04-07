#ifndef MENU_H_INCLUDED
#define MUNE_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

typedef struct MenuNode
{
    struct MenuNode *parent;
    struct MenuNode *child;
    struct MenuNode *sibling;

    void ( *func)(void);
    int index;
    char *str;
} MenuNode;





typedef struct
{
    uint8_t window_width;
    uint8_t window_height;
    uint8_t is_index_display;
    uint8_t index_display_style;
    
    uint8_t highlight_style;

    char *border_str;


} MenuForm;

typedef struct 
{
    MenuNode *root;

    MenuNode *current_node;   
    int index;

} Menu;

//establish menu
void menu_init( Menu *menu);

int menu_set_path( Menu *menu, char *path);                        //set path to add item,if the path doesn't exist,establish it
int menu_add( Menu *menu, char *child, char* (*func)());            //add child item

//use menu
void menu_back( Menu *menu);
void menu_confirm( Menu *menu);
void menu_up( Menu *menu);
void menu_down( Menu *menu);
char* menu_out_buffer( Menu *menu, MenuForm *form);

#ifdef __cplusplus
}
#endif

#endif 