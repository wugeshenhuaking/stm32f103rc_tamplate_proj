#include "drv_systick_msp.h"
#include "stm32f10x_it.h"

static uint16_t fac_us =0;
static uint64_t cnt_1ms =0 ;
	

void systick_init_msp(void)
{
	
	/* 系统时钟不需要配置，stm32f103 会在进入主函数之前自动执行systemInit函数，这个函数初始化时钟，默认使用HSE 8M, 然后HSE*8=72 */
	/* AHB总线时钟就是72M */
	
	/* 配置 systick 时钟 */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			// 选择 HSE/8 作为 systick的时钟 1M
	
	/* 配置SysTick寄存器装载值 */
	if(1 == SysTick_Config(SystemCoreClock/1000) )
	{
		HardFault_Handler();// 如果配置不成功，就会进入HardFault
	}
	


}

