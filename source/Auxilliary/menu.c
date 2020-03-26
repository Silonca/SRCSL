#include "menu.h"

#include <string.h>

void menu_init( Menu *menu)
{
    menu->root = ( MenuNode*)malloc( sizeof( MenuNode));
    menu->root->child = ( MenuNode*)malloc( sizeof( MenuNode));
    menu->root->func = NULL;
    menu->root->parent = NULL;
    menu->root->sibling = NULL;
    menu->root->index = 0;
    menu->root->str = "/";
    
    menu->current_node = menu->root;
    menu->index = 0; 
}

int menu_set_path( Menu *menu, char *path)                      
{
    menu->current_node = menu->root;
    for( char *name = strtok( path, "/"); path != NULL; name = strtok( path, "/"))
    {
        //to find the path
        while( strncmp( name, menu->current_node->str, strlen(name)) != 0)
        {
            //don't exist,establish one
            if( menu->current_node->sibling == NULL)
                return menu_add( menu, name, NULL);
            //next
            else
                menu->current_node = menu->current_node->sibling;       
        }
        
        //if there is a func of the node,it should not be a parent
        if( menu->current_node->func != NULL)       
            return -3;
        
        //add a sentry child,and change current node down a level along the tree to link to the sentry child
        menu->current_node->child = ( MenuNode*)malloc( sizeof( MenuNode));
        menu->current_node->child->parent = menu->current_node;
        menu->current_node = menu->current_node->child;
        menu->current_node->child = NULL;
        menu->current_node->sibling = NULL;
        menu->current_node->str = NULL;
        menu->current_node->func = NULL;
        menu->index = 0;


    }
}


int menu_add( Menu *menu, char *name, char* (*func)())
{
    menu->current_node->sibling = ( MenuNode*)malloc( sizeof( MenuNode));
    if( menu->current_node->sibling == NULL)
        return -1;
    menu->current_node->sibling->parent = menu->current_node->parent;
    menu->current_node->sibling->index = menu->current_node->index;
    menu->current_node->sibling->str = name;
    menu->current_node->sibling->func = func;

    menu->current_node = menu->current_node->sibling;

    return 0;
}


char* menu_out_buffer( Menu *menu, MenuForm *form);

