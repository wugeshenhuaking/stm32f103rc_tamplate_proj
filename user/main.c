#include "stm32f10x.h"
#include "drv_systick_bsp.h"
#include "app_led.h"

int main(void)
{
	
//	NVIC_SetPriorityGrouping(3);
	systick_init_bsp();
	app_led_msp_init();
	app_led_blink(get_app_led_struct());
	while(1)
	{
	}
}


