#ifndef _SERVO_H_
#define _SERVO_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"	  
#include "stm32f10x_tim.h"

#define SERVO_TIM				TIM1
#define SERVO_PORT			GPIOB
#define SERVO_TIM_RCC		RCC_APB2Periph_TIM1
#define SERVO_GPIO_RCC	RCC_APB2Periph_GPIOB

void servo_init(u16 presc, u16 count, u16 init_pos);
void servo_control(u8 servo_id, u16 val );

#endif /*_SERVO_H_*/
