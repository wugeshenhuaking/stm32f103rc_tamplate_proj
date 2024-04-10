#include "app_led.h"
#include "drv_systick_msp.h"

typedef enum
{
	LED_BLINK_ON_SETP,
	LED_BLINK_OFF_SETP,
	LED_BLINK_IDLE_SETP,
	
}APP_LED_BLINK_STEP;


static APP_LED_T g_app_led;

APP_LED_T* get_app_led_struct(void)
{
	return &g_app_led;
}


void app_led_blink(APP_LED_T* p)
{
	if(0 == left_ms(p->p_timer))
	{
		app_led_single_led_on();
//		app_led_single_led_off();
//		left_ms_set(p->timer,1000);
	}
}
