#include "drv_systick_msp.h"
#include "stm32f10x_it.h"

//static uint64_t cnt_1ms =0 ;


//volatile unsigned long cnt_1ms __attribute__((section(".ARM.__at_0x20000000")));

static uint64_t cnt_1ms=0;
	

void systick_init_msp(void)
{
	
	/* ϵͳʱ�Ӳ���Ҫ���ã�stm32f103 ���ڽ���������֮ǰ�Զ�ִ��systemInit���������������ʼ��ʱ�ӣ�Ĭ��ʹ��HSE 8M, Ȼ��HSE*9=72 */
	/* AHB����ʱ�Ӿ���72M */
	
	/* ���� systick ʱ�� */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	// ѡ�� AHB����ʱ�ӣ�Ҳ����ϵͳ�ں�ʱ�ӣ� ��Ϊ systick��ʱ�� 72M
	
	/* ����SysTick�Ĵ���װ��ֵ */
	if(1 == SysTick_Config(SystemCoreClock/1000) )		// ����systick��װ��ֵ��SystemCoreClock/1000 ����1ms ʱ���׼������systick�ж�
	{
		HardFault_Handler();														// ������ò��ɹ����ͻ����HardFault
	}
}

void user_systick(void)
{
	cnt_1ms++;		// �����ʱ��
}

