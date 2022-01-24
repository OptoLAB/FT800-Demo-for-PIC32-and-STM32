/* 
 * File:   FT800_Port.h
 * Author: Jovan
 *
 * Created on August 4, 2019, 10:44 PM
 */

#ifndef FT800_PORT_H
#define	FT800_PORT_H

#include "FT800_TypeDefs.h"
#include "stm32f4xx_hal.h"
// Every define commented here is taken out of the code due to Cube MX auto implementation and initialization


//-------------------------------------------------------------------------------
//SYSTEM 
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//FT800 PD PIN
//------------------------------------------------------------------------------
#define	FT800_PD_PORT		GPIOB
#define FT800_PD_PIN		GPIO_PIN_3

#define FT800_PD_LO()		FT800_PD_PORT->BSRR=(uint32_t)(FT800_PD_PIN<<16)
#define FT800_PD_HI() 		FT800_PD_PORT->BSRR=(FT800_PD_PIN)

//-------------------------------------------------------------------------------
//FT800 INT PIN
//-------------------------------------------------------------------------------
#define FT800_INT_PORT		GPIOC
#define FT800_INT_PIN		GPIO9
//-------------------------------------------------------------------------------
//FT800 SPI
//-------------------------------------------------------------------------------
#define FT800_SPI			SPI2
#define	FT800_CS_PORT		GPIOB
#define FT800_CS_PIN		GPIO_PIN_12
#define FT800_CS_LO()		FT800_CS_PORT->BSRR=(uint32_t)(FT800_CS_PIN<<16)
#define FT800_CS_HI() 		FT800_CS_PORT->BSRR=(FT800_CS_PIN)


void FT800_InitPins(void);
void F800_InitSPI(void);
void F800_InitInterrupt(void);
uint8_t SPI_xchg (uint8_t data);
void FT800_WriteSPI(uint8_t data);
uint8_t FT800_ReadSPI(void);


#endif	/* FT800_PORT_H */

