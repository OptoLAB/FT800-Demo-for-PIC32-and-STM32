/* 
 * File:   FT800_Port.h
 * Author: Jovan
 *
 * Created on August 4, 2019, 10:44 PM
 */

#ifndef FT800_PORT_H
#define	FT800_PORT_H

#include <xc.h>
#include "FT800_TypeDefs.h"

//-------------------------------------------------------------------------------
//SYSTEM 
//-------------------------------------------------------------------------------
#define SYS_FREQ    200000000L      // 200MHz - as set in CPUConfig
#define PCLK        (SYS_FREQ/2)    // 100MHz - as set in main.c
//-------------------------------------------------------------------------------
//FT800 PD PIN
//------------------------------------------------------------------------------
#define FT800_PD_IO()       TRISBbits.TRISB11=0
#define FT800_PD_LO()       LATBbits.LATB11=0
#define FT800_PD_HI()       LATBbits.LATB11=1
//-------------------------------------------------------------------------------
//FT800 INT PIN
//-------------------------------------------------------------------------------
#define FT800_INT_IO()     {\
                            /*INT1 on RG9*/\
                            INT1R=0b0001;\
                            TRISGbits.TRISG9=1;\
                           }     

//-------------------------------------------------------------------------------
//FT800 SPI
//-------------------------------------------------------------------------------
#define FT800_CS_IO()       TRISBbits.TRISB2=0
#define FT800_CS_LO()       LATBbits.LATB2=0
#define FT800_CS_HI()       LATBbits.LATB2=1
#define FT800_SPI_CHANNEL   SPI_CHANNEL2
#define FT800_SPIBUF        SPI2BUF
#define FT800_SPIBRG        SPI2BRG
#define FT800_SPISTATbits   SPI2STATbits   
#define FT800_SPICONbits    SPI2CONbits 
#define FT800_SPI_SPEED     10000000    //10MHz 
#define FT800_SPI_PPS(){\
        /*SDI on RD3*/\
        SDI2R=0b0000;\
        TRISDbits.TRISD3 = 1;\
        /*SDO on RD2*/\
        RPD2R=0b0110;\
        }

void FT800_InitPins(void);
void F800_InitSPI(void);
void F800_InitInterrupt(void);
uint8_t SPI_xchg (uint8_t data);
void FT800_WriteSPI(uint8_t data);
uint8_t FT800_ReadSPI(void);


#endif	/* FT800_PORT_H */

