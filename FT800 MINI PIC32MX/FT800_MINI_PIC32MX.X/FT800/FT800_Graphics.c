#include "FT800_Graphics.h"
#include <string.h>


/* ************************************************************************************ */
// FT800 Start new display list
/* ************************************************************************************ */

void FT800_startNewList(void)
{          
    FT800_Write32(RAM_CMD, CMD_DLSTART);
}

/* ************************************************************************************ */
// FT800 End of display list
/* ************************************************************************************ */

void FT800_endOfList(void)
{    
    FT800_Write32(RAM_CMD, 0x00000000);    
    FT800_Write32(RAM_CMD, CMD_SWAP);  
    FT800_Write16(REG_CMD_WRITE,get_CMD_Offset());  
}

/* ************************************************************************************ */
// FT800 Finish display list
/* ************************************************************************************ */

void FT800_finishList(void)
{
    uint32_t cmdBufferWr, cmdBufferRd;
    do
    {
        cmdBufferWr = FT800_Read16(REG_CMD_WRITE);          // Read the vaulue of the REG_CMD_WRITE register
        cmdBufferRd = FT800_Read16(REG_CMD_READ);           // Read the vaulue of the REG_CMD_READ register
    } while(cmdBufferWr != cmdBufferRd);
    set_CMD_Offset(FT800_Read16(REG_CMD_WRITE)); 
}

/* ************************************************************************************ */
// FT800 Execute all the commands written in RAM_CMD
/* ************************************************************************************ */

void FT800_executeCommands(void)
{
    FT800_Write16(REG_CMD_WRITE, get_CMD_Offset());
}

/* ************************************************************************************ */
// FT800 get free space in command buffer
/* ************************************************************************************ */

uint16_t FT800_getFreeSpace(void)
{
    uint32_t fullness;
    uint16_t freespace;

    fullness = (FT800_Read16(REG_CMD_WRITE) - FT800_Read16(REG_CMD_READ)) & 0xFFF;
    freespace = (4096 - 4) - fullness;
    
    return freespace;
}

/* ************************************************************************************ */
// FT800 Set Background color - 0x02BBGGRR, color=BBGGRRAA
/* ************************************************************************************ */

void FT800_setBackgroundColor(uint32_t color)
{         
    FT800_Write32(RAM_CMD, 0x02000000|(color&0x00FFFFFF));
}

/* ************************************************************************************ */
// FT800 Clear display - 0x2600000X  
//clr=X, X=1 clear tag, X=2 clear stencil, X=4 clear color, X=7 clear all
/* ************************************************************************************ */

void FT800_clear(uint8_t clr)
{       
    FT800_Write32(RAM_CMD, 0x26000000|(clr&0x07));  
}

/* ************************************************************************************ */
// FT800 color transparency alpha=[0-255]
/* ************************************************************************************ */

void FT800_setColorA(uint8_t alpha)
{
    FT800_Write32(RAM_CMD, 0x10000000|alpha);
}

/* ************************************************************************************ */
// FT800 Object color (BGR)
/* ************************************************************************************ */

void FT800_setColorRGB(uint32_t color)
{
    FT800_Write32(RAM_CMD, 0x04000000|(color&0x00FFFFFF));
}

/* ************************************************************************************ */
// FT800 Object background color
/* ************************************************************************************ */

void FT800_setBgColor(uint32_t color)
{
    FT800_Write32(RAM_CMD, CMD_BGCOLOR);
    FT800_Write32(RAM_CMD, (color&0x00FFFFFF));
}

/* ************************************************************************************ */
// FT800 Object foreground color
/* ************************************************************************************ */

void FT800_setFgColor(uint32_t color)
{
    FT800_Write32(RAM_CMD, CMD_FGCOLOR);   
    FT800_Write32(RAM_CMD, (color&0x00FFFFFF));
}

/* ************************************************************************************ */
// FT800 set the 3D button highlight color
/* ************************************************************************************ */

void FT800_setGradColor(uint32_t color)
{
    FT800_Write32(RAM_CMD, CMD_GRADCOLOR);   
    FT800_Write32(RAM_CMD, (color&0x00FFFFFF));
}
/* ************************************************************************************ */
// FT800 blend function - specifies how the source blending factor is computed.
/* ************************************************************************************ */

