#include "ff.h"
#include "FT800_Driver.h"
#include "FT800_Audio.h"
#include "FT800_Graphics.h"
#include "FT800_SD.h"

#define JFIF_SOI    0xFFD8
#define JFIF_APP0   0xFFE0
#define JIFF_SOS    0xFFDA
#define JIFF_EOI    0xFFD9

#define JPG_SOI 0
#define JPG_APP0 2
#define JPG_LEN 4
#define JPG_ID  6

#define RAM_G_SIZE (256<<10)
//--------------------------------------------------------------------------
//BMP header - BITMAPINFOHEADER 
//-------------------------------------------------------------------------- 

#define BMP_DIB     0x0E
#define BMP_WIDTH   0x12
#define BMP_HEIGHT  0x16
#define BMP_BPP     0x1C
#define BMP_COLORS  0x2E

//--------------------------------------------------------------------------
//WAV header  
//--------------------------------------------------------------------------  

#define WAV_FORMAT 20
#define WAV_CHANNELS 22
#define WAV_SAMPLE_RATE 24
#define WAV_BITS_PER_SAMPLE 34
#define WAV_SIZE    40
#define WAV_DATA    44

#define PCM_FRMT 1
#define ULAW_FRMT 7
#define ADPCM_FRMT 17
#define BUFF_SIZE 2048

uint8_t buff[BUFF_SIZE];

uint8_t FT800_loadWAVfromSD(uint32_t ram_offset, TCHAR *file_path, uint16_t *frmt, uint16_t *chn, uint32_t *sample, uint16_t *bpc, uint32_t *size)
{
    FIL myFile;
	unsigned int byteCount;   
    uint8_t  data[4];
    uint16_t wav_format=0, wav_channels=0, wav_bits_per_channel=0;
    uint32_t wav_sample_rate=0, bytes=0, offset=0,i,s;
    uint64_t wav_size=0;
   
    //open
    f_open(&myFile, file_path, FA_READ);
    //get format
    f_lseek(&myFile, WAV_FORMAT); 
    f_read(&myFile, &data, 2, &byteCount);
    wav_format=(data[1]<<8)|(data[0]);
    //get channels - mono, stereo
    f_lseek(&myFile, WAV_CHANNELS); 
    f_read(&myFile, &data, 2, &byteCount);
    wav_channels=(data[1]<<8)|(data[0]);
    //get sample sample rate
    f_lseek(&myFile, WAV_SAMPLE_RATE);
    f_read(&myFile, &data, 4, &byteCount);
    wav_sample_rate=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);
    //get bits per channel 
    f_lseek(&myFile, WAV_BITS_PER_SAMPLE);
    f_read(&myFile, &data, 4, &byteCount);
    wav_bits_per_channel=(data[1]<<8)|(data[0]);
    //get wav data size
    f_lseek(&myFile, WAV_SIZE);
    f_read(&myFile, &data, 4, &byteCount);
    wav_size=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);
    
    if(wav_format==PCM_FRMT)
    {
        if(wav_bits_per_channel==8)wav_format=PCM;
        else wav_format=UNDEFINED;
    }
    else if(wav_format==ULAW_FRMT)wav_format=ULAW;
    else if(wav_format==ADPCM_FRMT)wav_format=ADPCM;
    else wav_format=UNDEFINED;
    
    if(wav_format<=UNDEFINED)
    {
        if(wav_size>RAM_G_SIZE)wav_size=RAM_G_SIZE;
        s=wav_size;

        offset=ram_offset;
        f_lseek(&myFile, WAV_DATA);
        while(s)
        {
            if(s>BUFF_SIZE)bytes=BUFF_SIZE;
            else bytes=s;
            f_read(&myFile, &buff, bytes, &byteCount);

            FT800_CS_LO();                      // CS low 
            FT800_WriteAddress(RAM_G+offset,WRITE);// Send the address                                  
            for(i=0;i<bytes;i++)
            {
                if(wav_format==PCM)FT800_WriteSPI((int8_t)buff[i]-128);
                else FT800_WriteSPI(buff[i]);
            }
            FT800_CS_HI();    
            offset+=bytes;
            s=s-bytes;
        }
        *frmt=wav_format;
        *chn=wav_channels;
        *sample=wav_sample_rate;
        *bpc=wav_bits_per_channel;
        *size=wav_size;
    }
    else
    {
        *frmt=0;
        *chn=0;
        *sample=0;
        *bpc=0;
        *size=0;        
    }
    //close file
    f_close(&myFile);


    if(wav_format<=UNDEFINED) return 1; 
    else return 0;
}
uint8_t FT800_loadBMPfromSD(uint32_t ram_offset, TCHAR *file_path, uint16_t *width, uint16_t *height, uint8_t *bpc)
{
	FIL myFile;
    unsigned int byteCount;
    uint8_t  data[4];
    uint32_t y, x, bmp_offset=0, img_width, img_height, img_bpp, offset=0;
    uint8_t bytes;
    
    //open
    f_open(&myFile, file_path, FA_READ);
    //offset
    f_lseek(&myFile, BMP_DIB); 
    f_read(&myFile, &data, 4, &byteCount);
    bmp_offset=((data[3]<<24)|(data[2]<<16) |(data[1]<<8)|(data[0]))+BMP_DIB;
    //get image width
    f_lseek(&myFile, BMP_WIDTH);
    f_read(&myFile, &data, 4, &byteCount);
    img_width=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);
    //get image height
    f_lseek(&myFile, BMP_HEIGHT);
    f_read(&myFile, &data, 4, &byteCount);
    img_height=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);
    //get image Bits Per Pixel
    f_lseek(&myFile, BMP_BPP);
    f_read(&myFile, &data, 4, &byteCount);
    img_bpp=(data[1]<<8)|(data[0]);
    //go to image data
    f_lseek(&myFile, bmp_offset); 
    
    //get bytes per color
    bytes=img_bpp>>3;

    if(bytes==2) //only RGB565 is supported 2 bytes per pixel
    {
        offset=(img_width*bytes)*(img_height-1)+ram_offset;
        for(y=0;y<img_height;y++)
        {

            f_read(&myFile, &buff, img_width*bytes, &byteCount);

            FT800_CS_LO();                      // CS low 
            FT800_WriteAddress(RAM_G+offset,WRITE);// Send the address                                  
            for(x=0;x<(img_width*bytes);x++)FT800_WriteSPI(buff[x]);
            FT800_CS_HI();    
            offset-=((img_width)*bytes);
        }
        *width=img_width;
        *height=img_height;
        *bpc=bytes;
    }
    else
    {
        *width=0;
        *height=0;
        *bpc=0;        
    }
    //close
    f_close(&myFile);
    
    if(bytes==2)return 1;
    else return 0;
    
}


