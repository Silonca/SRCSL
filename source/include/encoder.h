#ifndef SRCSL_ENCODER_H_INCLUDED
#define SRCSL_ENCODER_H_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

enum ENCODER_TYPE { ENCODER_ABSOLUTE, ENCODER_INCREMENTAL};

typedef struct
{
    uint32_t enocder_type;

    int32_t angle_abs;             //for incremental encoder,it's relative to origin position
    int32_t angle_sum;
    int32_t rounds;  
    int32_t d_value;               //diffence between two angle    
    int32_t range;      

} Encoder;

/*
void encoder_absolute_init( Encoder *encoder, uint32_t range, uint32_t angle_abs);
void encoder_incremental_init( Encoder *encoder, uint32_t range);
void encoder_absolute_updata( Encoder *encoder, uint32_t angle_abs);
void encoder_incremental_updata( Encoder *encoder, uint32_t delta);
*/

void encoder_init( Encoder *encoder, uint32_t encoder_type, uint32_t range);
void encoder_set_angle_abs( Encoder *encoder, int32_t angle_abs);
void encoder_updata( Encoder *encoder, uint32_t angle);

uint32_t encoder_get_angle_abs( Encoder *encoder);
int32_t encoder_get_angle_total( Encoder *encoder);
int32_t encoder_get_d_value( Encoder *encoder);

void encoder_clone( Encoder *des, Encoder *src);

#ifdef __cplusplus
}
#endif

#endif
