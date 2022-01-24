/* 
 * File:   my_delays.h
 * Author: Jovan
 *
 */
#ifndef MY_DELAYS_H
#define	MY_DELAYS_H

#include <xc.h>
#include "FT800_TypeDefs.h"

#define _XTAL_FREQ   (200000000UL)    // system clock

void delay_ms(uint32_t delay); 
void delay_us(uint32_t delay);

#endif	/* MY_DELAYS_H */

