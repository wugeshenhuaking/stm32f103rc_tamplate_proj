#include "drv_systick_msp.h"
#include "stm32f10x_it.h"

uint32_t cnt_1ms __attribute__((section(".ARM.__at_0x20000000")));

void systick_init_msp(void)
{
	
	/* 系统时钟不需要配置，stm32f103 会在进入主函数之前自动执行systemInit函数，这个函数初始化时钟，默认使用HSE 8M, 然后HSE*9=72 */
	/* AHB总线时钟就是72M */
	
	/* 配置 systick 时钟 */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	// 选择 AHB总线时钟（也就是系统内核时钟） 作为 systick的时钟 72M
	
	/* 配置SysTick寄存器装载值 */
	if(1 == SysTick_Config(SystemCoreClock/1000) )		// 配置systick重装载值，SystemCoreClock/1000 产生1ms 时间基准。开启systick中断
	{
		HardFault_Handler();														// 如果配置不成功，就会进入HardFault
	}
}

void user_systick(void)
{
	cnt_1ms++;		// 毫秒计时器
}

uint32_t* get_cnt_1ms(void)
{
	uint32_t *p = &cnt_1ms;
	return p;
}

void left_ms_set(time_ms_T *p,time_ms_T val)
{
	*p = (cnt_1ms+val) | TIMS_MS_RUN;		//设置时间轴上的比较点，并且设置运行标志
}

long left_ms_sta(time_ms_T *p)
{
	long r=0;
	
	if(*p & TIMS_MS_RUN)
	{										//处于运行阶段
		r=(*p-cnt_1ms) & (~TIMS_MS_RUN);			//获取比较点与当前时间计时的差
		
		if(r & 0x40000000)					//如果为负，说明已经超过比较点，延时结束
		{
			*p=0;							//清零运行标志
			r=0;							//清零返回值
		}
		//时间没到，返回剩下的ms数
	}
	else
	{
		r=-1;
	}
	return(r);								
}

long left_ms(time_ms_T *p)
{
	long r=0;
	
	if(*p & TIMS_MS_RUN)
	{										//处于运行阶段
		r=(*p-cnt_1ms) & (~TIMS_MS_RUN);			//获取比较点与当前时间计时的差
		
		if(r & 0x40000000)					//如果为负，说明已经超过比较点，延时结束
		{
			*p=0;							//清零运行标志
			r=0;							//清零返回值
		}
		//时间没到，返回剩下的ms数
	}
	
	return(r);	
}