void FT800_setBlendFunc(uint8_t src, uint8_t dst)
{
    uint32_t blend=0x0B000000;
    
    blend|=((src&0x07)<<3);
    blend|=(dst&0x07);
    
    FT800_Write32(RAM_CMD, blend);  
}

/* ************************************************************************************ */
// FT800 Vertex2II  - x[-16384,16383], y[-16384,16383], in 1/16 of the pixel 
/* ************************************************************************************ */

void FT800_Vertex2F(int16_t x, int16_t y)
{
    uint32_t xy=0x40000000;
    
    xy|=((x&0x7FFF)<<15); //11 bits for +-x coordinate and 4 bits for x fraction (1/16 of pixel)
    xy|=(y&0x7FFF);       //11 bits for +-y coordinate and 4 bits for y fraction (1/16 of pixel)
   
    FT800_Write32(RAM_CMD, xy); 
}

/* ************************************************************************************ */
// FT800 Vertex2II  - x[0,511], y[0,511], handle [0-31], cell [0-127]  
/* ************************************************************************************ */

void FT800_Vertex2II(uint16_t x, uint16_t y, uint8_t handle, uint8_t cell)
{
    uint32_t xyhc=0x80000000;
    xyhc|=((x&0x01FF)<<21);
    xyhc|=((y&0x01FF)<<12);
    xyhc|=((handle&0x1F)<<7);
    xyhc|=(cell&0x7F);

    FT800_Write32(RAM_CMD, xyhc); 
} 

/* ************************************************************************************ */
// FT800 align - used filling up to 32 bit (4 bytes)
/* ************************************************************************************ */

void FT800_align(uint8_t n)
{
    while((n++) & 3)
    FT800_Write8(RAM_CMD, 0);
}
/* ************************************************************************************ */
// FT800 write string - used text draw and object naming
/* ************************************************************************************ */

void FT800_WriteString(const char*s)
{
    uint16_t string_length = 0;
    string_length = strlen(s)+1;
    while(*s)
    {
        char c=*s++;
        FT800_Write8(RAM_CMD, c);
    }
    FT800_Write8(RAM_CMD, 0);
    FT800_align(string_length);  
}

/************************************************************************************* */
// FT800 write zero to a block of memory
/* ************************************************************************************ */
 
void FT800_writeMemZero(uint32_t pointer, uint32_t number)
{
    FT800_Write32(RAM_CMD, CMD_MEMZERO); 
    FT800_Write32(RAM_CMD, pointer);   
    FT800_Write32(RAM_CMD, number); 
}

/************************************************************************************* */
// FT800 write value to a block of memory
/* ************************************************************************************ */

void FT800_writeMemSet(uint32_t pointer, uint32_t value, uint32_t number)
{
    FT800_Write32(RAM_CMD, CMD_MEMSET); 
    FT800_Write32(RAM_CMD, pointer); 
    FT800_Write32(RAM_CMD, value);  
    FT800_Write32(RAM_CMD, number); 
}

/************************************************************************************* */
// FT800 copy block of memory
/* ************************************************************************************ */

void FT800_writeMemCPy(uint32_t source, uint32_t destination)
{
    FT800_Write32(RAM_CMD, CMD_MEMCPY); 
    FT800_Write32(RAM_CMD, source); 
    FT800_Write32(RAM_CMD, destination);  
}

/* ************************************************************************************ */
// FT800 draw point  - x[-1024,1023], y[-1024,1023], color, size (in 1/16 of pixel) 
/* ************************************************************************************ */

void FT800_drawPoint(int16_t x, int16_t y, uint32_t color, uint16_t size)
{
    FT800_setColorRGB(color);              //point color
    FT800_Write32(RAM_CMD, 0x0D000000|size); //point size                
    FT800_Write32(RAM_CMD, BEGIN|POINT);   //begin drawing point
    FT800_Vertex2F(x<<4,y<<4);             //set coordinates    
    FT800_Write32(RAM_CMD, END);           //end of drawing
}

/* ************************************************************************************ */
// FT800 draw line from (x1,y1) to (x2,y2) of color color and linewidth width
/* ************************************************************************************ */

