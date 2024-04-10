#ifndef _DRV_SYSTICK_MSP_H_
#define _DRV_SYSTICK_MSP_H_

/* 头文件包含 */
#include "stm32f10x.h"

/* 宏定义 */
#define TIMS_MS_RUN	0x80000000

/* 类型定义 */
typedef uint32_t time_ms_T;

/* 函数定义 */
void left_ms_set(time_ms_T *p,time_ms_T val);						//设置延时比较点
long left_ms(time_ms_T *p);															//计算剩下的ms数，第一次到延时点，返回0，过延时点再次查询返回-1
long left_ms_sta(time_ms_T *p);													//延时刚到第一次调用返回0，以后返回-1，延时不到返回剩下的ms数
void systick_init_msp(void);
void user_systick(void);
uint32_t* get_cnt_1ms(void);


#endif 

