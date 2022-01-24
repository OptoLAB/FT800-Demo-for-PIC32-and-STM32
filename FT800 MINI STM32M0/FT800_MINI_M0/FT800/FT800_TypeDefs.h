/* 
 * File:   FT800_TypeDefs.h
 * Author: Jovan
 *
 * Created on August 4, 2019, 11:10 PM
 */

#ifndef FT800_TYPEDEFS_H
#define	FT800_TYPEDEFS_H

#include "stm32f0xx_hal.h"
#include <sys/_stdint.h>
//-------------------------------------------------------------------
//DEFINE TYPES - XC32 compiler
//char, signed char:                    8 bits      [-128, 127]
//unsigned char:                        8 bits      [0, 255]
//short, signed short:                  16 bits     [-32768, 32767]
//unsigned short:                       16 bits     [0, 65535]
//int, signed int, long, signed long:   32 bits     [-2^31, 2^31-1]
//unsigned int, unsigned long:          32 bits     [0 2^32-1]
//long long, signed long long:          64 bits     [-2^63, 2^63-1]
//unsigned long long:                   64 bits     [0 2^64-1]
//-------------------------------------------------------------------
//8, 16 & 32 bits data
//-------------------------------------------------------------------

#ifndef uint8_t
    typedef unsigned char type_uint8_t;      
    #define uint8_t type_uint8_t
#endif
#ifndef uint16_t
    typedef unsigned short type_uint16_t;
    #define uint16_t type_uint16_t
#endif
#ifndef uint32_t
    typedef unsigned long type_uint32_t;
    #define uint32_t type_uint32_t
#endif
#ifndef uint64_t
    typedef unsigned long long type_uint64_t;
    #define uint64_t type_uint64_t
#endif
    
    
#ifndef int8_t
    typedef char type_int8_t;
    #define int8_t type_int8_t
#endif
#ifndef int16_t
    typedef short type_int16_t;
    #define int16_t type_int16_t
#endif
#ifndef int32_t
    typedef long type_int32_t;
    #define int32_t type_int32_t
#endif
#ifndef int64_t
    typedef long long type_int64_t;
    #define int64_t type_int36_t
#endif



#endif	/* FT800_TYPEDEFS_H */

