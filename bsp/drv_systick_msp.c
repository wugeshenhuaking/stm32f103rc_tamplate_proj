#include "drv_systick_msp.h"
#include "stm32f10x_it.h"

uint32_t cnt_1ms __attribute__((section(".ARM.__at_0x20000000")));

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

uint32_t* get_cnt_1ms(void)
{
	uint32_t *p = &cnt_1ms;
	return p;
}

void left_ms_set(time_ms_T *p,time_ms_T val)
{
	*p = (cnt_1ms+val) | TIMS_MS_RUN;		//����ʱ�����ϵıȽϵ㣬�����������б�־
}

long left_ms_sta(time_ms_T *p)
{
	long r=0;
	
	if(*p & TIMS_MS_RUN)
	{										//�������н׶�
		r=(*p-cnt_1ms) & (~TIMS_MS_RUN);			//��ȡ�Ƚϵ��뵱ǰʱ���ʱ�Ĳ�
		
		if(r & 0x40000000)					//���Ϊ����˵���Ѿ������Ƚϵ㣬��ʱ����
		{
			*p=0;							//�������б�־
			r=0;							//���㷵��ֵ
		}
		//ʱ��û��������ʣ�µ�ms��
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
	{										//�������н׶�
		r=(*p-cnt_1ms) & (~TIMS_MS_RUN);			//��ȡ�Ƚϵ��뵱ǰʱ���ʱ�Ĳ�
		
		if(r & 0x40000000)					//���Ϊ����˵���Ѿ������Ƚϵ㣬��ʱ����
		{
			*p=0;							//�������б�־
			r=0;							//���㷵��ֵ
		}
		//ʱ��û��������ʣ�µ�ms��
	}
	
	return(r);	
}

