#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include <stdint.h>


enum KEY_STATE { KEY_STATE_PRESS, KEY_STATE_UNPRESS};
enum KEY_ACTION { KEY_ACTION_NONE, KEY_ACTION_PRESS, KEY_ACTION_UNPRESS};


typedef struct
{
    uint8_t state;
    uint8_t last_state;
    uint8_t action;
} Key;


void Key_Init( Key *key);
void Key_Update( Key *key, uint8_t key_state);
void Key_Update_WithQuiver( Key *key, uint8_t key_state);
uint8_t Key_Get_State( Key *key);
uint8_t Key_Get_Action( Key *key);



#endif

