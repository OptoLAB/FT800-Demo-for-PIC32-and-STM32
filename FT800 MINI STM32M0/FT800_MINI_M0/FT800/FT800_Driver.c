
#include "FT800_Driver.h"   
//#include "FT800_Config.h" // zasto sam to morao da dodam boga pitaj kad vec postoji u FT800_Driver.h
uint16_t CMD_Offset=0;

/* ************************************************************************************ */
// Increment FIFO address offset
/* ************************************************************************************ */

void CMD_Offset_Inc(uint8_t command_size)
{
    CMD_Offset+=command_size; 
    CMD_Offset%=4096;
}

/* ************************************************************************************ */
// Set FIFO address offset
/* ************************************************************************************ */

void set_CMD_Offset(uint16_t offset)
{
    CMD_Offset=offset;
}

/* ************************************************************************************ */
// Get FIFO address offset
/* ************************************************************************************ */

uint16_t get_CMD_Offset(void)
{
    return CMD_Offset;
}

/* ************************************************************************************ */
// Write address. Most significant byte is sent first.
// mode: writing to FT800(WRITE), reading from FT800(READ), configure GPU(CONFIG)  
/* ************************************************************************************ */

void FT800_WriteAddress(uint32_t address, uint8_t mode)
{
    uint8_t byte = 0;
    
    if(mode==CONFIG) address<<=16;
    
    byte = ((address & 0x00FF0000) >> 16);  // Mask the first byte to send
    byte = ((byte & 0x3F) | mode);            // the MSBs are forced to 10 for WRITE, 00 for READ, 01 for CONFIG
    FT800_WriteSPI(byte);                         // Call the low-level SPI transmit routine                                                 //
    
    byte = ((address & 0x0000FF00) >> 8);   // Mask the next byte to be sent
    FT800_WriteSPI(byte);                         // Call the low-level SPI transmit routine 

    byte = (address & 0x000000FF);          // Mask the next byte to be sent
    FT800_WriteSPI(byte);                         // Call the low-level SPI transmit routine 
    
    if(mode==READ)FT800_WriteSPI(0x00); 
}

/* ************************************************************************************ */
// FT800 Write BYTE data at address 
/* ************************************************************************************ */

void FT800_Write8(uint32_t address, uint8_t data)
{
    if(address==RAM_CMD) // if writing to FIFO
    {
        address+=CMD_Offset;
        CMD_Offset_Inc(1);// Move the CMD Offset 
    }
    FT800_CS_LO();                          
    FT800_WriteAddress(address,WRITE);                 
    FT800_WriteSPI(data);        
    FT800_CS_HI(); 
}

/* ************************************************************************************ */
// FT800 Write WORD data at address 
/* ************************************************************************************ */

void FT800_Write16(uint32_t address, uint16_t data)
{
    if(address==RAM_CMD )// if writing to FIFO
    {
        address+=CMD_Offset;
        CMD_Offset_Inc(2);// Move the CMD Offset
    }
    FT800_CS_LO();                               
    FT800_WriteAddress(address,WRITE);                    
    FT800_WriteSPI((data&0x00FF));  
    FT800_WriteSPI((data&0xFF00)>>8);   
    FT800_CS_HI(); 
}

/* ************************************************************************************ */
// FT800 Write DWORD data at address in FIFO
/* ************************************************************************************ */

void FT800_Write32(uint32_t address, uint32_t data)
{
    if(address==RAM_CMD) // if writing to FIFO 
    {
        address+=CMD_Offset;
        CMD_Offset_Inc(4);// Move the CMD Offset
    }
    FT800_CS_LO();                                
    FT800_WriteAddress(address,WRITE);   
    FT800_WriteSPI((data&0x000000FF));  
    FT800_WriteSPI((data&0x0000FF00)>>8);    
    FT800_WriteSPI((data&0x00FF0000)>>16);  
    FT800_WriteSPI((data&0xFF000000)>>24);  
    FT800_CS_HI(); 
}

/* ************************************************************************************ */
// FT800 Read BYTE from address 
/* ************************************************************************************ */

uint8_t FT800_Read8(uint32_t address)
{
    uint8_t byte = 0;
    FT800_CS_LO();                          
    FT800_WriteAddress(address,READ);                 
    byte=FT800_ReadSPI();        
    FT800_CS_HI(); 
    return byte;
}
/* ************************************************************************************ */
// FT800 Read WORD from address 
/* ************************************************************************************ */

uint16_t FT800_Read16(uint32_t address)
{
    uint16_t byte=0;
    uint16_t word=0;
 
    FT800_CS_LO();                          
    FT800_WriteAddress(address,READ);      
    byte=FT800_ReadSPI(); 
    word|=byte;
    byte=FT800_ReadSPI(); 
    word|=(byte<<8);
    FT800_CS_HI(); 
    
    return word;
}

/* ************************************************************************************ */
// FT800 Read DWORD from address 
/* ************************************************************************************ */

uint32_t FT800_Read32(uint32_t address)
{
    uint32_t byte=0;
    uint32_t dword=0;
 
    FT800_CS_LO();                          
    FT800_WriteAddress(address,READ);      
    byte=FT800_ReadSPI(); 
    dword|=byte;
    byte=FT800_ReadSPI(); 
    dword|=(byte<<8);
    byte=FT800_ReadSPI(); 
    dword|=(byte<<16);
    byte=FT800_ReadSPI(); 
    dword|=(byte<<24);
    FT800_CS_HI(); 
    
    return dword;
}

