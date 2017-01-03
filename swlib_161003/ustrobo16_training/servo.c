#include "servo.h"
						
void servo_init(u16 presc, u16 count, u16 init_pos){
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(SERVO_TIM_RCC|SERVO_GPIO_RCC|RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;
	GPIO_Init(SERVO_PORT, &GPIO_InitStructure);
	
	//-------------TimeBase Initialization-----------//
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseStructure.TIM_Prescaler = presc;
	TIM_TimeBaseStructure.TIM_Period = count;
	TIM_TimeBaseInit(SERVO_TIM, &TIM_TimeBaseStructure);
	
	// ------------OC Init Configuration------------//
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = init_pos;
	
	// OC Init
	TIM_OC1Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(SERVO_TIM, ENABLE);

	TIM_OC3Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(SERVO_TIM, ENABLE);
	
	TIM_ARRPreloadConfig(SERVO_TIM, ENABLE);
	TIM_Cmd(SERVO_TIM, ENABLE);	
	TIM_SetCounter(SERVO_TIM, 0);
	TIM_CtrlPWMOutputs(SERVO_TIM, ENABLE);
}

void servo_control(u8 servo_id, u16 val){
	if(servo_id == 0){
		TIM_SetCompare1(SERVO_TIM,val);
	}
	if(servo_id == 1){
		TIM_SetCompare3(SERVO_TIM,val);
	}
}
