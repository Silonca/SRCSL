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


void key_init( Key *key);
void key_update( Key *key, uint8_t key_state);
void key_update_withquiver( Key *key, uint8_t key_state);
uint8_t key_get_state( Key *key);
uint8_t key_get_action( Key *key);



#endif

