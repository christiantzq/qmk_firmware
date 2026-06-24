#pragma once

enum SoundName {
    //_SN_ZELDA_CHEST,
    //_SN_ZELDA_SECRET,
    //_SN_CAPS_ON,
    _SN_LAYER_SWAP,
    _SN_LAYER_SWITCH,
    _SN_SAVED_EEPROM,
    _SN_CONFIG_ON,
    _SN_CONFIG_OFF
};

// API
void audio_playSound(enum SoundName sound);