#include "app_led.h"
#include "drv_systick_msp.h"

#define LED_DELAY_TIME 100U

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

enum {
    LED_IDLE_STEP=0,
    LED_ON_STEP,
    LED_OFF_STEP
};

void app_led_app_init()
{
    APP_LED_T* p = get_app_led_struct();
    p->app_led_task=1;
}

void app_led_blink(APP_LED_T* p)
{
	
    switch(p->app_led_step)
    {
        case LED_ON_STEP:
            if(0 == left_ms(&p->p_timer))
            {
                app_led_single_led_on();
                left_ms_set(&p->p_timer,LED_DELAY_TIME);
                p->app_led_step = LED_OFF_STEP;
            }
            break;
        case LED_OFF_STEP:
            if(0 == left_ms(&p->p_timer))
            {
                app_led_single_led_off();
                left_ms_set(&p->p_timer,LED_DELAY_TIME);
                p->app_led_step = LED_ON_STEP;
            }
            break;
        case LED_IDLE_STEP:
            if(p->app_led_task == 1)
            {
                p->app_led_step = LED_ON_STEP;
            }
            else
            {
                p->app_led_step = LED_IDLE_STEP;
            }
            break;
        default:
            break;
    }

}
