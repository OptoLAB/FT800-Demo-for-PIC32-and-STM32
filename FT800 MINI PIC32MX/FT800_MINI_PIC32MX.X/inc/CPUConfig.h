/* 
 * Author: J. Bajic
 */

#ifndef CPUCONFIG_H
#define	CPUCONFIG_H

#define USE_MIKROE_BOOTLOADER //comment this line if not using mikroe bootloader 
// PIC32MX534F064H Configuration Bit Settings

// DEVCFG3
#pragma config USERID = 0x0             // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config FVBUSONIO = OFF          // VBUS_ON Selection bit = VBUS_ON selection is controlled by Port function
#pragma config FUSBIDIO = ON            // USB USBID Selection bit = USBID pin is controlled by USB module
#pragma config FCANIO = ON              // CAN I/O Pin Selectrion bit = Use default CAN I/O Pins
#pragma config FSRSSEL = PRIORITY_7     // SRS select bits = Assign interrupt priority 7 to a shadow register set (SRS)
// DEVCFG2
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider = PLL Divide by 1
#pragma config UPLLEN = ON              // USB PLL Enable = Enable USB PLL  
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider = 2x Divider
#pragma config FPLLMUL = MUL_20         // PLL Multiplier = 20x Multiplier
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider = 2x Divider
// DEVCFG1
#pragma config FWDTEN = OFF             // Watchdog Timer Enable = WDT Disabled 
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler = 1:1048576
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection = Clock Switch Disabled -CSD, FSCM Disabled=CMD)
#pragma config FPBDIV = DIV_2           // Peripheral Clock Divisor = PBCLK is SYSCLK div 1
#pragma config OSCIOFNC = OFF           // CLKO Enable = CLKO Output is disabled
#pragma config POSCMOD = XT             // Primary Oscillator Configuration = XT osc mode
#pragma config IESO = OFF               // Internal/External Switch Over = Disabled
#pragma config FSOSCEN = ON             // Secondary Oscillator = Enabled
#pragma config FNOSC = PRIPLL           // Oscillator Selection = Primary with PLL module (XT+PLL,HS+PLL,EC+PLL))
// DEVCFG0
#pragma config CP = OFF                 // Code Protect = Protection Disabled
#pragma config BWP = OFF                // Boot Flash Write Protect = Disabled
#pragma config PWP = OFF                // Program Flash Write Protect = 0kB protected
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel = ICE uses PGC2/PGD2
#pragma config DEBUG = OFF              // Background Debugger = Disabled



#endif	/* CPUCONFIG_H */

