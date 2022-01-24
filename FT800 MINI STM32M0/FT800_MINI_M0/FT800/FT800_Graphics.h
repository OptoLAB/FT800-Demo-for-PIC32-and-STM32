/* 
 * File:   FT800_Draw.h
 * Author: Jovan
 *
 * Created on August 1, 2019, 9:15 AM
 */

#ifndef FT800_GPAPHICS_H
#define	FT800_GPAPHICS_H

#include "FT800_Driver.h"

//OPTIONS
#define OPT_3D              0UL
#define OPT_RGB565          0UL
#define OPT_CENTER          1536UL
#define OPT_CENTERX         512UL
#define OPT_CENTERY         1024UL
#define OPT_FLAT            256UL
#define OPT_MONO            1UL
#define OPT_NOBACK          4096UL
#define OPT_NODL            2UL
#define OPT_NOHANDS         49152UL
#define OPT_NOHM            16384UL
#define OPT_NOPOINTER       16384UL
#define OPT_NOSECS          32768UL
#define OPT_NOTICKS         8192UL
#define OPT_RIGHTX          2048UL
#define OPT_SIGNED          256UL

//CLEAR FLAGS
#define CLEAR_TAG           0x01
#define CLEAR_STENCIL       0x02
#define CLEAR_COLOR         0x04
#define CLEAR_ALL           0x07

//DRAWING SETTINGS
#define END                 0x21000000
#define BEGIN               0x1F000000
#define BITMAP              0x00000001
#define POINT               0x00000002
#define LINE                0x00000003
#define LINE_STRIP          0x00000004
#define EDGE_STRIP_R        0x00000005
#define EDGE_STRIP_L        0x00000006
#define EDGE_STRIP_A        0x00000007
#define EDGE_STRIP_B        0x00000008
#define RECT                0x00000009

//BLEND MACROS (openGL)
#define ZERO                0 
#define ONE                 1 
#define SRC_ALPHA           2 
#define DST_ALPHA           3 
#define ONE_MINUS_SRC_ALPHA 4 
#define ONE_MINUS_DST_ALPHA 5

//BITMAMAP TRANSFORMATION
#define BMP_TRANSFORM_A 0x15000000
#define BMP_TRANSFORM_B 0x16000000
#define BMP_TRANSFORM_C 0x17000000
#define BMP_TRANSFORM_D 0x18000000
#define BMP_TRANSFORM_E 0x19000000
#define BMP_TRANSFORM_F 0x1A000000

//BITMAP FILTERING
#define NEAREST     0
#define BILINEAR    1

//BITMAP WRAP MODE
#define BORDER      0
#define REPEAT      1

// BITMAP_LAYOUT
#define ARGB1555    0
#define L1          1
#define L4          2
#define L8          3
#define RGB332      4
#define ARGB2       5
#define ARGB4       6
#define RGB565      7
#define PALETTED    8
#define TEXT8X8     9
#define TEXTVGA     10
#define BARGRAPH    11

