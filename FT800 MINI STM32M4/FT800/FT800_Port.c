#include "FT800_Port.h"

/* ************************************************************************************ */
// Initialize FT800 pins: CS, PD, SPI, INT
/* ************************************************************************************ */

void FT800_InitPins(void)
{
	__NOP();// Nothing to add since Cube MX generates this in main
}

/* ************************************************************************************ */
// Initialize (Open) FT800 SPI channel 
/* ************************************************************************************ */

void F800_InitSPI(void)
{

	__NOP();// Nothing to add since Cube MX generates this in main
	SET_BIT(FT800_SPI->CR1, SPI_CR1_SPE); //Just enable
}

/* ************************************************************************************ */
// Initialize external interrupt - required for touch screen
/* ************************************************************************************ */

void F800_InitInterrupt(void)
{
    __NOP();// Nothing to add since Cube MX generates this in main
}

/* ************************************************************************************ */
// Exchange byte over SPI
/* ************************************************************************************ */

uint8_t SPI_xchg (uint8_t data)
{
	while (!(FT800_SPI->SR&SPI_FLAG_TXE));
	FT800_SPI->DR=data;
	while (!(FT800_SPI->SR&SPI_FLAG_RXNE));
	return (FT800_SPI->DR);
}

/* ************************************************************************************ */
// Write data (transmit single byte over SPI)
/* ************************************************************************************ */

void FT800_WriteSPI(uint8_t data)
{
	SPI_xchg(data);
}

/* ************************************************************************************ */
// Read data (receive single byte over SPI)
/* ************************************************************************************ */

uint8_t FT800_ReadSPI(void)
{
	return SPI_xchg(0x00);
}