/* ************************************************************************************ */
// FT800 configure GPU  
/* ************************************************************************************ */
 
void FT800_configGPU(void)
{
    FT800_CS_LO();
    FT800_WriteAddress(FT_GPU_EXTERNAL_OSC, CONFIG); // Change the PLL to external clock - optional
    FT800_WriteAddress(FT_GPU_PLL_48M, CONFIG);      // Ensure configured to 48 MHz 
    FT800_WriteAddress(FT_GPU_CORE_RESET, CONFIG);   // Reset the core
    FT800_WriteAddress(FT_GPU_ACTIVE_M, CONFIG);     // Read address 0 to ensure FT800 is active
    FT800_CS_HI();

}
 
/* ************************************************************************************ */
// FT800 configure display 
/* ************************************************************************************ */
 
void FT800_configDisplay(void)
{
    FT800_Write16(REG_HCYCLE, DISPLAY_HSYNC_PERIOD);
    FT800_Write16(REG_HOFFSET, DISPLAY_HBP + DISPLAY_HSLEN);
    FT800_Write16(REG_HSYNC0, 0);           
    FT800_Write16(REG_HSYNC1, DISPLAY_HBP);      
    
    FT800_Write16(REG_VCYCLE, DISPLAY_VSYNC_PERIOD);
    FT800_Write16(REG_VOFFSET, DISPLAY_VBP+DISPLAY_VSLEN);
    FT800_Write16(REG_VSYNC0, 0);           
    FT800_Write16(REG_VSYNC1, DISPLAY_VBP);      
    
    FT800_Write8(REG_SWIZZLE, DISPLAY_SWIZZLE);
    FT800_Write8(REG_PCLK_POL, DISPLAY_PCLK_POL);  
    FT800_Write16(REG_HSIZE, DISPLAY_WIDTH);           
    FT800_Write16(REG_VSIZE, DISPLAY_HEIGHT);  
    FT800_Write8(REG_PCLK, DISPLAY_PCLK);
}

/* ************************************************************************************ */
// FT800 set backlight [0-128]
/* ************************************************************************************ */

void FT800_setBacklight(uint8_t pwm_duty)
{
    if(pwm_duty>128) pwm_duty = 128;
    FT800_Write32(REG_PWM_DUTY,pwm_duty);    
}
 
/* ************************************************************************************ */
// FT800 configure touch screen 
/* ************************************************************************************ */
 
void FT800_configTouchScreen(void)
{
    FT800_Write16(REG_TOUCH_RZTHRESH, TOUCH_SENSITIVITY); 
    FT800_Write8(REG_TOUCH_MODE, TOUCH_MODE);   
    FT800_Write8(REG_TOUCH_ADC_MODE, TOUCH_ADC_MODE);   
    FT800_Write16(REG_TOUCH_CHARGE, TOUCH_CHARGE);  
    FT800_Write8(REG_TOUCH_SETTLE, TOUCH_SETTLE);  
    FT800_Write8(REG_TOUCH_OVERSAMPLE, TOUCH_OVERSAMPLE);   
}

/* ************************************************************************************ */
// FT800 clear interrupt flags
/* ************************************************************************************ */
 
void FT800_clearIntFlags(void)
{
    FT800_Read8(REG_INT_FLAGS);                 // Reading clears interrupt flags
}

/* ************************************************************************************ */
// FT800 configure touch screen interrupt
/* ************************************************************************************ */

void FT800_configTouchScreenInt(void)
{
    FT800_Write8(REG_INT_EN, 0x01);                 // enable interrupt
    DELAY(20);
    FT800_Write8(REG_INT_MASK,0b00000110);                 // mask interrupt
    DELAY(20);

    FT800_clearIntFlags();             
}

/* ************************************************************************************ */
// FT800 configure GPIOs
/* ************************************************************************************ */

void FT800_configGPIO(void)
{
    FT800_Write8(REG_GPIO_DIR, GPIO_DIR); 
    FT800_Write8(REG_GPIO, GPIO_SET);  
}

/* ************************************************************************************ */
// FT800 initialize
/* ************************************************************************************ */
 
void FT800_init(void)
{
    FT800_InitPins();
    F800_InitSPI();
    F800_InitInterrupt();
    DELAY(50);
    
    FT800_PD_HI();
    DELAY(20);                          // Delay for power up of regulator
    
    FT800_CS_LO();
    FT800_WriteAddress(0x00000000,READ); //wake up
    FT800_CS_HI();
    
    FT800_configGPU();
    DELAY(50);
    FT800_configGPIO();
    FT800_configDisplay();                   
    FT800_configTouchScreen();
    FT800_configTouchScreenInt();

    FT800_Write32(RAM_DL,0x02000000);       // Set the colour which is used when the colour buffer is cleared   
    FT800_Write32(RAM_DL+4,0x26000007);     // Clear the Colour, Stencil and Tag buffers. This will set the screen to the 'clear' colour set above.(C/S/T define which parameters to clear)
    FT800_Write32(RAM_DL+8,0x00000000);     // Display command ends the display list
    FT800_Write32(REG_DLSWAP,0x00000002);   // Writing to the DL_SWAP register...value 10 means render after last frame complete     

}

