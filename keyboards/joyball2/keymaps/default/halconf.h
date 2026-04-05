#pragma once

#include_next <halconf.h>

// Audio PWM Setup in GPIO 10
#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE