/* 
 * File:   SD_Port.h
 * Author: Jovan
 *
 * Created on August 5, 2019, 1:16 AM
 */

#ifndef SD_PORT_H
#define	SD_PORT_H

#define SYS_FREQ    (200000000L)
#define PCLK        (SYS_FREQ/2)

#define SD_CS_IO()          TRISDbits.TRISD9 = 0
#define SD_CS_LO()          LATDbits.LATD9 = 0
#define SD_CS_HI()          LATDbits.LATD9 = 1
#define SD_SPI_CHANNEL      SPI_CHANNEL4
#define SD_SPIBUF           SPI4BUF
#define SD_SPIBRG           SPI4BRG
#define SD_SPISTATbits      SPI4STATbits   
#define SD_SPICONbits       SPI4CONbits

#define SD_SPI_SPEED_HI     20000000    //20MHz 
#define SD_SPI_SPEED_LO     400000      //400kHz    

#define	FCLK_SLOW()		{SD_SPIBRG=(PCLK/(2*SD_SPI_SPEED_LO) - 1);}	/* Set slow clock for card initialization (100k-400k) */
#define	FCLK_FAST()		{SD_SPIBRG=(PCLK/(2*SD_SPI_SPEED_HI) - 1);}	/* Set fast clock for generic read/write */

#define SD_SPI_PPS(){\
        /*SDI on RD11*/\
        SDI4R=0b0011;\
        TRISDbits.TRISD11 = 1;\
        /*SDO on RB6*/\
        RPB6R=0b1000;\
        }
#endif	/* SD_PORT_H */

