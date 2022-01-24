/* 
 * File:   my_delays.h
 * Author: Hector
 *
 */
#ifndef MY_DELAYS_H
#define	MY_DELAYS_H

#include <xc.h>

#define _XTAL_FREQ   (80000000L)    // system clock

void delay_us(unsigned long delay);
void delay_ms(unsigned long delay);



#endif	/* MY_DELAYS_H */

