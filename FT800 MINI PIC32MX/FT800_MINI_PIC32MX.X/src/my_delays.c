#include "my_delays.h"

void delay_ms(unsigned long delay) 
{
    register unsigned long startCntms = _CP0_GET_COUNT();
    register unsigned long waitCntms = delay * (_XTAL_FREQ / 1000 / 2); //core timer runs at half of system clock

    while (_CP0_GET_COUNT() - startCntms < waitCntms);
}

void delay_us(unsigned long delay) 
{
    register unsigned long startCnt = _CP0_GET_COUNT();
    register unsigned long waitCnt = delay * (_XTAL_FREQ / 1000000 / 2); //core timer runs at half of system clock

    while (_CP0_GET_COUNT() - startCnt < waitCnt);
}
