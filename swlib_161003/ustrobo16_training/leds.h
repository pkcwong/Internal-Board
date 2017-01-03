#ifndef __LEDS_H
#define __LEDS_H

#include "stm32f10x.h"

void led_init(void);
void led_blink(GPIO_TypeDef* PORT, u16 gpio_pin);
void led_off(GPIO_TypeDef* PORT, u16 gpio_pin);
void led_on(GPIO_TypeDef* PORT, u16 gpio_pin);

#endif
