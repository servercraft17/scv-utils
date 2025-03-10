#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#ifndef SS_PI
#define SS_PI 3.14159265358979323846
#endif /* SS_PI */

#ifndef SS_PI_2
#define SS_PI_2 SS_PI/2
#endif

#define SS_TAU SS_PI*2

typedef uint32_t        uint  ;  
typedef unsigned char   uchar ;  

#define SS_cot(x__) 1.0f/tanf((float)(x__))
#define SS_deg2rad(deg__) ((float)(deg__)) * SS_PI / 180.0f
#define SS_rad2deg(rad__) ((float)(rad__)) * 180.0f / SS_PI

#endif/* COMMON_HPP */
