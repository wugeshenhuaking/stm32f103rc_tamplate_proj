#ifndef _DRV_SYSTICK_MSP_H_
#define _DRV_SYSTICK_MSP_H_

/* ͷ�ļ����� */
#include "stm32f10x.h"

/* �궨�� */
#define TIMS_MS_RUN	0x80000000

/* ���Ͷ��� */
typedef uint32_t time_ms_T;

/* �������� */
void left_ms_set(time_ms_T *p,time_ms_T val);						//������ʱ�Ƚϵ�
long left_ms(time_ms_T *p);															//����ʣ�µ�ms������һ�ε���ʱ�㣬����0������ʱ���ٴβ�ѯ����-1
long left_ms_sta(time_ms_T *p);													//��ʱ�յ���һ�ε��÷���0���Ժ󷵻�-1����ʱ��������ʣ�µ�ms��
void systick_init_msp(void);
void user_systick(void);
uint32_t* get_cnt_1ms(void);


#endif 

