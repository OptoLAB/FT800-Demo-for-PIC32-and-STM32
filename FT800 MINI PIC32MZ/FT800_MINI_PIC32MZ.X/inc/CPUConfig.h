/* 
 * Author: J. Bajic
 */

#ifndef CPUCONFIG_H
#define	CPUCONFIG_H

#define USE_MIKROE_BOOTLOADER //comment this line if not using mikroe bootloader 
// PIC32MZ1024EFH064 Configuration Bit Settings

#pragma config USERID = 0x0             //USER ID = 0x0000
#pragma config FMIIEN = ON              // Ethernet RMII/MII Enable = MII Enabled
#pragma config FETHIO = OFF             // Ethernet I/O Pin Select = Alternate Ethernet I/O
#pragma config PGL1WAY = OFF            // Permission Group Lock One Way Configuration = Allow multiple reconfigurations
#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration = Allow multiple reconfigurations
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration = Allow multiple reconfigurations
#pragma config FUSBIDIO = ON            // USB USBID Selection = Controlled by the USB Module
// DEVCFG2
#pragma config FPLLIDIV = DIV_3         // System PLL Input Divider = 3x Divider
#pragma config FPLLRNG = RANGE_8_16_MHZ // System PLL Input Range = 8-16 MHz Input
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection = POSC is input to the System PLL
#pragma config FPLLMULT = MUL_50        // System PLL Multiplier = PLL Multiply by 50
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider = 2x Divider
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection = USB PLL input is 24 MHz
// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits = System PLL
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval = Window/Interval value is 127/128 counter value
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable = Disable SOSC
#pragma config IESO = OFF               // Internal/External Switch Over = Disabled
#pragma config POSCMOD = EC             // Primary Oscillator Configuration = External clock mode
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin = Disabled
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection = Clock Switch Disabled - CSD, FSCM Disabled -CMD
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler = 1:1048576
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming = WDT stops during Flash programming
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode = Watchdog Timer is in non-Window mode
#pragma config FWDTEN = OFF             // Watchdog Timer Enable = WDT Disabled
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size = Window size is 25%
#pragma config DMTCNT = DMT31           // Deadman Timer Count Selection = 2^31 (2147483648)
#pragma config FDMTEN = OFF             // Deadman Timer Enable = Deadman Timer is disabled
// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable = Debugger is disabled
#pragma config JTAGEN = OFF             // JTAG Enable = JTAG Disabled
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select = Communicate on PGEC2/PGED2
#pragma config TRCEN = OFF              // Trace Enable = Trace features in the CPU are disabled
#pragma config BOOTISA = MIPS32         // Boot ISA Selection = Boot code and Exception code is MIPS32
#pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration = ECC and Dynamic ECC are disabled (ECCCON bits are writable)
#pragma config FSLEEP = OFF             // Flash Sleep Mode = Flash is powered down when the device is in Sleep mode
#pragma config DBGPER = PG_ALL          // Debug Mode CPU Access Permission = Allow CPU access to all permission regions 
#pragma config SMCLR = MCLR_NORM        // Soft Master Clear Enable bit = MCLR pin generates a normal system Reset
#pragma config SOSCGAIN = GAIN_2X       // Secondary Oscillator Gain Control bits = 2x gain setting
#pragma config SOSCBOOST = ON           // Secondary Oscillator Boost Kick Start Enable bit = Boost the kick start of the oscillator
#pragma config POSCGAIN = GAIN_2X       // Primary Oscillator Gain Control bits = 2x gain setting
#pragma config POSCBOOST = ON           // Primary Oscillator Boost Kick Start Enable bit = Boost the kick start of the oscillator
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot = Normal EJTAG functionality
// DEVCP0
#pragma config CP = OFF                 // Code Protect = Protection Disabled
// SEQ3
#pragma config TSEQ = 0xFFFF            // Boot Flash True Sequence Number (Enter Hexadecimal value)
#pragma config CSEQ = 0xFFFF            // Boot Flash Complement Sequence Number (Enter Hexadecimal value)

#endif	/* CPUCONFIG_H */

