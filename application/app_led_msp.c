#include "stm32f10x.h"

#define LED0_PORT 			GPIOA
#define LED0_PINS				GPIO_Pin_8
#define SET_LED0 				GPIO_SetBits(LED0_PORT,LED0_PINS)
#define RESET_LED0			GPIO_ResetBits(LED0_PORT,LED0_PINS)

void app_led_gpio_rcc_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

void app_led_gpio_mode_cfg(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED0_PINS;				 //LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(LED0_PORT, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
}

void app_led_gpio_pwm_mode_cfg(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Pin=LED0_PINS;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz ;
	GPIO_Init(LED0_PORT,&GPIO_InitStructure);
}


void app_led_msp_init(void)
{
	app_led_gpio_rcc_init();
	app_led_gpio_mode_cfg();
}

void app_led_single_led_on(void)
{
	RESET_LED0;
}

void app_led_single_led_off(void)
{
	SET_LED0;
}
