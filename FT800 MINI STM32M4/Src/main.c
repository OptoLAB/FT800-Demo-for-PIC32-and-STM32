
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2021 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"

/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "FT800_Graphics.h"
#include "FT800_Colors.h"
#include "FT800_Audio.h"
#include "FT800_SD.h"

#include "fatfs.h"
#include "user_diskio.h"
#include "ff.h"

//PUT EXTERN IN FRON OF HSPI1 and HSPI2 AFTER CUBE REGENERATION!
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

//MINI BOARD BUILTIN LEDs
//Set as output in CubeMX
#define DATA_LED(bit) ((bit==1)?(GPIOC->BSRR=(GPIO_PIN_12)):(GPIOC->BSRR=(uint32_t)(GPIO_PIN_12<<16)))
#define STAT_LED(bit) ((bit==1)?(GPIOC->BSRR=(GPIO_PIN_13)):(GPIOC->BSRR=(uint32_t)(GPIO_PIN_13<<16)))
//OPTOLAB BOARD BUILTIN LEDs
//Set as output in CubeMX
#define D5_LED(bit) ((bit==1)?(GPIOB->BSRR=(GPIO_PIN_0)):(GPIOB->BSRR=(uint32_t)(GPIO_PIN_0<<16)))
#define D6_LED(bit) ((bit==1)?(GPIOB->BSRR=(GPIO_PIN_1)):(GPIOB->BSRR=(uint32_t)(GPIO_PIN_1<<16)))
//--------------------------------------

#define MAIN_MENU   (0x01|0x80)
#define PRIMITIVES  (0x02|0x80)
#define BARS        (0x03|0x80)
#define KNOBS       (0x04|0x80)
#define GRADIENT    (0x05|0x80)
#define KEYS        (0x06|0x80)
#define SOUND       (0x07|0x80)
#define BMP         (0x08|0x80)
#define WAV         (0x09|0x80)
#define JPG         (0x0A|0x80)
#define TRANSFORM   (0x0B|0x80)
#define SKETCH      (0x0C|0x80)
#define SCRSAVER    (0x0D|0x80)

#define SLIDER      0x01
#define SCROLL_V    0x02
#define SCROLL_H    0x03
#define DIAL        0x04
#define TOGGLE      0x05
#define KEY         0x06
#define NOTES       0x07
#define SLIDER1     0x08
#define BACKWARD    0x09
#define FORWARD     0x0A
#define NEXT        0x0B
#define PREVIOUS    0x0C
#define PLAY        0x0D
#define SLIDER2     0x0E
#define SCROLL_S    0x0F
#define SCROLL_R    0x10
FATFS myFAT={0};
FRESULT res;
FIL myFile;
char chipid = 0, touched =0;

uint8_t menu=MAIN_MENU, previous_menu=MAIN_MENU, tag;
uint16_t tag_value;


//object variables
uint16_t slider_value=500, scroll_v_value=128, scroll_h_value=256, dial_value=0, toggle_value=0, key_value, prev_key_value;
uint16_t ms=0,sec=0,min=59,hour=11;
uint8_t mute=0;
char MYPath[4];
extern Diskio_drvTypeDef  USER_Driver;
char path[20]={0};

//BMP variables
#define NUM_OF_BMPS 5
const char *bmp_folder="BMP";
const char *bmps[NUM_OF_BMPS]={"im1.bmp","im2.bmp","im3.bmp","im4.bmp","im5.bmp"};
uint8_t bmp_num=1;


//BMP variables
#define NUM_OF_JPGS 5
const char *jpg_folder="JPG";
const char *jpgs[NUM_OF_JPGS]={"jpg1.jpg","jpg2.jpg","jpg3.jpg","jpg4.jpg","jpg5.jpg"};
uint8_t jpg_num=1;

int16_t scale_factor=0, rotate_factor=0;
uint16_t img_width, img_height;
uint8_t img_bytes;

