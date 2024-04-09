#include "drv_systick_msp.h"
#include "stm32f10x_it.h"

static uint16_t fac_us =0;
static uint64_t cnt_1ms =0 ;
	

void systick_init_msp(void)
{
	
	/* ϵͳʱ�Ӳ���Ҫ���ã�stm32f103 ���ڽ���������֮ǰ�Զ�ִ��systemInit���������������ʼ��ʱ�ӣ�Ĭ��ʹ��HSE 8M, Ȼ��HSE*8=72 */
	/* AHB����ʱ�Ӿ���72M */
	
	/* ���� systick ʱ�� */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			// ѡ�� HSE/8 ��Ϊ systick��ʱ�� 1M
	
	/* ����SysTick�Ĵ���װ��ֵ */
	if(1 == SysTick_Config(SystemCoreClock/1000) )
	{
		HardFault_Handler();// ������ò��ɹ����ͻ����HardFault
	}
	


}

