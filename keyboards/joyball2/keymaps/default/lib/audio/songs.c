#include QMK_KEYBOARD_H
#include "songs.h"

/*
Resources:
https://docs.qmk.fm/features/audio
https://getreuer.info/posts/keyboards/qmk-song-player/song-syntax.html
https://getreuer.info/posts/keyboards/qmk-song-player/index.html
*/

//#define CK_SANTA QD_NOTE(_G5), ED_NOTE(_E5), ED_NOTE(_F5), QD_NOTE(_G5), H__NOTE(_G5),  ED_NOTE(_G5), ED_NOTE(_A5), ED_NOTE(_B5), QD_NOTE(_C6), H__NOTE(_C6), ED_NOTE(_C6), ED_NOTE(_E5), ED_NOTE(_F5), QD_NOTE(_G5), QD_NOTE(_G5), QD_NOTE(_G5), ED_NOTE(_A5), ED_NOTE(_G5), QD_NOTE(_F5), HD_NOTE(_F5), QD_NOTE(_E5), QD_NOTE(_G5), QD_NOTE(_C5), QD_NOTE(_E5),  QD_NOTE(_D5),  HD_NOTE(_F5), QD_NOTE(_B4), W__NOTE(_C5)

float layer_swap_sound[][2] = SONG(AG_SWAP_SOUND);
float layer_switch_sound[][2] = SONG(QWERTY_SOUND);
float saved_eeprom_sound[][2] = SONG(VIOLIN_SOUND);
float config_on_sound[][2] = SONG(AUDIO_ON_SOUND);
float config_off_sound[][2] = SONG(AUDIO_OFF_SOUND);

void audio_playSound(enum SoundName sound) {
  switch(sound){
    case _SN_LAYER_SWAP:
      PLAY_SONG(layer_swap_sound);
      break;
    case _SN_LAYER_SWITCH:
      PLAY_SONG(layer_switch_sound);
      break;
    case _SN_SAVED_EEPROM:
      PLAY_SONG(saved_eeprom_sound);
      break;
    case _SN_CONFIG_ON:
      PLAY_SONG(config_on_sound);
      break;
    case _SN_CONFIG_OFF:
      PLAY_SONG(config_off_sound);
      break;
  }
}