void FT800_startNewList(void);
void FT800_endOfList(void);
void FT800_finishList(void);
void FT800_executeCommands(void);
uint16_t FT800_getFreeSpace(void);
void FT800_setBackgroundColor(uint32_t color);
void FT800_clear(uint8_t clr);
void FT800_setColorA(uint8_t alpha);
void FT800_setColorRGB(uint32_t color);
void FT800_setBgColor(uint32_t color);
void FT800_setFgColor(uint32_t color);
void FT800_setGradColor(uint32_t color);
void FT800_setBlendFunc(uint8_t src, uint8_t dst);
void FT800_Vertex2F(int16_t x, int16_t y);
void FT800_Vertex2II(uint16_t x, uint16_t y, uint8_t handle, uint8_t cell);
void FT800_align(uint8_t n);
void FT800_WriteString(const char*s);
//---------------------------------MEM------------------------------------------------------------ //OK
void FT800_writeMemZero(uint32_t pointer, uint32_t number);
void FT800_writeMemSet(uint32_t pointer, uint32_t value, uint32_t number);
void FT800_writeMemCpy(uint32_t source, uint32_t destination);
//------------------------------PRIMITIVES-------------------------------------------------------- //OK
void FT800_drawPoint(int16_t x, int16_t y, uint32_t color, uint16_t size);
void FT800_drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color, uint16_t width);
void FT800_drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color, uint16_t width);
void FT800_drawLineStrip(int16_t x[], int16_t y[],uint16_t num_of_points, uint32_t color, uint16_t width);
void FT800_drawEdgeLineStrip(int16_t x[], int16_t y[], uint16_t num_of_points, uint8_t choice, uint32_t color);
//--------------------------------TEXT-------------------------------------------------------------//OK
void FT800_drawChar(uint16_t x, uint16_t y, uint8_t font, uint32_t color, char c);
void FT800_drawText(int16_t x, int16_t y, uint8_t font, uint32_t color, uint16_t options, const char *s);   
void FT800_drawDecimalNumb(int16_t x, int16_t y, uint8_t font, uint16_t options, uint32_t n, uint32_t color);
//-------------------------------OBJECTS----------------------------------------------------------- //OK
void FT800_drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t colorBG, uint8_t font, uint16_t options, const char*s, uint32_t colorTXT, uint8_t tag);
void FT800_drawClock(int16_t x, int16_t y, uint16_t r, uint32_t colorBG, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms, uint32_t colorNeedle, uint8_t tag);
void FT800_drawGradient(int16_t x0, int16_t y0, uint32_t color0, int16_t x1, int16_t y1, uint32_t color1);
void FT800_drawScissorXY(int16_t x, int16_t y);
void FT800_drawScissorSize(uint16_t w, uint16_t h);
void FT800_drawKeys(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t colorBG, uint8_t font, uint16_t options, const char*s, uint32_t colorTXT, uint8_t tag);
void FT800_drawScrollBar(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t colorBG, uint32_t colorSCR, uint16_t options, uint16_t value, uint16_t size, uint16_t range, uint8_t tag);
void FT800_drawToggle(int16_t x, int16_t y, uint16_t w, uint8_t font, uint16_t options, uint16_t state, const char *s, uint32_t colorKnob, uint32_t colorBCG, uint32_t colorTXT, uint8_t tag);
void FT800_drawSlider(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t value, uint16_t range, uint32_t colorR, uint32_t colorKnob, uint32_t colorL, uint8_t tag);
void FT800_drawProgressBar(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t value, uint16_t range, uint32_t colorBCG, uint32_t colorPRO, uint8_t tag);
void FT800_drawDial(int16_t x, int16_t y, uint16_t r, uint16_t options, uint16_t value, uint32_t colorMarker, uint32_t colorKnob, uint8_t tag);
void FT800_drawGauge(int16_t x, int16_t y, uint16_t r, uint16_t options, uint8_t major, uint8_t minor, uint16_t value, uint16_t range, uint32_t colorBCG, uint32_t colorNeedle, uint8_t tag);
//---------------------------------TAG------------------------------------------------------------- //OK
void FT800_track(int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t tag);
void FT800_tagMask(uint8_t mask);
uint8_t FT800_readTag(void);
uint16_t FT800_readValue(void);
//--------------------------------ANIM------------------------------------------------------------- //OK
void FT800_runTouchCalibration(void);
void FT800_drawAnimSpinner(int16_t x, int16_t y, uint8_t style, uint8_t scale);
void FT800_drawLogo(void);
void FT800_waitLogo(void);
void FT800_drawScreensaver(void);
void FT800_drawSketch(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t pointer, uint16_t format);
void FT800_stop(void);
void FT800_macro(uint8_t m);
//---------------------------------BMP------------------------------------------------------------- //OK
void FT800_bitmapBegin(void);
void FT800_bitmapHandle(uint8_t handle);
void FT800_bitmapLayout(uint8_t format, int16_t linestride, int16_t heigth);
void FT800_bitmapSize(uint8_t filter, uint8_t wrapx, uint8_t wrapy, int16_t width, int16_t heigth);
void FT800_bitmapSource(uint32_t add);
void FT800_bitmapTransform(uint32_t transform, int32_t value);
void FT800_loadIdentity(void);
void FT800_setMatrix(void);
void FT800_scale(int16_t sx,int16_t sy);
void FT800_translate(int16_t tx,int16_t ty);
void FT800_rotate(int16_t a);
void FT800_loadJpgCMD(uint32_t ptr, uint32_t opt);

#endif	/* FT800_GPARHICS_H */

