#include QMK_KEYBOARD_H
#include "songs.h"

// https://docs.qmk.fm/features/audio
// https://getreuer.info/posts/keyboards/qmk-song-player/song-syntax.html


//#define CK_SANTA QD_NOTE(_G5), ED_NOTE(_E5), ED_NOTE(_F5), QD_NOTE(_G5), H__NOTE(_G5),  ED_NOTE(_G5), ED_NOTE(_A5), ED_NOTE(_B5), QD_NOTE(_C6), H__NOTE(_C6), ED_NOTE(_C6), ED_NOTE(_E5), ED_NOTE(_F5), QD_NOTE(_G5), QD_NOTE(_G5), QD_NOTE(_G5), ED_NOTE(_A5), ED_NOTE(_G5), QD_NOTE(_F5), HD_NOTE(_F5), QD_NOTE(_E5), QD_NOTE(_G5), QD_NOTE(_C5), QD_NOTE(_E5),  QD_NOTE(_D5),  HD_NOTE(_F5), QD_NOTE(_B4), W__NOTE(_C5)
#define CK_ZELDA_CHEST QD_NOTE(_A4), QD_NOTE(_AS4), QD_NOTE(_B4), B__NOTE(_C5)
#define CK_ZELDA_SECRET Q__NOTE(_G5), Q__NOTE(_FS5), Q__NOTE(_DS5), Q__NOTE(_A4), Q__NOTE(_GS4), Q__NOTE(_E5), Q__NOTE(_GS5), QD_NOTE(_C6)

float zelda_chest_song[][2] = SONG(CK_ZELDA_CHEST);
float zelda_secret_song[][2] = SONG(CK_ZELDA_SECRET);
float caps_on_song[][2] = SONG(CAPS_LOCK_ON_SOUND );


void audio_playZeldaChest(void) {
  PLAY_SONG(zelda_chest_song);
}

void audio_playZeldaSecret(void) {
  PLAY_SONG(zelda_secret_song);
}

void audio_playCapsOn(void) {
  PLAY_SONG(caps_on_song);
}