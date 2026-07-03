#pragma once

enum SoundName {
    _SN_LAYER_SWAP,
    _SN_LAYER_SWITCH,
    _SN_SAVED_EEPROM,
    _SN_CONFIG_ON,
    _SN_CONFIG_OFF
};

// API
void audio_playSound(enum SoundName sound);