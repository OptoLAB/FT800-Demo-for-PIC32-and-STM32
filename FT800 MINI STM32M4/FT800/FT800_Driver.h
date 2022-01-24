#ifndef FT800_DRIVER_H    /* Guard against multiple inclusion */
#define FT800_DRIVER_H

#include "FT800_Port.h"
#include "FT800_Config.h"

//CMD
#define CMDBUF_SIZE             4096UL
#define CMD_APPEND              4294967070UL
#define CMD_BGCOLOR             4294967049UL
#define CMD_BITMAP_TRANSFORM    4294967073UL
#define CMD_BUTTON              4294967053UL
#define CMD_CALIBRATE           4294967061UL
#define CMD_CLOCK               4294967060UL
#define CMD_COLDSTART           4294967090UL
#define CMD_CRC                 4294967043UL
#define CMD_DIAL                4294967085UL
#define CMD_DLSTART             4294967040UL
#define CMD_EXECUTE             4294967047UL
#define CMD_FGCOLOR             4294967050UL
#define CMD_GAUGE               4294967059UL
#define CMD_GETMATRIX           4294967091UL
#define CMD_GETPOINT            4294967048UL
#define CMD_GETPROPS            4294967077UL
#define CMD_GETPTR              4294967075UL
#define CMD_GRADCOLOR           4294967092UL
#define CMD_GRADIENT            4294967051UL
#define CMD_HAMMERAUX           4294967044UL
#define CMD_IDCT                4294967046UL
#define CMD_INFLATE             4294967074UL
#define CMD_INTERRUPT           4294967042UL
#define CMD_KEYS                4294967054UL
#define CMD_LOADIDENTITY        4294967078UL
#define CMD_LOADIMAGE           4294967076UL
#define CMD_LOGO                4294967089UL
#define CMD_MARCH               4294967045UL
#define CMD_MEMCPY              4294967069UL
#define CMD_MEMCRC              4294967064UL
#define CMD_MEMSET              4294967067UL
#define CMD_MEMWRITE            4294967066UL
#define CMD_MEMZERO             4294967068UL
#define CMD_NUMBER              4294967086UL
#define CMD_PROGRESS            4294967055UL
#define CMD_REGREAD             4294967065UL
#define CMD_ROTATE              4294967081UL
#define CMD_SCALE               4294967080UL
#define CMD_SCREENSAVER         4294967087UL
#define CMD_SCROLLBAR           4294967057UL
#define CMD_SETFONT             4294967083UL
#define CMD_SETMATRIX           4294967082UL
#define CMD_SKETCH              4294967088UL
#define CMD_SLIDER              4294967056UL
#define CMD_SNAPSHOT            4294967071UL
#define CMD_SPINNER             4294967062UL
#define CMD_STOP                4294967063UL
#define CMD_SWAP                4294967041UL
#define CMD_TEXT                4294967052UL
#define CMD_TOGGLE              4294967058UL
#define CMD_TOUCH_TRANSFORM     4294967072UL
#define CMD_TRACK               4294967084UL
#define CMD_TRANSLATE           4294967079UL
//RAM
#define RAM_CMD                 1081344UL
#define RAM_DL                  1048576UL
#define RAM_G                   0UL
#define RAM_PAL                 1056768UL
#define RAM_REG                 1057792UL      
//REGs
#define REG_ANALOG              1058104UL
#define REG_ANA_COMP            1058160UL
#define REG_BIST_CMD            1058124UL
#define REG_BIST_EN             1058132UL
#define REG_BIST_RESULT         1058128UL
#define REG_BUSYBITS            1058008UL
#define REG_CLOCK               1057800UL
#define REG_CMD_DL              1058028UL
#define REG_CMD_READ            1058020UL
#define REG_CMD_WRITE           1058024UL
#define REG_CPURESET            1057820UL
#define REG_CRC                 1058152UL
#define REG_CSPREAD             1057892UL
#define REG_CYA0                1058000UL
#define REG_CYA1                1058004UL
#define REG_CYA_TOUCH           1058100UL
#define REG_DATESTAMP           1058108UL
#define REG_DITHER              1057884UL
#define REG_DLSWAP              1057872UL
#define REG_FRAMES              1057796UL
#define REG_FREQUENCY           1057804UL
#define REG_GPIO                1057936UL
#define REG_GPIO_DIR            1057932UL
#define REG_HCYCLE              1057832UL
#define REG_HOFFSET             1057836UL
#define REG_HSIZE               1057840UL
#define REG_HSYNC0              1057844UL
#define REG_HSYNC1              1057848UL
#define REG_ID                  1057792UL
#define REG_INT_EN              1057948UL
#define REG_INT_FLAGS           1057944UL
#define REG_INT_MASK            1057952UL
#define REG_MACRO_0             1057992UL
#define REG_MACRO_1             1057996UL
#define REG_MARCH_ACC           1058144UL
#define REG_MARCH_DIR           1058136UL
#define REG_MARCH_OP            1058140UL
#define REG_MARCH_WIDTH         1058148UL
#define REG_OUTBITS             1057880UL
#define REG_PCLK                1057900UL
#define REG_PCLK_POL            1057896UL
#define REG_PLAY                1057928UL
#define REG_PLAYBACK_FORMAT     1057972UL
#define REG_PLAYBACK_FREQ       1057968UL
#define REG_PLAYBACK_LENGTH     1057960UL
#define REG_PLAYBACK_LOOP       1057976UL
#define REG_PLAYBACK_PLAY       1057980UL
#define REG_PLAYBACK_READPTR    1057964UL
#define REG_PLAYBACK_START      1057956UL
#define REG_PWM_DUTY            1057988UL
#define REG_PWM_HZ              1057984UL
#define REG_RENDERMODE          1057808UL
#define REG_ROMSUB_SEL          1058016UL
#define REG_ROTATE              1057876UL
#define REG_SNAPSHOT            1057816UL
#define REG_SNAPY               1057812UL
#define REG_SOUND               1057924UL
#define REG_SWIZZLE             1057888UL
#define REG_TAG                 1057912UL
#define REG_TAG_X               1057904UL
#define REG_TAG_Y               1057908UL
#define REG_TAP_CRC             1057824UL
#define REG_TAP_MASK            1057828UL
#define REG_TOUCH_ADC_MODE      1058036UL
#define REG_TOUCH_CHARGE        1058040UL
#define REG_TOUCH_DIRECT_XY     1058164UL
#define REG_TOUCH_DIRECT_Z1Z2   1058168UL
#define REG_TOUCH_MODE          1058032UL
#define REG_TOUCH_OVERSAMPLE    1058048UL
#define REG_TOUCH_RAW_XY        1058056UL
#define REG_TOUCH_RZ            1058060UL
#define REG_TOUCH_RZTHRESH      1058052UL
#define REG_TOUCH_SCREEN_XY     1058064UL
#define REG_TOUCH_SETTLE        1058044UL
#define REG_TOUCH_TAG           1058072UL
#define REG_TOUCH_TAG_XY        1058068UL
#define REG_TOUCH_TRANSFORM_A   1058076UL
#define REG_TOUCH_TRANSFORM_B   1058080UL
#define REG_TOUCH_TRANSFORM_C   1058084UL
#define REG_TOUCH_TRANSFORM_D   1058088UL
#define REG_TOUCH_TRANSFORM_E   1058092UL
#define REG_TOUCH_TRANSFORM_F   1058096UL
#define REG_TRACKER             1085440UL
#define REG_TRIM                1058156UL
#define REG_VCYCLE              1057852UL
#define REG_VOFFSET             1057856UL
#define REG_VOL_PB              1057916UL
#define REG_VOL_SOUND           1057920UL
#define REG_VSIZE               1057860UL
#define REG_VSYNC0              1057864UL
#define REG_VSYNC1              1057868UL            
//GPU
#define FT_GPU_INTERNAL_OSC     0x48 //default
#define FT_GPU_EXTERNAL_OSC     0x44
#define FT_GPU_PLL_48M          0x62  //default
#define FT_GPU_PLL_36M          0x61
#define FT_GPU_PLL_24M          0x64
#define FT_GPU_ACTIVE_M         0x00  
#define FT_GPU_STANDBY_M        0x41//default
#define FT_GPU_SLEEP_M          0x42
#define FT_GPU_POWERDOWN_M      0x50
#define FT_GPU_CORE_RESET       0x68
/*******************************************/

#define READ    0x00
#define CONFIG  0x40
#define WRITE   0x80

//-----------------CMD Offset---------------------------
void CMD_Offset_Inc(uint8_t command_size);
void set_CMD_Offset(uint16_t offset);
uint16_t get_CMD_Offset(void);
//-------------------WRITE------------------------------
void FT800_WriteAddress(uint32_t address, uint8_t mode);
void FT800_Write8(uint32_t address, uint8_t data);
void FT800_Write16(uint32_t address, uint16_t data);
void FT800_Write32(uint32_t address, uint32_t data);
//-------------------READ-------------------------------
uint8_t FT800_Read8(uint32_t address);
uint16_t FT800_Read16(uint32_t address);
uint32_t FT800_Read32(uint32_t address);
//------------------CONFIG------------------------------
void FT800_configGPU(void);
void FT800_configDisplay(void);
void FT800_setBacklight(uint8_t pwm_duty);
void FT800_configTouchScreen(void);
void FT800_clearIntFlags(void);
void FT800_configTouchScreenInt(void);
void FT800_configGPIO(void);
//------------------INIT------------------------------
void FT800_init(void);


#endif /* FT800_DRIVER_H */

