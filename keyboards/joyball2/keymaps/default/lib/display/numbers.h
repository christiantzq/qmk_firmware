/*
These define a 2x1 matrix pointing to pre-determined memory
locations of the glcdfont.c to create the Big Numbers font in 
the oled display.
*/

static const char PROGMEM number_1_top[] = {
    0x01, 0x02, 0x00
};

static const char PROGMEM number_1_low[] = {
    0x21, 0x22, 0x00
};

static const char PROGMEM number_2_top[] = {
    0x03, 0x04, 0x00
};

static const char PROGMEM number_2_low[] = {
    0x23, 0x24, 0x00
};

static const char PROGMEM number_3_top[] = {
    0x05, 0x06, 0x00
};

static const char PROGMEM number_3_low[] = {
    0x25, 0x26, 0x00
};

static const char PROGMEM number_4_top[] = {
    0x07, 0x08, 0x00
};

static const char PROGMEM number_4_low[] = {
    0x27, 0x28, 0x00
};

static const char PROGMEM number_5_top[] = {
    //0x09, 0x0a, 0x00 // special char
    0x1b, 0x1c, 0x00
};

static const char PROGMEM number_5_low[] = {
    0x29, 0x2a, 0x00
};

static const char PROGMEM number_6_top[] = {
    0x0b, 0x0c, 0x00
};

static const char PROGMEM number_6_low[] = {
    0x2b, 0x2c, 0x00
};

static const char PROGMEM number_7_top[] = {
    //0x0d, 0x0e, 0x00 // special char
    0x1d, 0x1e, 0x00
};

static const char PROGMEM number_7_low[] = {
    0x1f, 0x2e, 0x00
};

static const char PROGMEM number_8_top[] = {
    0x0f, 0x10, 0x00
};

static const char PROGMEM number_8_low[] = {
    0x11, 0x12, 0x00
};

static const char PROGMEM number_9_top[] = {
    0x13, 0x14, 0x00
};

static const char PROGMEM number_9_low[] = {
    0x15, 0x16, 0x00
};

static const char PROGMEM number_0_top[] = {
    0x17, 0x18, 0x00
};

static const char PROGMEM number_0_low[] = {
    0x19, 0x1a, 0x00
};

static const char PROGMEM *topNum[] = {
    number_0_top, number_1_top, number_2_top, number_3_top, 
    number_4_top, number_5_top, number_6_top, number_7_top, 
    number_8_top, number_9_top
};

static const char PROGMEM *lowNum[] = {
    number_0_low, number_1_low, number_2_low, number_3_low, 
    number_4_low, number_5_low, number_6_low, number_7_low, 
    number_8_low, number_9_low
};