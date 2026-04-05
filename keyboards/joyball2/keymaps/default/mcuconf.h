#pragma once

#include_next <mcuconf.h>

// Serial Peripheral Interface (Trackball)
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE

// Audio PWM Setup in GPIO 10
// https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#page=14
#undef RP_PWM_USE_PWM5
#define RP_PWM_USE_PWM5 TRUE