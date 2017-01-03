#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"	  
#include "stm32f10x_tim.h"

#define MOTOR_TIM				TIM1
#define MOTOR_RCC				RCC_APB2Periph_TIM1
#define MOTOR_GPIO_RCC	RCC_APB2Periph_GPIOB

void motor_init(u16 presc, u16 count, u16 init_val);
void motor_control(u8 motor_id, u8 dir, u16 magnitude);

#endif
