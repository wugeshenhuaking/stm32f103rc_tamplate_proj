#ifndef __APP_LED_H_
#define __APP_LED_H_


#include "stm32f10x.h"
#include "drv_systick_msp.h"

typedef struct
{
	uint8_t app_led_step;
	uint8_t app_led_task;
	time_ms_T p_timer;
}APP_LED_T;


APP_LED_T* get_app_led_struct(void);
void app_led_app_init(void);
void app_led_blink(APP_LED_T* p);


void app_led_msp_init(void);
void app_led_single_led_on(void);
void app_led_single_led_off(void);


#endif
