#ifndef __BUTTON_H
#define __BUTTON_H

#include "stm32f10x_gpio.h"

#define BUTTON1 GPIO_Pin_13
#define BUTTON2 GPIO_Pin_14
#define BUTTON3 GPIO_Pin_15

#define BUTTON_GPIO	GPIOC

void button_init(void);
u8 read_button(u16 gpio_pin);
void check_button(void);

#endif