void FT800_drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color, uint16_t width)
{  
    
    FT800_setColorRGB(color);
    FT800_Write32(RAM_CMD, 0x0E000000|(width&0x0FFF));         
    FT800_Write32(RAM_CMD, BEGIN|LINE);
    FT800_Vertex2F(x1<<4,y1<<4);
    FT800_Vertex2F(x2<<4,y2<<4);
    FT800_Write32(RAM_CMD, END); 
}
/* ************************************************************************************ */
// FT800 draw rectangle starting from (x1,y1) and ending at (x2,y2) of color color and linewidth width
/* ************************************************************************************ */

void FT800_drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color, uint16_t width)
{  
    FT800_setColorRGB(color);
    FT800_Write32(RAM_CMD, 0x0E000000|(width&0x0FFF));  
    FT800_Write32(RAM_CMD, BEGIN|RECT);
    FT800_Vertex2F(x1<<4,y1<<4);
    FT800_Vertex2F(x2<<4,y2<<4);
    FT800_Write32(RAM_CMD, END); 
}  

/* ************************************************************************************ */
// FT800 draw line strip in number of points num_of_points
/* ************************************************************************************ */

void FT800_drawLineStrip(int16_t x[], int16_t y[],uint16_t num_of_points, uint32_t color, uint16_t width)
{
    uint16_t i;
    FT800_setColorRGB(color);
    FT800_Write32(RAM_CMD, 0x0E000000|(width&0x0FFF));  
    FT800_Write32(RAM_CMD, BEGIN|LINE_STRIP);
    for(i=0;i<num_of_points;i++) FT800_Vertex2F(x[i]<<4,y[i]<<4);
    FT800_Write32(RAM_CMD, END);
} 

/* ************************************************************************************ */
// FT800 draw edge line strip (color filling) in number of points num_of_points
/* ************************************************************************************ */

void FT800_drawEdgeLineStrip(int16_t x[], int16_t y[], uint16_t num_of_points, uint8_t choice, uint32_t color)
{
    uint32_t c=0; uint16_t i;
    
       
    switch(choice) //choose edge side 
    {
        case'R': c = EDGE_STRIP_R; //right
                    break;
        case'L': c = EDGE_STRIP_L; //left
                    break;
        case'A': c = EDGE_STRIP_A; //above
                    break;
        case'B': c = EDGE_STRIP_B; //below
                    break;
    }
    FT800_setColorRGB(color);
    FT800_Write32(RAM_CMD, BEGIN|c);
    for(i=0;i<num_of_points;i++) FT800_Vertex2F(x[i]<<4,y[i]<<4);
    FT800_Write32(RAM_CMD, END);
}   

/* ************************************************************************************ */
// FT800 draw char at position (x,y), font [16-31], color, char
/* ************************************************************************************ */

void FT800_drawChar(uint16_t x, uint16_t y, uint8_t font, uint32_t color, char c)
{
    FT800_setColorRGB(color);
    FT800_Write32(RAM_CMD, BEGIN|BITMAP); 
    if(font>31)font=31;
    if(font<16)font=16;
    FT800_Vertex2II(x, y, font, c);
    FT800_Write32(RAM_CMD, END);
}

/* ************************************************************************************ */
// FT800 draw text at position (x,y), font [16-31], color, options [ie. OPT_RIGHTX], text s
/* ************************************************************************************ */

void FT800_drawText(int16_t x, int16_t y, uint8_t font, uint32_t color, uint16_t options, const char *s)   
{ 
    FT800_setColorRGB(color);
    FT800_Write32(RAM_CMD, CMD_TEXT);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    if(font>31)font=31;
    if(font<16)font=16;
    FT800_Write16(RAM_CMD, font);
    FT800_Write16(RAM_CMD, options);
    FT800_WriteString(s);
}
/************************************************************************************* */
// FT800 decimal number
/* ************************************************************************************ */

void FT800_drawDecimalNumb(int16_t x, int16_t y, uint8_t font, uint16_t options, uint32_t n, uint32_t color)
{
    FT800_setColorRGB(color);
    FT800_Write32(RAM_CMD, CMD_NUMBER);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    if(font>31)font=31;
    if(font<16)font=16;
    FT800_Write16(RAM_CMD, font);
    FT800_Write16(RAM_CMD, options);
    FT800_Write32(RAM_CMD, n);
}

