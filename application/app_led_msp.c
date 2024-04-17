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
	
	
	TIM_InternalClockConfig(TIM1);
	
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //时钟分频，主要控制滤波系数
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_InitStructure.TIM_Period = 100-1;  //ARR
    TIM_InitStructure.TIM_Prescaler = 720-1;  //PSC预分频值
    TIM_InitStructure.TIM_RepetitionCounter =0x00;	
	TIM_TimeBaseInit(TIM1,&TIM_InitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStucture;  //配置输出比较模块
	TIM_OCStructInit(&TIM_OCInitStucture);
	TIM_OCInitStucture.TIM_OCMode= TIM_OCMode_PWM1;  //输出模式
	TIM_OCInitStucture.TIM_OCPolarity = TIM_OCPolarity_High;  //极性选择
	TIM_OCInitStucture.TIM_OutputState = TIM_OutputState_Enable;  //使能
	TIM_OCInitStucture.TIM_Pulse =0 ;  //配置CCR
	TIM_OC1Init(TIM1,&TIM_OCInitStucture);
	
	TIM_Cmd(TIM1,ENABLE);
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
