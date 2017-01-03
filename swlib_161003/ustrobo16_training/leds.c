#include "leds.h"
#define LED_L  GPIO_Pin_4
#define LED_M  GPIO_Pin_3
#define LED_R  GPIO_Pin_15

void led_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_M | LED_L;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_R;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, LED_R);
	GPIO_ResetBits(GPIOB, LED_M);
	GPIO_ResetBits(GPIOB, LED_L);
}

void led_blink(GPIO_TypeDef* PORT, u16 gpio_pin) {
	static u8 state = 0;
	
	if (state)
		GPIO_SetBits(PORT, gpio_pin);
	else
		GPIO_ResetBits(PORT, gpio_pin);
	state = !state;
}
 
void led_off(GPIO_TypeDef* PORT, u16 gpio_pin) {
	GPIO_ResetBits(PORT, gpio_pin);
}

void led_on(GPIO_TypeDef* PORT, u16 gpio_pin) {
	GPIO_SetBits(PORT, gpio_pin);
}
