/*
 * FT800_SD.h
 *
 *  Created on: May 3, 2020
 *      Author: predr
 */

#ifndef FT800_SD_H_
#define FT800_SD_H_

#include "ff.h"

uint8_t FT800_loadWAVfromSD(uint32_t ram_offset, TCHAR *file_path, uint16_t *frmt, uint16_t *chn, uint32_t *sample, uint16_t *bpc, uint32_t *size);
uint8_t FT800_loadBMPfromSD(uint32_t ram_offset, TCHAR *file_path, uint16_t *width, uint16_t *height, uint8_t *bpc);
uint8_t FT800_loadJPGfromSD(uint32_t ram_offset, TCHAR *file_path, uint16_t *width, uint16_t *height);


#endif /* FT800_SD_H_ */