/* ************************************************************************************ */
// FT800 draw button
/* ************************************************************************************ */

void FT800_drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t colorBG, uint8_t font, uint16_t options, const char*s, uint32_t colorTXT, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,w,h,tag);
    }
    FT800_setFgColor(colorBG); //button color
    FT800_setColorRGB(colorTXT); //text color
    FT800_Write32(RAM_CMD, CMD_BUTTON);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, w);
    FT800_Write16(RAM_CMD, h);
    if(font>31)font=31;
    if(font<16)font=16;
    FT800_Write16(RAM_CMD, font);
    FT800_Write16(RAM_CMD, options);
    FT800_WriteString(s);
    FT800_tagMask(0);
}

/* ************************************************************************************ */
// FT800 draw analog clock
/* ************************************************************************************ */

void FT800_drawClock(int16_t x, int16_t y, uint16_t r, uint32_t colorBG, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms, uint32_t colorNeedle, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,1,1,tag);
    }
    FT800_setBgColor(colorBG);
    FT800_setColorRGB(colorNeedle);
    FT800_Write32(RAM_CMD, CMD_CLOCK);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, r);
    FT800_Write16(RAM_CMD, options);
    FT800_Write16(RAM_CMD, h);
    FT800_Write16(RAM_CMD, m);
    FT800_Write16(RAM_CMD, s);
    FT800_Write16(RAM_CMD, ms);
    FT800_tagMask(0);
}

/* ************************************************************************************ */
// FT800 draw gradient from color0 to color1 (use in combination with scissors)
/* ************************************************************************************ */

void FT800_drawGradient(int16_t x0, int16_t y0, uint32_t color0, int16_t x1, int16_t y1, uint32_t color1)
{
    FT800_Write32(RAM_CMD, CMD_GRADIENT);
    FT800_Write16(RAM_CMD, x0);
    FT800_Write16(RAM_CMD, y0);
    FT800_setColorRGB(color0);
    FT800_Write16(RAM_CMD, x1);
    FT800_Write16(RAM_CMD, y1);
    FT800_setColorRGB(color1);
}

/* ************************************************************************************ */
// FT800 scissor start point
/* ************************************************************************************ */

void FT800_drawScissorXY(int16_t x, int16_t y)
{
    uint32_t scissorXY = 0x1B000000;
    
    scissorXY |= (x&0x01FF)<<9;
    scissorXY |= (y&0x01FF); 

    FT800_Write32(RAM_CMD, scissorXY);
}

/************************************************************************************* */
// FT800 scissor width and height
/* ************************************************************************************ */

void FT800_drawScissorSize(uint16_t w, uint16_t h)
{
    uint32_t scissorSize = 0x1C000000;
    
    scissorSize |= (w&0x03FF)<<10;
    scissorSize |= (h&0x03FF); 

    FT800_Write32(RAM_CMD, scissorSize);
}

/************************************************************************************* */
// FT800 keys - number of keys=number of letters in string s
/* ************************************************************************************ */

void FT800_drawKeys(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t colorBG, uint8_t font, uint16_t options, const char*s, uint32_t colorTXT, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,w,h,tag);
    }
    FT800_setFgColor(colorBG);
    FT800_setColorRGB(colorTXT);
    FT800_Write32(RAM_CMD, CMD_KEYS);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, w);
    FT800_Write16(RAM_CMD, h);
    if(font>31)font=31;
    if(font<16)font=16;
    FT800_Write16(RAM_CMD, font);
    FT800_Write16(RAM_CMD, options);
    FT800_WriteString(s);
    FT800_tagMask(0);
}

/************************************************************************************* */
// FT800 scroll bar - if w>h: horizontal else: vertical 
/* ************************************************************************************ */

