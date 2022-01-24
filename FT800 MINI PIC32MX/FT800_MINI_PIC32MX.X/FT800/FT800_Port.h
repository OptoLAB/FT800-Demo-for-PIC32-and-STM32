/* 
 * File:   FT800_Port.h
 * Author: Jovan
 *
 * Created on August 4, 2019, 10:44 PM
 */

#ifndef FT800_PORT_H
#define	FT800_PORT_H

#include "FT800_TypeDefs.h"

//-------------------------------------------------------------------------------
//SYSTEM 
//-------------------------------------------------------------------------------
#define SYS_FREQ            80000000L      // 80MHz - as set in CPUConfig
#define PCLK                (SYS_FREQ/2)   // 40MHz - as set in CPUConfig
//-------------------------------------------------------------------------------
//FT800 PD PIN
//------------------------------------------------------------------------------
#define FT800_PD_IO()       TRISEbits.TRISE6=0
#define FT800_PD_LO()       LATEbits.LATE6=0
#define FT800_PD_HI()       LATEbits.LATE6=1
//-------------------------------------------------------------------------------
//FT800 INT PIN
//-------------------------------------------------------------------------------
#define FT800_INT_IO()      TRISDbits.TRISD0=1  //INT0
//-------------------------------------------------------------------------------
//FT800 SPI
//-------------------------------------------------------------------------------
#define FT800_CS_IO()       TRISBbits.TRISB9=0
#define FT800_CS_LO()       LATBbits.LATB9=0
#define FT800_CS_HI()       LATBbits.LATB9=1
#define FT800_SPI_CHANNEL   SPI_CHANNEL2
#define FT800_SPIBUF        SPI2BUF
#define FT800_SPIBRG        SPI2BRG
#define FT800_SPISTATbits   SPI2STATbits   
#define FT800_SPICONbits    SPI2CONbits 
#define FT800_SPI_SPEED     10000000    //10MHz 

void FT800_InitPins(void);
void F800_InitSPI(void);
void F800_InitInterrupt(void);
uint8_t SPI_xchg (uint8_t data);
void FT800_WriteSPI(uint8_t data);
uint8_t FT800_ReadSPI(void);


#endif	/* FT800_PORT_H */