uint8_t FT800_loadJPGfromSD(uint32_t ram_offset, TCHAR *file_path, uint16_t *width, uint16_t *height)
{
	FIL myFile;
    unsigned int byteCount;
    uint8_t  data[8], read=1;
    uint32_t bytes, size=0;
    uint16_t len, marker=0, i;
    //uint16_t soi,app0,length;

    //open
    f_open(&myFile, file_path, FA_READ);
    //offset
    f_lseek(&myFile, JPG_SOI); 
    f_read(&myFile, &data, 2, &byteCount);
    //soi=(data[0]<<8)|(data[1]);
    //get image width
    f_lseek(&myFile, JPG_APP0);
    f_read(&myFile, &data, 2, &byteCount);
    //app0=(data[0]<<8)|(data[1]);
    //get image height
    f_lseek(&myFile, JPG_LEN);
    f_read(&myFile, &data, 2, &byteCount);
    len=(data[0]<<8)|(data[1]);


    //go to image data

      while(1) {
        if(marker == 0xFFC0) break;
        if(marker == 0xFF00) break;
        if (f_lseek(&myFile, len+2+size) != 0) break;
        f_read(&myFile, &data, 4, &byteCount);
        marker = data[0] << 8 | data[1];
       //length = data[2] << 8 | data[3];
        size+=4;
    }
    f_lseek(&myFile, len+2+size+1);
    f_read(&myFile, &data, 4, &byteCount);
    *height=(data[0]<< 8)|data[1];
    *width=(data[2]<< 8)|data[3];

   
    f_lseek(&myFile, 0); 
    FT800_finishList();

    FT800_loadJpgCMD(ram_offset,OPT_NODL);
    while(read)
    {
      f_read(&myFile, &buff, 2048, &byteCount);

      if(byteCount<2048)
      {
        bytes=byteCount;
        read=0;
      }
      else bytes=2048;
      while(FT800_getFreeSpace()<bytes)
      set_CMD_Offset(FT800_Read16(REG_CMD_WRITE));
      for(i=0;i<bytes;i++) FT800_Write8(RAM_CMD,buff[i]);    
      FT800_executeCommands();
   }
       
   FT800_align(bytes);
   FT800_endOfList(); 
       
   f_close(&myFile);
   
   return 1;
}