void FT800_drawScrollBar(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t colorBG, uint32_t colorSCR, uint16_t options, uint16_t value, uint16_t size, uint16_t range, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,w,h,tag);
    }
    FT800_setFgColor(colorBG);
    FT800_setBgColor(colorSCR);
    FT800_Write32(RAM_CMD, CMD_SCROLLBAR);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, w);
    FT800_Write16(RAM_CMD, h);
    FT800_Write16(RAM_CMD, options);
    FT800_Write16(RAM_CMD, value);
    FT800_Write16(RAM_CMD, size);
    FT800_Write16(RAM_CMD, range);
    FT800_tagMask(0);
}

/************************************************************************************* */
// FT800 toggle button
/* ************************************************************************************ */

void FT800_drawToggle(int16_t x, int16_t y, uint16_t w, uint8_t font, uint16_t options, uint16_t state, const char *s, uint32_t colorKnob, uint32_t colorBCG, uint32_t colorTXT, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,w,font,tag);
    }    
    FT800_setFgColor(colorKnob);
    FT800_setBgColor(colorBCG);
    FT800_setColorRGB(colorTXT);
    FT800_Write32(RAM_CMD, CMD_TOGGLE);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, w);
    if(font>31)font=31;
    if(font<16)font=16;
    FT800_Write16(RAM_CMD, font);
    FT800_Write16(RAM_CMD, options);
    FT800_Write16(RAM_CMD, state);
    FT800_WriteString(s);
    FT800_tagMask(0);
}

/************************************************************************************* */
// FT800 slider - if w>h: horizontal else: vertical 
/* ************************************************************************************ */

void FT800_drawSlider(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t value, uint16_t range, uint32_t colorR, uint32_t colorKnob, uint32_t colorL, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,w,h,tag);
    }
    FT800_setFgColor(colorKnob);
    FT800_setColorRGB(colorR);
    FT800_setBgColor(colorL);
    FT800_Write32(RAM_CMD, CMD_SLIDER);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, w);
    FT800_Write16(RAM_CMD, h);
    FT800_Write16(RAM_CMD, options);
    FT800_Write16(RAM_CMD, value);
    FT800_Write16(RAM_CMD, range);
    FT800_Write16(RAM_CMD, 0);
    FT800_tagMask(0);
}

/************************************************************************************* */
// FT800 progress bar - if w>h: horizontal else: vertical 
/* ************************************************************************************ */

void FT800_drawProgressBar(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t value, uint16_t range, uint32_t colorBCG, uint32_t colorPRO, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,w,h,tag);
    }
    FT800_setColorRGB(colorBCG);
    FT800_setBgColor(colorPRO);
    FT800_Write32(RAM_CMD, CMD_PROGRESS);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, w);
    FT800_Write16(RAM_CMD, h);
    FT800_Write16(RAM_CMD, options);
    FT800_Write16(RAM_CMD, value);
    FT800_Write16(RAM_CMD, range);
    FT800_Write16(RAM_CMD, 0); // align to 32
    FT800_tagMask(0);
}

/************************************************************************************* */
// FT800 draw dial potentiometer
/* ************************************************************************************ */

void FT800_drawDial(int16_t x, int16_t y, uint16_t r, uint16_t options, uint16_t value, uint32_t colorMarker, uint32_t colorKnob, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,1,1,tag);//rotary tracker
    }
    FT800_setColorRGB(colorKnob);
    FT800_setFgColor(colorMarker);
    FT800_Write32(RAM_CMD, CMD_DIAL);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, r);
    FT800_Write16(RAM_CMD, options);    
    FT800_Write16(RAM_CMD, value);
    FT800_Write16(RAM_CMD, 0); // align to 32
    FT800_tagMask(0);
}

/************************************************************************************* */
// FT800 draw gauge indicator
/* ************************************************************************************ */

void FT800_drawGauge(int16_t x, int16_t y, uint16_t r, uint16_t options, uint8_t major, uint8_t minor, uint16_t value, uint16_t range, uint32_t colorBCG, uint32_t colorNeedle, uint8_t tag)
{
    if(tag)
    {
        FT800_tagMask(1);
        FT800_track(x,y,1,1,tag);
    }
    FT800_setColorRGB(colorNeedle);
    FT800_setBgColor(colorBCG);
    FT800_Write32(RAM_CMD, CMD_GAUGE);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, r);
    FT800_Write16(RAM_CMD, options);
    FT800_Write16(RAM_CMD, major);
    FT800_Write16(RAM_CMD, minor);
    FT800_Write16(RAM_CMD, value);
    FT800_Write16(RAM_CMD, range);
    FT800_tagMask(0);
}

/************************************************************************************* */
// FT800 assign tag and track given area for touch 
// all object in the given area will have the same tag - to prevent use tag mask
/* ************************************************************************************ */

void FT800_track(int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t tag)
{
    FT800_Write32(RAM_CMD, CMD_TRACK);
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    FT800_Write16(RAM_CMD, w);
    FT800_Write16(RAM_CMD, h);
    FT800_Write32(RAM_CMD, tag);
    FT800_Write32(RAM_CMD,0x03000000|(tag&0xFF)); 
}

/************************************************************************************* */
// FT800 tag mask - disable(0) or enable(1) object tag
/* ************************************************************************************ */

void FT800_tagMask(uint8_t mask)
{
    FT800_Write32(RAM_CMD,0x14000000|(mask&0x01));
}

/************************************************************************************* */
// FT800 read tag value
/* ************************************************************************************ */

uint8_t FT800_readTag(void)
{
    uint32_t tag;

    tag=FT800_Read32(REG_TRACKER)&0x000000FF;
    
    return (uint8_t)tag;
}

/************************************************************************************* */
// FT800 read value tagged object
/* ************************************************************************************ */

uint16_t FT800_readValue(void)
{
    uint32_t value;

    value = FT800_Read32(REG_TRACKER)&(0xFFFF0000);

    return (uint16_t)(value>>16);
}

/************************************************************************************* */
// FT800 run touch screen animation
/* ************************************************************************************ */

void FT800_runTouchCalibration(void)
{
    FT800_Write32(RAM_CMD, CMD_CALIBRATE);
}

/************************************************************************************* */
// FT800 animated spinner
/* ************************************************************************************ */

void FT800_drawAnimSpinner(int16_t x, int16_t y, uint8_t style, uint8_t scale)
{
    FT800_Write32(RAM_CMD, CMD_SPINNER);      
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);
    if(style>3) style=0;
    FT800_Write16(RAM_CMD, style);    
    FT800_Write16(RAM_CMD, scale);
}

/************************************************************************************* */
// FT800 draw FTDI animated logo
/* ************************************************************************************ */

void FT800_drawLogo(void)
{
    FT800_Write32(RAM_CMD, CMD_LOGO);
}

/* ************************************************************************************ */
// FT800 wait Logo to finish 
/* ************************************************************************************ */

void FT800_waitLogo(void)
{
    FT800_executeCommands();
    DELAY(1);
    while((FT800_Read16(REG_CMD_WRITE) != 0));
    DELAY(1); 
    FT800_finishList();
}

/************************************************************************************* */
// FT800 screensaver command
/* ************************************************************************************ */

void FT800_drawScreensaver(void)
{
   FT800_Write32(RAM_CMD, CMD_SCREENSAVER); 
}

/************************************************************************************* */
// FT800 draw sketch
/* ************************************************************************************ */

void FT800_drawSketch(int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t pointer, uint16_t format)
{
    FT800_Write32(RAM_CMD, CMD_SKETCH); 
    FT800_Write16(RAM_CMD, x);
    FT800_Write16(RAM_CMD, y);    
    FT800_Write16(RAM_CMD, w);
    FT800_Write16(RAM_CMD, h);
    FT800_Write32(RAM_CMD, pointer); 
    FT800_Write16(RAM_CMD, format); 
    FT800_Write16(RAM_CMD, 0x0000);  //align      
}

/************************************************************************************* */
// FT800 stop spinner, screensaver or sketch
/* ************************************************************************************ */

void FT800_stop(void)
{
    FT800_Write32(RAM_CMD, CMD_STOP);      
}

/************************************************************************************* */
// FT800 macro
/* ************************************************************************************ */

void FT800_macro(uint8_t m)
{
    uint32_t macro = 0x25000000;

    macro |= (m&0x01);
    FT800_Write32(RAM_CMD, macro); 
}

/************************************************************************************* */
// FT800 bitmap begin
/* ************************************************************************************ */

