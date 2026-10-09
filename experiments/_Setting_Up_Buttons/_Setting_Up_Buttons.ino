#include "driver/i2s_std.h"
#include "driver/gpio.h"

#define PTT_BTN 36

void pinMode_setup() {
    pinMode(PTT_BTN, INPUT) // Arduino IDE method to configure the GPIO 36, as an Input pin. Not using INPUT_PULLUP since we have an ext. Pull up Res.
}