//WAV variables
#define NUM_OF_WAVS 4
const char *wav_folder="WAV";
const char *wavs[NUM_OF_WAVS]={"bells.wav", "dixie.wav","laugh.wav","cowboy.wav"};
uint16_t wav_format, wav_channels, wav_bpc;
uint32_t wav_sample_rate, wav_size;
uint8_t wav_num=0;

uint8_t new_file=0;

char wallpaper[20];
char wallpaper_folder[20];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint8_t getNote(char key)
{
    uint8_t note=0;

    if(key=='C')note=72;
    if(key=='c')note=73;
    if(key=='D')note=74;
    if(key=='d')note=75;
    if(key=='E')note=76;
    if(key=='F')note=77;
    if(key=='f')note=78;
    if(key=='G')note=79;
    if(key=='g')note=80;
    if(key=='A')note=81;
    if(key=='a')note=82;
    if(key=='B')note=83;

    return note;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  //Test LEDs
  DATA_LED(1); STAT_LED(1);
  D5_LED(1); D6_LED(1);
  delay_ms(1000);
  DATA_LED(0); STAT_LED(0);
  D5_LED(0); D6_LED(0);

  FATFS_UnLinkDriver(USERPath);
  f_mount(0, 0, 1);

  FT800_init();
  HAL_Delay(50);

  FATFS_LinkDriver(&USER_Driver, USERPath);
  res=f_mount(&myFAT,"",0);

  FT800_drawLogo();
  FT800_waitLogo();

  FT800_startNewList();
  FT800_setBackgroundColor(DARKGRAY);
  FT800_clear(CLEAR_ALL);
  FT800_runTouchCalibration();
  FT800_endOfList();

  strcpy(wallpaper_folder,bmp_folder);
  strcpy(wallpaper,bmps[4]);
  sprintf((char*)path, "%s/%s",wallpaper_folder, wallpaper);
  FT800_loadBMPfromSD(0,path, &img_width, &img_height, &img_bytes);
  delay_ms(50);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      switch(menu)
      {
          case MAIN_MENU:

              if(previous_menu==WAV||previous_menu==TRANSFORM||previous_menu==SCRSAVER||previous_menu==SKETCH)
              {
                  FT800_finishList();
                  FT800_startNewList();
                  FT800_setBackgroundColor(BLACK);
                  FT800_clear(CLEAR_ALL);
                  FT800_stop();
                  FT800_endOfList();
                  sprintf((char*)path, "%s/%s",wallpaper_folder, wallpaper);
                  if(!strcmp(wallpaper_folder,bmp_folder))
                      FT800_loadBMPfromSD(0,path, &img_width, &img_height, &img_bytes);
                  else
                      FT800_loadJPGfromSD(0,path,&img_width,&img_height);
              }
              previous_menu=MAIN_MENU;


              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(BLACK);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);
              FT800_bitmapSource(0);
              FT800_bitmapLayout(RGB565, img_width*img_bytes, img_height);
              FT800_bitmapSize(NEAREST,BORDER,BORDER, img_width, img_height);
              FT800_bitmapBegin();
              FT800_Vertex2II(0,0,0,0);

              FT800_setColorA(50);
              FT800_drawScrollBar(450, 20, 20, 200, DARKGRAY, WHITE, OPT_3D, scroll_v_value, 28, 256, SCROLL_V);
              FT800_drawScrollBar(20, 240, 400, 20, DARKGRAY, WHITE, OPT_3D, scroll_h_value, 28, 512, SCROLL_H);
              int16_t x0=scroll_h_value-256;
              int16_t y0=scroll_v_value-128;
              FT800_drawScissorXY(0, 0);
              FT800_drawScissorSize(440, 230);
              FT800_setColorA(200);
              FT800_drawButton(10+x0,10+y0,100,60,HOTPINK,23,OPT_3D,"Primitives",BLACK, PRIMITIVES);
              FT800_drawButton(150+x0,10+y0,100,60,LIMEGREEN,23,OPT_3D,"Bars",BLACK, BARS);
              FT800_drawButton(290+x0,10+y0,100,60,TOMATO,23,OPT_3D,"Knobs",BLACK, KNOBS);
              FT800_drawButton(10+x0,90+y0,100,60,INDIGO,23,OPT_3D,"Toggle",WHITE, GRADIENT);
              FT800_drawButton(150+x0,90+y0,100,60,GOLD,23,OPT_3D,"Keys",BLACK, KEYS);
              FT800_drawButton(290+x0,90+y0,100,60,CRIMSON,23,OPT_3D,"Sound",WHITE, SOUND);
              FT800_drawButton(10+x0,170+y0,100,60,YELLOWGREEN,23,OPT_3D,"BMP",BLACK, BMP);
              FT800_drawButton(150+x0,170+y0,100,60,PLUM,23,OPT_3D,"WAV",BLACK, WAV);
              FT800_drawButton(290+x0,170+y0,100,60,AQUAMARINE,23,OPT_3D,"JPG",BLACK, JPG);
              FT800_drawButton(10+x0,250+y0,100,60,KHAKI,23,OPT_3D,"Transform",BLACK, TRANSFORM);
              FT800_drawButton(150+x0,250+y0,100,60,TURQUOISE,23,OPT_3D,"Sketch",BLACK, SKETCH);
              FT800_drawButton(290+x0,250+y0,100,60,VIOLET,23,OPT_3D,"Scr. Saver",BLACK, SCRSAVER);
              FT800_setColorA(255);


              FT800_endOfList();
              break;
          case PRIMITIVES:
              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(DARKGRAY);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);

              short xs[10]={0, 50, 100, 150, 200, 250, 300, 350, 400, 472};
              short ys[10]={0, 200, 10, 50, 100, 150, 20, 40, 100, 0};
              FT800_drawEdgeLineStrip(xs, ys, 10, 'A', DARKGRAY);
              FT800_drawEdgeLineStrip(xs, ys, 10, 'B', LIGHTGRAY);
              FT800_drawLineStrip(xs, ys, 10,BLACK,80);
              FT800_drawPoint(300, 136, YELLOW, 1000);
              FT800_drawLine(30,50,400,200,BLUE,320);
              FT800_setColorA(150);
              FT800_drawRectangle(10,100,200,200,GREEN,40);
              FT800_drawPoint(400, 220, RED, 400);
              FT800_setColorA(255);
              FT800_drawLine(30,250,400,50,CYAN,80);
              FT800_drawChar(310,200,25,MAGENTA,'A');
              FT800_drawChar(330,200,31,MAGENTA,'A');

              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 primitives: points, lines, rectangles");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);

              FT800_endOfList();
              break;
          case BARS:
              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(DARKGRAY);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);

              FT800_drawProgressBar(20, 200, 440, 20, OPT_3D, slider_value, 1024, GREEN, LIGHTGRAY,0);
              FT800_drawDecimalNumb(200, 120, 31, OPT_FLAT, slider_value, YELLOW);
              FT800_drawSlider(20, 60, 440, 20, OPT_3D, slider_value, 1024, BLUE, WHITE, WHITE, SLIDER);

              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 slider & progress bar");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);

              FT800_endOfList();
              break;
          case KNOBS:
              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(DARKGRAY);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);

              FT800_drawDial(85, 110, 65, OPT_3D, dial_value, BLUE, YELLOW, DIAL);
              FT800_drawGauge(235, 110, 65, OPT_3D, 5, 5, dial_value>>6, 1024, ORANGE, DARKGRAY,0);
              FT800_drawClock(385, 110, 65, RED, OPT_3D, hour, min, sec, ms, WHITE,0);
              FT800_drawDecimalNumb(200, 210, 31, OPT_FLAT, dial_value>>6, YELLOW);
              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 dial, gauge & clock");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);

              FT800_endOfList();
              break;
          case GRADIENT:
              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(DARKGRAY);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);

              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 Gradient and Toggle");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);
              uint32_t c1, c2;
              if(toggle_value>32768)
              {
                  FT800_drawToggle(50, 90, 50, 28, OPT_3D, 65535, "on", DARKGRAY, ORANGE, BLACK,TOGGLE);
                  c1=RED;
                  c2=GREEN;
              }
              else
              {
                  FT800_drawToggle(50, 90, 50, 28, OPT_3D, 0, "off", DARKGRAY, ORANGE, BLACK,TOGGLE);
                  c1=GREEN;
                  c2=RED;
              }
              FT800_drawScissorXY(30, 150);
              FT800_drawScissorSize(410, 90);
              FT800_drawGradient(30, 150, c1, 440, 150, c2);

              FT800_endOfList();
              break;
          case KEYS:
              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(DARKGRAY);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);

              key_value=FT800_Read8(REG_TOUCH_TAG);
              FT800_drawKeys(30, 150, 400, 50, LIGHTGRAY, 25, key_value, "ABCDEFGH", BLUE, KEYS);
              FT800_drawKeys(55, 202, 350, 50, LIGHTGRAY, 25, key_value, "1234567", BLUE, KEYS);
              if(key_value)FT800_drawChar(220,50,31,ORANGE,key_value);
              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 keys");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);

              FT800_endOfList();
              break;
          case SOUND:
              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(DARKGRAY);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);
              mute=1;

              prev_key_value=key_value;
              key_value=FT800_Read8(REG_TOUCH_TAG);

              FT800_drawKeys(30, 170, 410, 100, WHITE, 25, key_value, "CDEFGAB", BLACK, NOTES);
              FT800_drawKeys(30+30, 130, 110, 60, BLACK, 25, key_value, "cd", WHITE, NOTES);
              FT800_drawKeys(30+180+30, 130, 156, 60, BLACK, 25, key_value, "fga", WHITE, NOTES);
              if(key_value)FT800_drawChar(350,30,31,ORANGE,key_value);
              FT800_drawText(40, 60, 18, ORANGE, OPT_FLAT, "Volume");
              FT800_drawSlider(40, 90, 390, 10, OPT_3D, slider_value, 1024, ORANGE, DARKGRAY, WHITE, SLIDER1);


              FT800_setSoundVolume(slider_value>>2);
              if(key_value!=prev_key_value)
              {

                  if(key_value)
                      FT800_setSoundEffect(getNote(key_value),0x02);
                  else
                      FT800_setSoundEffect(getNote(key_value),0x00);
                  FT800_playSound(1);

              }
              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 sound synthesizer");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);


              FT800_endOfList();
              break;
          case BMP:
              if((previous_menu==MAIN_MENU)||new_file)
              {
                  new_file=0;
                  FT800_finishList();
                  FT800_startNewList();
                  FT800_setBackgroundColor(BLACK);
                  FT800_clear(CLEAR_ALL);
                  FT800_drawText(205, 20, 23, WHITE, OPT_FLAT, "Loading...");
                  FT800_drawAnimSpinner(240,136,0,1);
                  FT800_endOfList();
                  sprintf((char*)path, "%s/%s",bmp_folder, bmps[bmp_num]);
                  FT800_loadBMPfromSD(0,path , &img_width, &img_height, &img_bytes);
                  strcpy(wallpaper_folder,bmp_folder);
                  strcpy(wallpaper,bmps[bmp_num]);
              }
              previous_menu=BMP;

              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(BLACK);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);

              FT800_bitmapSource(0);
              FT800_bitmapLayout(RGB565, img_width*img_bytes, img_height);
              FT800_bitmapSize(NEAREST,BORDER,BORDER, img_width, img_height);
              FT800_bitmapBegin();
              FT800_Vertex2II(0,0,0,0);

              FT800_setColorA(100);
              FT800_drawButton(445,5,30,30,LIGHTGRAY,28,OPT_3D,"X",BLACK, MAIN_MENU);
              FT800_drawButton(190,230,40,40,LIGHTGRAY,30,OPT_3D,"<",BLACK, BACKWARD);
              FT800_drawButton(250,230,40,40,LIGHTGRAY,30,OPT_3D,">",BLACK, FORWARD);
              FT800_setColorA(255);

              FT800_endOfList();
              break;
          case WAV:
              if(previous_menu==MAIN_MENU)
              {
                  FT800_finishList();
                  FT800_startNewList();
                  FT800_setBackgroundColor(BLACK);
                  FT800_clear(CLEAR_ALL);
                  FT800_endOfList();
                  sprintf((char*)path, "%s/%s",wav_folder, wavs[wav_num]);
                  FT800_loadWAVfromSD(0, path, &wav_format, &wav_channels, &wav_sample_rate, &wav_bpc, &wav_size);
                  FT800_setPlaybackVolume(128);
                  slider_value=512;
              }
              previous_menu=WAV;

              if(new_file)
              {
                  new_file=0;
                  sprintf((char*)path, "%s/%s", wav_folder, wavs[wav_num]);
                  FT800_loadWAVfromSD(0, path, &wav_format, &wav_channels, &wav_sample_rate, &wav_bpc, &wav_size);
              }

              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(ORANGE);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);
              FT800_drawText(10, 10, 18, BLACK, OPT_FLAT, wavs[wav_num]);
              FT800_drawText(20, 30, 18, DARKGRAY, OPT_FLAT, "FORMAT:  (0-PCM, 1-uLAW, 2-ADPCM)");
              FT800_drawText(20, 50, 18, DARKGRAY, OPT_FLAT, "CHANNELS:  (1-MONO, 2-STEREO)");
              FT800_drawText(20, 70, 18, DARKGRAY, OPT_FLAT, "SAMPLE RATE [Hz]:");
              FT800_drawText(20, 90, 18, DARKGRAY, OPT_FLAT, "BITS:");
              FT800_drawText(20, 110, 18, DARKGRAY, OPT_FLAT, "BYTES[KB]:     (MAX 256)");
              FT800_drawDecimalNumb(80, 30, 18, OPT_FLAT, wav_format, BLACK);
              FT800_drawDecimalNumb(95, 50, 18, OPT_FLAT, wav_channels, BLACK);
              FT800_drawDecimalNumb(160, 70, 18, OPT_FLAT, wav_sample_rate, BLACK);
              FT800_drawDecimalNumb(65, 90, 18, OPT_FLAT, wav_bpc, BLACK);
              FT800_drawDecimalNumb(95, 110, 18, OPT_FLAT, wav_size>>10, BLACK);

              FT800_drawSlider(40, 160, 390, 10, OPT_3D, slider_value, 1024, DARKGRAY, LIGHTGRAY, WHITE, SLIDER2);
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);
              FT800_drawButton(170,200,60,60,DARKGRAY,30,OPT_3D,"<",ORANGE, PREVIOUS);
              FT800_drawButton(260,200,60,60,DARKGRAY,30,OPT_3D,">",ORANGE, NEXT);
              FT800_drawButton(320,70,100,60,DARKGRAY,28,OPT_3D,"PLAY",ORANGE, PLAY);

              FT800_endOfList();
              break;
          case JPG:
              if((previous_menu==MAIN_MENU)||new_file)
              {
                  new_file=0;
                  FT800_finishList();
                  FT800_startNewList();
                  FT800_setBackgroundColor(BLACK);
                  FT800_clear(CLEAR_ALL);
                  FT800_drawText(205, 20, 23, WHITE, OPT_FLAT, "Loading...");
                  FT800_drawAnimSpinner(240,136,0,1);
                  FT800_endOfList();
                  sprintf((char*)path, "%s/%s", jpg_folder, jpgs[jpg_num]);
                  FT800_loadJPGfromSD(0,path,&img_width,&img_height);
                  strcpy(wallpaper_folder,jpg_folder);
                  strcpy(wallpaper,jpgs[jpg_num]);
              }
              previous_menu=JPG;

              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(BLACK);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);
              FT800_stop();
              FT800_bitmapSource(0);
              FT800_bitmapLayout(RGB565, img_width*2, img_height);
              FT800_bitmapSize(NEAREST,BORDER,BORDER, img_width, img_height);
              FT800_bitmapBegin();
              FT800_Vertex2II(0,0,0,0);

              FT800_setColorA(100);
              FT800_drawButton(445,5,30,30,LIGHTGRAY,28,OPT_3D,"X",BLACK, MAIN_MENU);
              FT800_drawButton(190,230,40,40,LIGHTGRAY,30,OPT_3D,"<",BLACK, BACKWARD);
              FT800_drawButton(250,230,40,40,LIGHTGRAY,30,OPT_3D,">",BLACK, FORWARD);
              FT800_setColorA(255);

              FT800_endOfList();
              break;
          case TRANSFORM:
              if(previous_menu==MAIN_MENU)
              {
                  FT800_finishList();
                  FT800_startNewList();
                  FT800_setBackgroundColor(BLACK);
                  FT800_clear(CLEAR_ALL);
                  FT800_endOfList();
                  sprintf((char*)path, "%s/%s",bmp_folder, "mario.bmp");
                  FT800_loadBMPfromSD(0,path , &img_width, &img_height, &img_bytes);
              }
              previous_menu=TRANSFORM;

              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(BLACK);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);

              FT800_drawScrollBar(20, 55, 20, 200, DARKGRAY, ORANGE, OPT_3D, scale_factor, 1, 4, SCROLL_S);
              FT800_drawScrollBar(450, 55, 20, 200, DARKGRAY, ORANGE, OPT_3D, rotate_factor, 10, 1024, SCROLL_R);
              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 scale and rotate");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);


              FT800_loadIdentity();
              FT800_scale(scale_factor+1,scale_factor+1);
              FT800_translate((img_width>>1),(img_height>>1));
              FT800_rotate((rotate_factor*360)/1023);
              FT800_translate(-(img_width>>1),-(img_height>>1));
              FT800_setMatrix();


              FT800_bitmapSource(0);
              FT800_bitmapLayout(RGB565, img_width*img_bytes, img_height);
              FT800_bitmapSize(NEAREST,BORDER,BORDER, img_width*(scale_factor+1), img_height*(scale_factor+1));
              FT800_bitmapBegin();
              FT800_Vertex2II((DISPLAY_WIDTH>>1)-(((scale_factor+1)*img_width)>>1),(DISPLAY_HEIGHT>>1)-(((scale_factor+1)*img_height)>>1),0,0);

              FT800_endOfList();
              break;
          case SKETCH:
              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(BLACK);
              FT800_clear(CLEAR_ALL);
              FT800_tagMask(0);
              if(previous_menu==MAIN_MENU)
              {
                  FT800_writeMemZero(0, 480 * 272 * 2);
              }
              previous_menu=SKETCH;
              FT800_drawText(5, 5, 18, ORANGE, OPT_FLAT, "FT800 sketch");
              FT800_drawButton(445,5,30,30,RED,28,OPT_3D,"X",WHITE, MAIN_MENU);


                FT800_drawSketch(0, 0, 480, 272, 0, L1);



              FT800_bitmapSource(0);
              FT800_bitmapLayout(L1, 480/8, 272);
              FT800_bitmapSize(NEAREST,BORDER,BORDER, 480, 272); //92 48
              FT800_bitmapBegin();
              FT800_Vertex2II(0,0,0,0);

              FT800_endOfList();
              break;
          case SCRSAVER:
              if(previous_menu==MAIN_MENU)
              {
                  FT800_finishList();
                  FT800_startNewList();
                  FT800_setBackgroundColor(BLACK);
                  FT800_clear(CLEAR_ALL);
                  FT800_endOfList();
                  sprintf((char*)path, "%s/%s",bmp_folder, "mario.bmp");
                  FT800_loadBMPfromSD(0,path , &img_width, &img_height, &img_bytes);
              }
              previous_menu=SCRSAVER;

              FT800_finishList();
              FT800_startNewList();
              FT800_setBackgroundColor(BLACK);
              FT800_clear(CLEAR_ALL);
              FT800_track(0, 0, 480, 272, MAIN_MENU);

              FT800_drawScreensaver();

              FT800_loadIdentity();
              FT800_scale(2,2);
              FT800_setMatrix();

              FT800_bitmapSource(0);
              FT800_bitmapLayout(RGB565, img_width*img_bytes, img_height);
              FT800_bitmapSize(NEAREST,BORDER,BORDER, img_width*2, img_height*2);
              FT800_bitmapBegin();

              FT800_macro(0);
              FT800_endOfList();

              break;
      }
      if(touched)
      {
          touched=0;
          FT800_clearIntFlags();
          tag = FT800_readTag();

          if(tag)
          {
              if(tag&0x80)
              {
                  mute=0;
                  menu=tag;
              }
              else
              {
                  switch(tag)
                  {
                      case SLIDER:
                          slider_value=FT800_readValue()>>6;
                          break;
                      case SCROLL_V:
                          scroll_v_value=FT800_readValue()>>8;
                          break;
                      case SCROLL_H:
                          scroll_h_value=FT800_readValue()>>7;
                          break;
                      case DIAL:
                          dial_value=FT800_readValue();
                          break;
                      case TOGGLE:
                          toggle_value=FT800_readValue();
                          break;
                      case KEY:
                          break;
                      case NOTES:
                          break;
                      case SLIDER1:
                          mute=0; slider_value=FT800_readValue()>>6;
                          break;
                      case FORWARD:
                          if(menu==BMP)
                          {
                              if(bmp_num==(NUM_OF_BMPS-1))bmp_num=0;
                              else bmp_num++;
                          }
                          if(menu==JPG)
                          {
                              if(jpg_num==(NUM_OF_JPGS-1))jpg_num=0;
                              else jpg_num++;
                          }
                          new_file=1;
                          break;
                        case BACKWARD:
                          if(menu==BMP)
                          {
                              if(bmp_num==0)bmp_num=NUM_OF_BMPS-1;
                              else bmp_num--;
                          }
                          if(menu==JPG)
                          {
                              if(jpg_num==0)jpg_num=NUM_OF_JPGS-1;
                              else jpg_num--;
                          }
                          new_file=1;
                          break;
                      case NEXT:
                          if(wav_num==(NUM_OF_WAVS-1))wav_num=0;
                          else wav_num++;
                          new_file=1;
                          break;
                      case PREVIOUS:
                          if(wav_num==0)wav_num=NUM_OF_WAVS-1;
                          else wav_num--;
                          new_file=1;
                          break;
                      case PLAY:
                          FT800_configurePlayback(0, wav_size, wav_sample_rate, wav_format, 0);
                          FT800_playPlayback(1);
                          break;
                      case SLIDER2:
                          slider_value=FT800_readValue()>>6;
                          FT800_setPlaybackVolume(slider_value>>2);
                          break;
                      case SCROLL_S:
                          scale_factor=FT800_readValue()>>14;
                          break;
                      case SCROLL_R:
                          rotate_factor=FT800_readValue()>>6;
                          break;
                  }
              }
              if(!mute)
              {
                  FT800_setSoundVolume(255);
                  FT800_setSoundEffect(0x6C,0x50);
                  FT800_playSound(1);
                  //while(FT800_isSoundPlaying());
              }

          }
      }
      //for clock testing
      ms+=20;
      if(ms==1000)
      {
          ms=0;
          sec++;
          if(sec==60)
          {
              sec=0;
              min++;
              if(min==60)
              {
                  min=0;
                  hour++;
                  if(hour==12)hour=0;
              }
          }
      }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SPI2 init function */
static void MX_SPI2_Init(void)
{

  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB12 PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){
	if(GPIO_PIN == GPIO_PIN_9){
		touched = 1;
	}
	else{
		__NOP();
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
