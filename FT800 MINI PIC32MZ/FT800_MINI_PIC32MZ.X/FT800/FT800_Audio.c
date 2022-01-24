#include "FT800_Audio.h"


/* ************************************************************************************ */
// FT800 set volume for Sound Synthesizer 
/* ************************************************************************************ */

void FT800_setSoundVolume(uint8_t volume)
{
    FT800_Write8(REG_VOL_SOUND,volume);
}

/* ************************************************************************************ */
// FT800 set sound effect
// note: MIDI note (pitch control), effect: Sound effects pre-loaded in a ROM wave library
/* ************************************************************************************ */

void FT800_setSoundEffect(uint8_t note, uint8_t effect)
{
    FT800_Write16(REG_SOUND,((uint16_t)note<<8)|effect);
}

/* ************************************************************************************ */
// FT800 play sound
/* ************************************************************************************ */

void FT800_playSound(uint8_t play)
{
    FT800_Write8(REG_PLAY,play&0x01);
}

/* ************************************************************************************ */
// FT800 get sound playing status - 0=finished, 1=playing
/* ************************************************************************************ */

uint8_t FT800_isSoundPlaying(void)
{
    return FT800_Read8(REG_PLAY);
}

/* ************************************************************************************ */
// FT800 set volume for Audio Playback
/* ************************************************************************************ */

void FT800_setPlaybackVolume(uint8_t volume)
{
    FT800_Write8(REG_VOL_PB,volume);
}

/* ************************************************************************************ */
// FT800 configure Audio Playback - format: PCM, ULAW, ADPCM or UNDEFINDED
/* ************************************************************************************ */

void FT800_configurePlayback(uint32_t start_addr, uint32_t length, uint16_t freq, uint8_t format, uint8_t loop)
{
    FT800_Write32(REG_PLAYBACK_START,start_addr);
    FT800_Write32(REG_PLAYBACK_LENGTH,length);
    FT800_Write16(REG_PLAYBACK_FREQ,freq);
    FT800_Write8(REG_PLAYBACK_FORMAT,format&0x03);
    FT800_Write8(REG_PLAYBACK_LOOP,loop&0x01);
}

/* ************************************************************************************ */
// FT800 play audio playback
/* ************************************************************************************ */

void FT800_playPlayback(uint8_t play)
{
    FT800_Write8(REG_PLAYBACK_PLAY,play&0x01);
}

/* ************************************************************************************ */
// FT800 get playback playing status - 0=finished, 1=playing
/* ************************************************************************************ */

uint8_t FT800_isPlaybackPlaying(void)
{
    return FT800_Read8(REG_PLAYBACK_PLAY);
}

/* ************************************************************************************ */
// FT800 get playback location - 20-bit pointer of the current playback location
/* ************************************************************************************ */

uint32_t FT800_getPlaybackLocation(void)
{
    return (FT800_Read32(REG_PLAYBACK_READPTR)&0x000FFFFF);
}