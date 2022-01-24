/* 
 * File:   SD_Port.h
 * Author: Jovan
 *
 * Created on August 5, 2019, 1:16 AM
 */

#ifndef SD_PORT_H
#define	SD_PORT_H

#define SYS_FREQ    (80000000L)
#define PCLK        (SYS_FREQ/2)

#define SD_CS_IO()          TRISDbits.TRISD10 = 0
#define SD_CS_LO()          LATDbits.LATD10 = 0
#define SD_CS_HI()          LATDbits.LATD10 = 1
#define SD_SPI_CHANNEL      SPI_CHANNEL3
#define SD_SPIBUF           SPI3BUF
#define SD_SPIBRG           SPI3BRG
#define SD_SPISTATbits      SPI3STATbits   
#define SD_SPICONbits       SPI3CONbits

#define SD_SPI_SPEED_HI     10000000    //10MHz 
#define SD_SPI_SPEED_LO     400000      //400kHz      

#define	FCLK_SLOW()		{SD_SPIBRG=(PCLK/(2*SD_SPI_SPEED_LO) - 1);}	/* Set slow clock for card initialization (100k-400k) */
#define	FCLK_FAST()		{SD_SPIBRG=(PCLK/(2*SD_SPI_SPEED_HI) - 1);}	/* Set fast clock for generic read/write */

#endif	/* SD_PORT_H */

