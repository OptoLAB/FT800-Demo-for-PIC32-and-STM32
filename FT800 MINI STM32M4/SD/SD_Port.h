/* 
 * File:   SD_Port.h
 * Author: Jovan
 *
 * Created on August 5, 2019, 1:16 AM
 */

#ifndef SD_PORT_H
#define	SD_PORT_H

#define SD_SPI		 	SPI1
#define	CS_PORT			GPIOA
#define CS_PIN			GPIO_PIN_4
#define SD_CS_LOW()		CS_PORT->BSRR=(uint32_t)(CS_PIN<<16)
#define SD_CS_HIGH()	CS_PORT->BSRR=(CS_PIN)

//(Note that the _256 is used as a mask to clear the prescalar bits as it provides binary 111 in the correct position)
#define FCLK_SLOW() { MODIFY_REG(SD_SPI->CR1, SPI_BAUDRATEPRESCALER_256, SPI_BAUDRATEPRESCALER_128); }	// Set SCLK = slow
#define FCLK_FAST() { MODIFY_REG(SD_SPI->CR1, SPI_BAUDRATEPRESCALER_256, SPI_BAUDRATEPRESCALER_2); }	// Set SCLK = fast

#endif	/* SD_PORT_H */

