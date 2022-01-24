/* 
 * File:   FT800_Audio.h
 * Author: Jovan
 *
 * Created on August 4, 2019, 10:04 AM
 */

#ifndef FT800_AUDIO_H
#define	FT800_AUDIO_H

#include "FT800_Driver.h"

#define PCM         0     
#define ULAW        1
#define ADPCM       2
#define UNDEFINED   3


//--------------------SOUNDSYNTHESIZER------------------------------
void FT800_setSoundVolume(uint8_t volume);
void FT800_setSoundEffect(uint8_t note, uint8_t effect);
void FT800_playSound(uint8_t play);
uint8_t FT800_isSoundPlaying(void);
//--------------------AUDIO PLAYBACK--------------------------------
void FT800_setPlaybackVolume(uint8_t volume);
void FT800_configurePlayback(uint32_t start_addr, uint32_t length, uint16_t freq, uint8_t format, uint8_t loop);
void FT800_playPlayback(uint8_t play);
uint8_t FT800_isPlaybackPlaying(void);
uint32_t FT800_getPlaybackLocation(void);

#endif	/* FT800_AUDIO_H */