void FT800_bitmapBegin(void)
{ 
    FT800_Write32(RAM_CMD, BEGIN|BITMAP);
}

/************************************************************************************* */
// FT800 bitmap handle
/* ************************************************************************************ */

void FT800_bitmapHandle(uint8_t handle)
{
    FT800_Write32(RAM_CMD, 0x05000000|(handle&0x1F));
}

/************************************************************************************* */
// FT800 bitmap layout
/* ************************************************************************************ */

void FT800_bitmapLayout(uint8_t format, int16_t linestride, int16_t heigth)
{
    uint32_t bitmap_layout=0x07000000;
   
    if(format>11) format = 11; //The valid range is from  0 to 11
    bitmap_layout |= (uint32_t)(format&0x1F)<<19;
    bitmap_layout |= (uint32_t)(linestride&0x03FF)<<9;
    bitmap_layout |= (heigth&0x01FF);  
    
    FT800_Write32(RAM_CMD, bitmap_layout);
}

/************************************************************************************* */
// FT800 bitmap size
/* ************************************************************************************ */

void FT800_bitmapSize(uint8_t filter, uint8_t wrapx, uint8_t wrapy, int16_t width, int16_t heigth)
{
    uint32_t bitmap_size=0x08000000;
    
    bitmap_size |= (uint32_t)(filter&0x01)<<20;
    bitmap_size |= (uint32_t)(wrapx&0x01)<<19;
    bitmap_size |= (uint32_t)(wrapy&0x01)<<18;
    bitmap_size |= (uint32_t)(width&0x01FF)<<9;
    bitmap_size |= (uint32_t)(heigth&0x01FF);
    
    FT800_Write32(RAM_CMD, bitmap_size);
}

/************************************************************************************* */
// FT800 bitmap source
/* ************************************************************************************ */

void FT800_bitmapSource(uint32_t add)
{  
    FT800_Write32(RAM_CMD, 0x01000000|(add&0x000FFFFF));
}

/************************************************************************************* */
// FT800 bitmapTransform - scaling, rotation and translation
// value=[BMP_TRAMSFORM_A-BMP_TRANSFORM_F]
// x1=x*A+y*B+C y1=x*D+y*E+F
/* ************************************************************************************ */

void FT800_bitmapTransform(uint32_t transform, int32_t value)
{ 
    FT800_Write32(RAM_CMD, transform|(value&0x00FFFFFF)); 
}

/************************************************************************************* */
// FT800 load matrix
/* ************************************************************************************ */

void FT800_loadIdentity(void)
{
    FT800_Write32(RAM_CMD, CMD_LOADIDENTITY);
}

/************************************************************************************* */
// FT800 set matrix
/* ************************************************************************************ */

void FT800_setMatrix(void)
{
    FT800_Write32(RAM_CMD, CMD_SETMATRIX);
}

/************************************************************************************* */
// FT800 scale command
/* ************************************************************************************ */

void FT800_scale(int16_t sx,int16_t sy)
{
    FT800_Write32(RAM_CMD, CMD_SCALE);
    FT800_Write32(RAM_CMD, (int32_t)sx<<16);
    FT800_Write32(RAM_CMD, (int32_t)sy<<16);    
}

/************************************************************************************* */
// FT800 translate command
/* ************************************************************************************ */

void FT800_translate(int16_t tx,int16_t ty)
{
    FT800_Write32(RAM_CMD, CMD_TRANSLATE);
    FT800_Write32(RAM_CMD, (int32_t)tx<<16);
    FT800_Write32(RAM_CMD, (int32_t)ty<<16);    
}

/************************************************************************************* */
// FT800 rotate command
/* ************************************************************************************ */

void FT800_rotate(int16_t a)
{
    FT800_Write32(RAM_CMD, CMD_ROTATE);
    FT800_Write32(RAM_CMD, ((int32_t)a<<16)/360);   
}

/************************************************************************************* */
// FT800 load jpg command
/* ************************************************************************************ */

void FT800_loadJpgCMD(uint32_t ptr, uint32_t opt)
{
    FT800_Write32(RAM_CMD, CMD_LOADIMAGE);
    FT800_Write32(RAM_CMD, ptr);
    FT800_Write32(RAM_CMD, opt);
}


