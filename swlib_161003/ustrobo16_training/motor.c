#include "motor.h"

void motor_init(u16 presc, u16 count, u16 init_val) {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_RCC|MOTOR_GPIO_RCC|RCC_APB2Periph_AFIO, ENABLE);	// Enable bus
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;						// Push-Pull Output Alternate-function
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_14;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						// Push-Pull Output Alternate-function
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//-------------TimeBase Initialization-----------//
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			// counter will count up (from 0 to FFFF)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;					//timer clock = dead-time and sampling clock 	
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	//------------------------------//
	TIM_TimeBaseStructure.TIM_Prescaler = presc;												//clk=72M/(71+1)= Hz, interval=? 
	TIM_TimeBaseStructure.TIM_Period = count;												//pulse cycle=x  xperiod for one up
	//------------------------------//366hz
	//40300for turn on  

	TIM_TimeBaseInit(MOTOR_TIM, &TIM_TimeBaseStructure);
	//final freq= timer freq / prescaler / period
	
	// ------------OC Init Configuration------------//
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   		// set "high" to be effective output
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;   		// set "high" to be effective output
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	           		// produce output when counter < CCR
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;		// Reset OC Idle state
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;	// Reset OC NIdle state
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  	// this part enable the normal output
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // this part enable the Nstate
	//------------------------------//
	TIM_OCInitStructure.TIM_Pulse = init_val;												// this part sets the initial CCR value that mean the pwm value
	//------------------------------//
	\
	// OC Init
	TIM_OC1Init(MOTOR_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(MOTOR_TIM, ENABLE);

	TIM_OC3Init(MOTOR_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(MOTOR_TIM, ENABLE);
	
	
	TIM_ARRPreloadConfig(MOTOR_TIM, ENABLE);
	TIM_Cmd(MOTOR_TIM, ENABLE);	
	TIM_SetCounter(MOTOR_TIM,0);
	TIM_CtrlPWMOutputs(MOTOR_TIM, ENABLE);

}

void motor_control(u8 motor_id, u8 dir, u16 magnitude){
	if (motor_id == 0) {
		if (dir == 0) {
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
			TIM_SetCompare1(MOTOR_TIM,magnitude);
		}	else {
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			TIM_SetCompare1(MOTOR_TIM,magnitude);
		}
	}
	
	if (motor_id == 1) {
		if (dir == 0) {
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
			TIM_SetCompare3(MOTOR_TIM,magnitude);
		} else {
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
			TIM_SetCompare3(MOTOR_TIM,magnitude);
		}	
	}
}
