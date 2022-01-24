/* ************************************************************************** */

/* ************************************************************************** */

#ifndef FT800_CONFIG_H    /* Guard against multiple inclusion */
#define FT800_CONFIG_H

#include "my_delays.h"
//-------------------------------------------------------------------------------
//GPU
//-------------------------------------------------------------------------------
#define GPU_FREQ         (48000000ULL) // FT800 frequency - set in FT800_configGPU()  
//-------------------------------------------------------------------------------
//DISPLAY
//-------------------------------------------------------------------------------
#define DISPLAY_FPS      (60U)     // frame rate

#define DISPLAY_WIDTH    (480U)    // horizontal resolution
#define DISPLAY_HBP      (41U)     // horizontal back porch
#define DISPLAY_HFP      (25U)     // horizontal front porch
#define DISPLAY_HSLEN    (2U)      // horizontal sync length
   
#define DISPLAY_HEIGHT   (272U)    // vertical resolution
#define DISPLAY_VBP      (10U)     // vertical back porch
#define DISPLAY_VFP      (8U)      // vertical front porch
#define DISPLAY_VSLEN    (2U)      // vertical sync length

#define DISPLAY_PCLK_POL (1)       // 0= data clocked on PCLK rising edge, 1=data clocked on PCLK falling edge
#define DISPLAY_SWIZZLE  0       // B[7:2] G[7:2] R[7:2] - arrangement of output RGB pins
          
#define	DISPLAY_HSYNC_PERIOD    (DISPLAY_HSLEN + DISPLAY_HBP + DISPLAY_WIDTH  + DISPLAY_HFP)
#define	DISPLAY_VSYNC_PERIOD    (DISPLAY_VSLEN + DISPLAY_VBP + DISPLAY_HEIGHT  + DISPLAY_VFP)   
#define DISPLAY_SYNC_PERIOD     (DISPLAY_VSYNC_PERIOD * DISPLAY_HSYNC_PERIOD)   
#define DISPLAY_PCLK            (GPU_FREQ/DISPLAY_SYNC_PERIOD/(DISPLAY_FPS-1)) 
//-------------------------------------------------------------------------------
//TOUCH SCREEN
//-------------------------------------------------------------------------------
#define TOUCH_SENSITIVITY   (1800)  //touching sensitivity 0x0000-0xFFFF(highest sensitivity)
#define TOUCH_MODE          (3)     // 0-off, 1- single mode, 2-frame mode, 3-continuous mode 
#define TOUCH_ADC_MODE      (1)     //0-Single Ended mode,  1-Differential Mode
#define TOUCH_CHARGE        (6000)  // touch-screen charge time, in the unit of 6 clocks
#define TOUCH_SETTLE        (3)     // touch screen settle time in the unit of 6 clocks
#define TOUCH_OVERSAMPLE    (7)     // 1-15, touch screen oversample factor. The higher value -> more accuracy & more power consumption 
//-------------------------------------------------------------------------------
//FT800 GPIO PINS
//-------------------------------------------------------------------------------
#define GPIO_DIR            (0x83)    // GPIO7-GPIO0, 1=output, 0=input 
#define GPIO_SET            (0x81)    // GPIO7-GPIO0, 1="HI", 0="LO" 
//-------------------------------------------------------------------------------
//DELAY FUNCTION
//-------------------------------------------------------------------------------
#define DELAY(x)            delay_ms(x) 


#endif /* FT800_CONFIG_H */

/* *****************************************************************************
 End of File
 */
