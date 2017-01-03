#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "stm32f10x.h"
#include "ticks.h"
#include "buzzer.h"
#include "buzzer_song.h"
#include "adc.h"
#include "leds.h"
#include "gpio.h"
#include "button.h"
#include "uart.h"

#include "servo.h"
#include "motor.h"
#include "tft_display.h"
#include "pneumatic.h"
#include "linear_ccd.h"

int main(void);

#endif
