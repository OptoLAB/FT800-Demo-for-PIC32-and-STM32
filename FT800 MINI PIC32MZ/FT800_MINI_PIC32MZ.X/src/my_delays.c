#include"my_delays.h"
#include <xc.h>

void delay_ms(uint32_t delay) 
{
    register uint32_t startCntms = _CP0_GET_COUNT();
    register uint32_t waitCntms = delay * (_XTAL_FREQ / 1000 / 2); //core timer runs at half of system clock

    while (_CP0_GET_COUNT() - startCntms < waitCntms);
}

void delay_us(uint32_t delay) 
{
    register uint32_t startCnt = _CP0_GET_COUNT();
    register uint32_t waitCnt = delay * (_XTAL_FREQ / 1000000 / 2); //core timer runs at half of system clock

    while (_CP0_GET_COUNT() - startCnt < waitCnt);
}

